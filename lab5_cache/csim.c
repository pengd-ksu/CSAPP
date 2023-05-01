#include <getopt.h>
#include <stdio.h>
// to import malloc, free, exit
#include <stdlib.h>
// to import atoi, strcpy
#include <string.h>

#include "cachelab.h"

#define MAXLEN 1000

// Construct input arguments as global variables
int s, E, b;
// Decide if print verbose information
int verbose = 0;

// char [] t holds the trace file name so that we could open it in parseTrace
char t[MAXLEN];

// Construct results as global var
int missCount, hitCount, evictionCount;

typedef struct _cacheLine {
    int valid;
    int tag;
    int timeStamp;// Older time stamp goes larger, newest set as 0
} cacheLine;

typedef struct _cacheSim {
    int S;
    int E;
    int B;
    cacheLine **line; // 2d array, so we use **
} cacheSim;

cacheSim *cache = NULL; // initialize it globally

void initCache(int s, int E, int b) {
    int S = 1 << s;
    int B = 1 << b;
    cache = (cacheSim *)malloc(sizeof(cacheSim));
    cache->S = S;
    cache->E = E;
    cache->B = B;
    cache->line = (cacheLine **) malloc (sizeof(cacheLine *) * S);
    for (int i = 0; i < S; i++) {
        cache->line[i] = (cacheLine *) malloc (sizeof (cacheLine) * E);
        for (int j = 0; j < E; j++) {
            cache->line[i][j].valid = 0;
            cache->line[i][j].tag = -1;
            cache->line[i][j].timeStamp = 0;
        }
    }
}

void freeCache() {
    int S = cache->S;
    for (int i = 0; i < S; i++) {
        free(cache->line[i]);
    }
    free(cache->line);
    free(cache);
}

// Find given the cache index (S), if there's any match cache line that has same tag
int matchCacheLine(int cacheTag, int cacheIndex) {
    for (int i = 0; i < cache->E; i++) {
        if (cache->line[cacheIndex][i].valid && cache->line[cacheIndex][i].tag == cacheTag) {
            return i;
        }
    }
    return -1;
}

// Given the cache index, find the first available one, which is invalid, to check if it's full
int getCacheLine(int cacheIndex) {
    for (int i = 0; i < cache->E; i++) {
        if (cache->line[cacheIndex][i].valid == 0) {
            return i;
        }
    }
    return -1;
}

// return the cache line index of the oldest time stamp
int find_LRU(int cacheIndex) {
    int maxIdx = 0, maxStamp = 0;
    for (int i = 0; i < cache->E; i++) {
        if (cache->line[cacheIndex][i].timeStamp > maxStamp) {
            maxIdx = i;
            maxStamp = cache->line[cacheIndex][i].timeStamp;
        }
    }
    return maxIdx;
}

// update the time stamp of cache lines under the same cache index
void update(int cacheIndex, int i, int cacheTag) {
    cache->line[cacheIndex][i].valid = 1;
    cache->line[cacheIndex][i].tag = cacheTag;
    for (int j = 0; j < cache->E; j++) {
        cache->line[cacheIndex][j].timeStamp++;
    }
    // The newest will be the smallest
    cache->line[cacheIndex][i].timeStamp = 0;
}

void updateCount(int cacheTag, int cacheIndex) {
    // Check if there's any match given the cache index
    int idx = matchCacheLine(cacheTag, cacheIndex);
    // There's no match
    if (idx == -1) {
        missCount++;
        if (verbose) {
            printf("miss\n");
        }
        // Check if it's already full under the index
        int i = getCacheLine(cacheIndex);
        // All the cache lines in this index are full, has to evict
        if (i == -1) {
            evictionCount++;
            i = find_LRU(cacheIndex);
        }
        update(cacheIndex, i, cacheTag);
    } else {
        hitCount++;
        if (verbose) {
            printf("hit\n");
        }
        update(cacheIndex, idx, cacheTag);
    }
}

void parseTrace() {
    FILE *pFile;
    pFile = fopen(t, "r");
    if (pFile == NULL) {
        fprintf(stderr, "Met error opening trace file");
        exit(0);
    }
    char operation;
    unsigned int address;
    int size;
    while (fscanf(pFile, " %c %x, %d", &operation, &address, &size) > 0) {
        int cacheTag = address >> (s + b);
        int cacheIndex = (address >> b) & (~(~0 << s));
        switch (operation) {
            case 'M':
                // M has two operations, a data load followed by a data store
                updateCount(cacheTag, cacheIndex);
                updateCount(cacheTag, cacheIndex);
                break;
            case 'L':
                updateCount(cacheTag, cacheIndex);
                break;
            case 'S':
                updateCount(cacheTag, cacheIndex);
                break;
            default:
                break;
        }
    }
    fclose(pFile);
}

void printUsage()
{
    printf("Usage: ./csim-ref [-hv] -s <num> -E <num> -b <num> -t <file>\n"
            "Options:\n"
            "  -h         Print this help message.\n"
            "  -v         Optional verbose flag.\n"
            "  -s <num>   Number of set index bits.\n"
            "  -E <num>   Number of lines per set.\n"
            "  -b <num>   Number of block offset bits.\n"
            "  -t <file>  Trace file.\n\n"
            "Examples:\n"
            "  linux>  ./csim-ref -s 4 -E 1 -b 4 -t traces/yi.trace\n"
            "  linux>  ./csim-ref -v -s 8 -E 2 -b 4 -t traces/yi.trace\n");
}

int main(int argc, char **argv)
{
    missCount = 0, hitCount = 0, evictionCount = 0;
    int opt = 0;

    while (-1 != (opt = getopt(argc, argv, "hvs:E:b:t:"))) {
        switch(opt) {
            case 'h':
                printUsage();
                exit(0);
            case 'v':
                verbose = 1;
                break;
            case 's':
                s = atoi(optarg);
                break;
            case 'E':
                E = atoi(optarg);
                break;
            case 'b':
                b = atoi(optarg);
                break;
            case 't':
                strcpy(t, optarg);
                break;
            default:
                printUsage();
                exit(1);
        }
    }
    initCache(s, E, b);
    parseTrace();
    printSummary(hitCount, missCount, evictionCount);
    return 0;
}
