#include "../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal* result) {
  *result = value;

  //
  return OK;
}

int s21_round(s21_decimal value, s21_decimal* result) {
  *result = value;

  //
  return OK;
}

int s21_truncate(s21_decimal value, s21_decimal* result) {
  *result = value;
  // int pow = s21_getPower(value);
  int out = OK;

  // if (pow > 0) {
  //   if (pow > 28) {
  //     out = ERROR;
  //   } else {
  //     //
  //   }
  // }

  // get the decimal * -10 *pow
  // substract

  // or
  // -10 -> to decimal
  // pow -> to decimal
  // multiply
  // divide the orig decimal by result
  // substract this division from the original decimal

  return out;
}

int s21_negate(s21_decimal value, s21_decimal* result) {
  init(result);
  s21_decimal copy = value;
  int sign = s21_getSign(value);

  if (sign == 1) {
    s21_setSign(&copy, 0);
  } else if (sign == 0) {
    s21_setSign(&copy, 1);
  }

  *result = copy;
  return OK;
}
