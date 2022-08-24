#include "../s21_decimal.h"

// Узнать, какой сейчас стоит знак (1: минус / 0: плюс)
int s21_getSign(s21_decimal num) {
  int sign;
  if ((num.bits[3] & (1 << 31)) == 0) {
    sign = 0;
  } else {
    sign = 1;
  }

  return sign;
}

// Указать значение знака
void s21_setSign(s21_decimal* num, int result) {
  if (result == 1) {
    num->bits[3] = num->bits[3] | (1 << 31);
  } else if (result == 0) {
    num->bits[3] = num->bits[3] & ~(1 << 31);
  }
}

// Узнать значение конкретного бита
int s21_getBit(s21_decimal num, int curBit) {
  int bit;
  if ((num.bits[curBit / 32] & (1 << curBit % 32)) == 0) {
    bit = 0;
  } else {
    bit = 1;
  }

  return bit;
}

// Указать значение конкретного бита
void s21_setBit(s21_decimal* num, int bit, int result) {
  if (result == 1) {
    num->bits[bit / 32] = num->bits[bit / 32] | (1 << bit % 32);
  } else if (result == 0) {
    num->bits[bit / 32] = num->bits[bit / 32] & ~(1 << bit % 32);
  }
}

int s21_getPower(s21_decimal num) {
  int power = 0;
  int counter = 0;
  int length = 16;
  while (length <= 23) {
    int bit = ((num.bits[3] & (1 << length)) != 0);
    power += bit * pow(2, counter);
    length++;
    counter++;
  }

  return power;
}

void s21_setPower(s21_decimal* num, int result) {
  int length = 16;
  while (length <= 23) {
    if (result > 0 && result % 2 == 1) {
      num->bits[3] = num->bits[3] | (1 << length);
    } else {
      num->bits[3] = num->bits[3] & ~(1 << length);
    }
    result /= 2;
    length++;
  }
}

int s21_shiftLeft(s21_decimal* num) {
  int isOverflow = s21_getBit(*num, 95);
  for (int i = 95; i >= 0; i--) {
    if (i != 0) {
      s21_setBit(num, i, s21_getBit(*num, i - 1));
    } else {
      s21_setBit(num, i, 0);
    }
  }
  return isOverflow;
}

int s21_shiftRight(s21_decimal* num) {
  int isOverflow = s21_getBit(*num, 1);
  for (int i = 0; i <= 95; i++) {
    if (i != 95) {
      s21_setBit(num, i, s21_getBit(*num, i + 1));
    } else {
      s21_setBit(num, i, 0);
    }
  }
  return isOverflow;
}
