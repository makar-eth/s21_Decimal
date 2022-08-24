#include "../s21_decimal.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int result = TRUE;
  int sign_1 = s21_getSign(value_1);
  int sign_2 = s21_getSign(value_2);
  int pow_1 = s21_getPower(value_1);
  int pow_2 = s21_getPower(value_2);

  if (s21_is_equal(value_1, value_2) || (!sign_1 && sign_2)) {
    result = FALSE;
  } else if (sign_1 == sign_2) {
    for (int i = 95; i >= 0; i--) {
      int bit_1 = s21_getBit(value_1, i);
      int bit_2 = s21_getBit(value_2, i);

      if (bit_1 > bit_2) {
        result = FALSE;
        break;
      } else if (bit_2 > bit_1) {
        result = TRUE;
        break;
      }
    }

    if (pow_1 > pow_2) {
      result = s21_switch_result(result);
    }
    if (sign_1 && sign_2) {
      result = s21_switch_result(result);
    }
  }

  return result;
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = FALSE;

  if (s21_is_equal(value_1, value_2) == TRUE ||
      s21_is_less(value_1, value_2) == TRUE) {
    result = TRUE;
  }
  return result;
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int result = TRUE;

  if (s21_is_less(value_1, value_2) == TRUE ||
      s21_is_equal(value_1, value_2) == TRUE) {
    result = FALSE;
  }
  return result;
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = FALSE;

  if (s21_is_equal(value_1, value_2) == TRUE ||
      s21_is_greater(value_1, value_2) == TRUE) {
    result = TRUE;
  }
  return result;
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = TRUE;
  int sign_1 = s21_getSign(value_1);
  int sign_2 = s21_getSign(value_2);
  int pow_1 = s21_getPower(value_1);
  int pow_2 = s21_getPower(value_2);

  if (s21_is_zeroed(value_1) == FALSE || s21_is_zeroed(value_2) == FALSE) {
    if (sign_1 == sign_2 && pow_1 == pow_2) {
      for (int i = 0; i < 3; i++) {
        if (value_1.bits[i] != value_2.bits[i]) {
          result = FALSE;
          break;
        }
      }
    } else {
      result = FALSE;
    }
  }
  return result;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return (s21_is_equal(value_1, value_2) == TRUE) ? FALSE : TRUE;
}
