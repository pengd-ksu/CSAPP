/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  return (~(x&y))&(~((~x)&(~y)));
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {

  return (1 << 31);

}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  /* -1, or 0xffffffff also satisfies the following property. However, -1+1=0,
  while Tmax+1=Tmin. We could use this to exclude x=-1. Because when x==-1,
  x+1==0, and !(x+1)==1. While !(Tmax+1)==0.*/
  int tmin_1 = x + 1 + !(x+1);
  int tmin_2 = ~x;
  return !(tmin_1^tmin_2);
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  /*According to test dlc, only only 0x0 - 0xff allowed*/
  int mask = 0xAA + (0xAA<<8);
  mask = mask + (mask<<16);
  return !((x&mask)^mask);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x + 1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
/* The first part checks if all the digits besides the right 8 on the left are all zeros
  The second part checks if digits on 4 to 7 from right are 0011
  The third part: every digits that are larger than 9, must have 1 on the most
  siginificant position (3 from right), and at least 1 on 4 or 5.
*/
int isAsciiDigit(int x) {
  return (!(x >> 8)) & (!((x&(0xf0))^(0x30))) & ((!(x&(0x08)))|(!(x&(0x06))));
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  x = !!x; /* x will be 0 if none zero; or 1 if 0*/
  x = ~x + 1; /*See below. x will be filled with 1 on every bit if 1;
               or 0 on every bit if 0, because negative one + 1 equals 0*/
  return (x&y) | ((~x)&z); /*When x is all 1, only keeps y and mask off z*/
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  /*As in function negate, -y=~y+1; so x-y=~y+x+1, and if ~y+x<0, x<=y;
  However, overflow could happen when (1) negative minus positive, or (2) 
  positive minus negative. For the former one, x is less than y, and it should 
  return 1; for the latter one, x is larger than y and it should return 0. When 
  x and y are both positive or both negative, there will not be overflow and we
  could use regular check as stated before. We could extract x and y's sign bit
  to handle overflow. When x is positive and y is negative, we will make sure
  0 is returned so the check stopped immediately; otherwise we should make sure
  1 is returned when x is negative and y is positive, or make sure regular 
  check continues for the rest posibilities. So x_sign and y_sign should be
  combined to make sure three out of four situations could continue, and we will
  use or (|) here. 0 should be returned immediately, so an and(&) should be used
  to combine overflow check and regular check. Overflow check on negative x and
  positive y should be accompanied with regular check with an or in the second 
  part, to make sure regular check doesn't happen when this type of overflow 
  occurs. And it also needs to make sure results of (1) positive x and positive 
  y, (2) negative x and negative y, will be dependent on regular check. That's 
  why x_sign and y_sign are combined with an and (&).*/
  int x_sign = x >> 31;
  int y_sign = y >> 31;
  int regular_check = !!((~y+x)>>31);
  return (x_sign | (!y_sign)) & ((x_sign & (!y_sign)) | regular_check);
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  /* For non-zero numbers, there exists a different negation, such as 1 and -1.
  While zero has a same negation. So we could check most significant bit. If
  it's 1, the number is non-zero and should return 0. Otherwise, it's 0 and 
  should return 1. However, from the tests we could see for overflow it's not
  the case. For example, 0x80 (suppose there are only 8 bits) would not have
  corresponding positive counterpart. like -128 to 127. The negation of the 
  smallest negative number will be itself. The final form should
  be something like ~(x op ~x+1)>>31. We need to decide the form of op. For 
  1 op 0, and 0 op 1, and 1 op 1 (overflow), the result should be 1. And for
  0 op 0, the result should be 0. So op should be 'or'. 
  However, it still couldn't pass the test of 0xff (still suppose 8 bits here).
  Because when most significant bit is 1, shifting right is usually implemented
  as arithmetically in c, as on page P58 of CSAPP. Sothe final step we should
  mask with 1. Otherwise, the result will be -1.*/
  return (~(x|(~x+1))>>31)&1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  int first_16, first_8, first_4, first_2, first_1, first_0;
  /* The first trick, change negative number via ~. Like 1111 1011,
  to 0000 0100. That's because the former one could also be displayed
  as 1011, and its ~ form 0100 could be used to find the minimum
  number of bits(starting with 1). Find the first 0, and plus 1 could
  get the number of bits. As for non-negative number, we also need a
  leading 0 to denote the sign bit. That's why howManyBits(12)=5,
  because 12 is 01100, with a leading 0.*/
  int sign_x = x >> 31; /**/
  int transfer_x = (sign_x&~x) | (~sign_x&x);
  /* The second trick, kind of like binary search, but we need to move
  all the higher rank to its lower rank, because (1) we only to count 
  the lower ranks in total and don't need the lower ranks anymore; (2)
  to keep the form in consistency. For example, !!(transfer_x >> 16) << 4
  would be zero or 2^4, depending whther the first 16 bits contains 1 
  or not. If it is, move 16 higher rank bits to right; if not, doesn't
  move, or we could say move zero bits. In that case, the form would be
  consistent.*/
  first_16 = !!(transfer_x >> 16) << 4;
  transfer_x = transfer_x >> first_16;
  first_8 = !!(transfer_x >> 8) << 3;
  transfer_x = transfer_x >> first_8;
  first_4 = !!(transfer_x >> 4) << 2;
  transfer_x = transfer_x >> first_4;
  first_2 = !!(transfer_x >> 2) << 1;
  transfer_x = transfer_x >> first_2;
  first_1 = !!(transfer_x >> 1) << 1;
  first_0 = transfer_x >> first_1;
  return first_16+first_8+first_4+first_2+first_1+first_0+1;
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  int exp =(uf&0x7f800000)>> 23;
  if (exp == 255)/*Check if uf is NaN or infinity*/
    return uf;
  int sign = (1<<31) & uf;
  if (exp == 0)
    return (uf<<1) | sign;/*If it's a small fraction number, it won't overflow*/
  exp++;/*If times 2 is equal to add one to the exponent*/
  if (exp == 255) /*Check if uf will become infinity after timing 2*/
    return 0x7f800000 | sign;/*Keep the sign*/
  else
    return (exp<<23) | (uf&0x807fffff);
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  int sign = (1<<31)&uf;
  int exp = (uf&0x7f800000)>>23;
  if (exp == 0) /*Denormalized numbers are less than or equal to 0, coerce to 0.ß*/
    return 0;
  if (exp == 255)
    return 0x80000000u;
  /* We have excluded denormailized,infinity and NaN. So we only consider 
  normalized here. So Bias=127 for signle precision. And frac has an extra
  leading 1 which is implicit. */
  int frac = (uf&0x007fffff) | 0x00800000; //
  int E = exp - 127;
  if (E < 0)
    return 0;
  else if (E > 31) /* The sign bit will be covered*/
    return 0x80000000u;
  else if (E > 23)
    frac <<= (E-23);/*set frac to itself shifted by (E-23) bits to the left*/
  else
    frac >>= (23-E);
  if (!((frac&0x80000000)^sign)) /*Check if there's overflow. Sign bit will
  be different after coercion if overflow occurs*/
    return frac;
  else if (frac>>31) /* Overflow from positive to negative*/
    return 0x80000000u;
  else
    return ~frac+1;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
  /*Consider 2.0^x as 1.0*2.0^x, we could represent the result with IEEE 
  floating point numbers, and the fraction parts should all be zeros. And with
  a leading 1, the fraction part should represent 1.0. Check whether there 
  would be overflow.*/
    int INFINITY = 0x7f800000; /*Positive infinity only*/
    int exp = x +127; /*Bias of normalized is 127 for single precision*/
    if (exp <= 0)
      return 0;
    else if (exp >= 255)
      return INFINITY; /*Overflow for the exp part*/
    else
      return exp << 23;
}
