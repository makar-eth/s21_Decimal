#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  init(dst);
  int flag = 0;

  if (src == -INFINITY || src == INFINITY) {
    flag = 1;
  }

  if (flag == 0) {
    if (src < 0) {
      dst->bits[0] = -src;
      s21_setSign(dst, 1);
    } else {
      dst->bits[0] = src;
      s21_setSign(dst, 0);
    }
  }

  return flag ? ERROR : OK;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  *dst = src.bits[0];
  int flag = 0;

  if (s21_getPower(src) != 0) {
    flag = 1;
  }

  if (s21_getSign(src)) *(dst) = *(dst) * -1;

  return flag ? ERROR : OK;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  // затычка
  init(dst);
  s21_decimal temp = {0};
  int value = 0;
  if (src == 0) {
    value = 0;
  } else {
    value = 1;
  }
  temp.bits[0] = value;
  *dst = temp;

  return OK;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  *dst = 0;

  double nextStep = 1;
  // int sign = 1;
  double result = 0;
  int power = s21_getPower(src);

  for (int i = 0; i < 96; i++) {
    if (s21_getBit(src, i)) result += nextStep;
    nextStep *= 2;
  }
  for (int i = 0; i < power; i++) result /= 10;

  if (s21_getSign(src)) {
    *dst = -result;
  } else {
    *dst = result;
  }

  return OK;
}
