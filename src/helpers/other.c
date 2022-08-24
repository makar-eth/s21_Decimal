#include "../s21_decimal.h"

// Вывод всех битов
void output(s21_decimal num) {
  for (int i = 127; i >= 0; i--) {
    int tmp = s21_getBit(num, i);
    printf("%d ", tmp);
    if (i == 96 || i == 64 || i == 32) {
      printf("\t");
    }
  }
}

// Зануление параметра result в функциях
void init(s21_decimal* num) {
  num->bits[0] = 0;
  num->bits[1] = 0;
  num->bits[2] = 0;
}

int s21_from_decimal_to_num(s21_decimal src, int *dst) {
  *dst = src.bits[0];
  int flag = 0;

  if (s21_getPower(src) != 0) {
    flag = 1;
  }

  if (s21_getSign(src))
    *(dst) = *(dst) * -1;


  return flag ? ERROR : OK;
}


// хелпер для основной функции (по факту и является сложением, но без кучи
// проверок, которые в оснойной функции сложения)
int s21_add_helper(s21_decimal val_1, s21_decimal val_2, s21_decimal* result) {
  init(result);
  int buffer = 0;
  for (int i = 0; i < 96; i++) {
    int bitVal_1 = s21_getBit(val_1, i);
    int bitVal_2 = s21_getBit(val_2, i);

    s21_setBit(result, i, bitVal_1 ^ bitVal_2 ^ buffer);

    buffer =
        (bitVal_1 && bitVal_2) || (bitVal_1 && buffer) || (bitVal_2 && buffer);
  }

  return buffer;
}

void s21_sub_helper(s21_decimal val_1, s21_decimal val_2, s21_decimal* result) {
  init(result);

  for (int i = 0; i < 96; i++) {
    int bitVal_1 = s21_getBit(val_1, i);
    int bitVal_2 = s21_getBit(val_2, i);

    s21_setBit(result, i, bitVal_1 ^ bitVal_2);

    if (bitVal_1 == 0 && bitVal_2 == 1) {
      int j = i + 1;
      while ((bitVal_1 = s21_getBit(val_1, j)) != 1) {
        s21_setBit(&val_1, j, 1);
        j++;
      }
      s21_setBit(&val_1, j, 0);
    }
  }
}


// s21_decimal s21_div_helper(s21_decimal value_1, s21_decimal value_2,
//                            s21_decimal* result) {}

// checks if values at 0-95 are zeroes
int s21_is_zeroed(s21_decimal value) {
  int result = TRUE;
  for (int i = 0; i < 96; i++) {
    if (s21_getBit(value, i) != 0) {
      result = FALSE;
    }
  }
  return result;
}

int s21_switch_result(int result) {
  if (result == FALSE) {
    result = TRUE;
  } else if (result == TRUE) {
    result = FALSE;
  }
  return result;
}

int s21_pow_is_less(s21_decimal value_1, s21_decimal value_2) {
  return (s21_getPower(value_1) < s21_getPower(value_2)) ? TRUE : FALSE;
}

int s21_pow_is_greater(s21_decimal value_1, s21_decimal value_2) {
  return (s21_getPower(value_1) > s21_getPower(value_2)) ? TRUE : FALSE;
}

int s21_pow_is_equal(s21_decimal value_1, s21_decimal value_2) {
  return (s21_getPower(value_1) == s21_getPower(value_2)) ? TRUE : FALSE;
}

void s21_bankers_rounding() {}

int s21_normalize(s21_decimal* value_1, s21_decimal* value_2) {
  int flag = 1;
  int powerSignCopy_1 = value_1->bits[3];
  int powerSignCopy_2 = value_2->bits[3];
  int power_1 = s21_getPower(*value_1);
  int power_2 = s21_getPower(*value_2);

  if (power_1 == power_2) flag = 0;

  if (flag) {
    int minPower = power_1, maxPower = power_2;
    s21_decimal *minPow_ValCopy = value_1, *maxPow_ValCopy = value_2;

    if (power_1 > power_2) {
      maxPower = power_1;
      maxPow_ValCopy = value_1;
    }
    if (power_2 < power_1) {
      minPower = power_2;
      minPow_ValCopy = value_2;
    }

    s21_decimal nextStep;
    s21_from_int_to_decimal(10, &nextStep);

    while (minPower != maxPower) {
      int mul10 = s21_mul(*minPow_ValCopy, nextStep, minPow_ValCopy);
      if (!mul10 && minPower <= 27) {
        s21_setPower(minPow_ValCopy, minPower);
        minPower++;
      } else {
        s21_bankers_rounding();
        break;
      }
    }

    value_1->bits[3] = powerSignCopy_1;
    value_2->bits[3] = powerSignCopy_2;
    s21_setPower(minPow_ValCopy, minPower);
    s21_setPower(maxPow_ValCopy, minPower);
  }

  return flag;
}
