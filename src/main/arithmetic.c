#include "../s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_normalize(&value_1, &value_2);
  int signVal1 = s21_getSign(value_1);
  int signVal2 = s21_getSign(value_2);
  int startPower = s21_getPower(value_1);

  int isOverflow = 0;
  s21_decimal value1Absolute = value_1;
  s21_decimal value2Absolute = value_2;

  if (s21_getSign(value1Absolute)) s21_setSign(&value1Absolute, 0);
  if (s21_getSign(value2Absolute)) s21_setSign(&value2Absolute, 0);

  if (!(s21_getSign(value_1) ^ s21_getSign(value_2))) {
    isOverflow = s21_add_helper(value_1, value_2, result);
    s21_setSign(result, signVal1);
    if (isOverflow && signVal1) {
      isOverflow = NUMBER_MIN_INF;
    }
  } else if (s21_is_less(value1Absolute, value2Absolute)) {
    s21_sub_helper(value_2, value_1, result);
    s21_setSign(result, signVal2);
  } else {
    s21_sub_helper(value_1, value_2, result);
    s21_setSign(result, signVal1);
  }

  s21_setPower(result, startPower);

  return OK;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int sign = !s21_getSign(value_2);
  s21_setSign(&value_2, sign);
  s21_add(value_1, value_2, result);

  return OK;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  // Если что нормалайз здесь не нужен хдд. Здесь работает всё
  // сдвигу и нам важно оставять все биты на своих местах хдд.
  // Есть вонючий баг с умножением чисел < 1 && > 0 : Вместо
  // записи 0.123 со степенью 3 соответственно, будет записано
  // 0.1230 со степенью 4 хддд.
  s21_decimal val1Cpy;
  s21_decimal localResult;
  init(&localResult);
  init(result);
  int i = 0;
  for (i = 0; i < 96; i++) {
    init(&val1Cpy);
    if (s21_getBit(value_2, i) == 1) {
      val1Cpy = value_1;
      int j = 0;
      while (j < i) {
        if (s21_shiftLeft(&val1Cpy)) break;
        j++;
      }

      s21_add_helper(val1Cpy, localResult, &localResult);
    }
  }

  if ((s21_getSign(value_1) && !s21_getSign(value_2)) ||
      ((!s21_getSign(value_1) && s21_getSign(value_2))))
    s21_setSign(&localResult, 1);

  s21_setPower(&localResult, s21_getPower(value_1) + s21_getPower(value_2));

  *result = localResult;

  return OK;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  // Затычка хддд
  init(result);
  int flag = 0;
  s21_decimal zero = {{0, 0, 0, 0}};

  if (s21_is_equal(value_2, zero)) flag = 1;

  s21_normalize(&value_1, &value_2);

  return flag ? DIVIDE_ZERO : OK;
}

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  // s21_decimal nul = {0};
  // *result = s21_div_helper(value_1, value_2, NULL);

  // затычка
  if (s21_is_equal(value_1, value_2)) {
    *result = value_1;
  } else {
    *result = value_2;
  }

  return OK;
}
