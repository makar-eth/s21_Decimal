#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#define ONLY_SIGH 2147483648
#define SIGH_WITH_TWO_POWER 2147614720
#define ONLY_TWO_POWER 131072
#define ONLY_THREE_POWER 196608
#define ZERO 0

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum arithmetic_errors { NUMBER_INF = 1, NUMBER_MIN_INF = 2, DIVIDE_ZERO = 3 };

enum errors { OK = 0, ERROR = 1 };

enum state { FALSE = 0, TRUE = 1 };

typedef struct {
  int bits[4];
} s21_decimal;

/**
 * HELPERS
 */

// bits
int s21_getBit(s21_decimal num, int curBit);
void s21_setBit(s21_decimal* num, int bit, int result);
int s21_getSign(s21_decimal num);
void s21_setSign(s21_decimal* num, int result);
int s21_shiftLeft(s21_decimal* num);
int s21_shiftRight(s21_decimal* num);
int s21_getPower(s21_decimal num);
void s21_setPower(s21_decimal* num, int result);

// other
void output(s21_decimal num);
void init(s21_decimal* num);
int s21_add_helper(s21_decimal val_1, s21_decimal val_2, s21_decimal* result);
void s21_sub_helper(s21_decimal val_1, s21_decimal val_2, s21_decimal* result);
int s21_is_zeroed(s21_decimal value);
int s21_switch_result(int result);
s21_decimal s21_div_helper(s21_decimal value_1, s21_decimal value_2,
                           s21_decimal* result);
int s21_pow_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_pow_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_pow_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_normalize(s21_decimal* value_1, s21_decimal* value_2);
int s21_from_decimal_to_num(s21_decimal src, int* dst);

/**
 * MAIN
 */

// arithmetic
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);

// comparison
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

// converters and parsers
int s21_from_int_to_decimal(int src, s21_decimal* dst);
int s21_from_float_to_decimal(float src, s21_decimal* dst);
int s21_from_decimal_to_int(s21_decimal src, int* dst);
int s21_from_decimal_to_float(s21_decimal src, float* dst);

// another
int s21_floor(s21_decimal value, s21_decimal* result);
int s21_round(s21_decimal value, s21_decimal* result);
int s21_truncate(s21_decimal value, s21_decimal* result);
int s21_negate(s21_decimal value, s21_decimal* result);

#endif  //  SRC_S21_DECIMAL_H_
