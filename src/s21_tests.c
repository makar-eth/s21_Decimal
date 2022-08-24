#include <check.h>

#include "s21_decimal.h"

void run_test(Suite *thesuit) {
  SRunner *therunner = srunner_create(thesuit);

  srunner_set_fork_status(therunner, CK_NOFORK);
  srunner_run_all(therunner, CK_NORMAL);
  srunner_ntests_failed(therunner);
  srunner_free(therunner);

  printf("\n");
}

// ARITHMETIC

// add

START_TEST(part1_add_normal) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {{1535}};
  value_1.bits[0] = 150;
  value_2.bits[0] = 35;
  s21_setPower(&value_2, 1);
  s21_add(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(s21_getPower(result), 1);
  ck_assert_int_eq(s21_getSign(result), 0);
}
END_TEST

START_TEST(part1_add_both_neg) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {{1535}};
  value_1.bits[0] = 150;
  value_2.bits[0] = 35;
  s21_setSign(&value_2, 1);
  s21_setSign(&value_1, 1);
  s21_setPower(&value_2, 1);
  s21_add(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(s21_getPower(result), 1);
  ck_assert_int_eq(s21_getSign(result), 1);
}
END_TEST

START_TEST(part1_add_error) {
  // s21_decimal value_1 = {0};
  // s21_decimal value_2 = {0};
  // s21_decimal result = {0};
  // value_1.bits[0] = 2147483647;
  // value_1.bits[1] = 2147483647;
  // value_1.bits[2] = 2147483647;
  // value_2.bits[0] = 35;
  // int res = s21_add(value_1, value_2, &result);
  // ck_assert_int_eq(res, INFINITY);
  // s21_setSign(&value_2, 1);
  // s21_setSign(&value_1, 1);
  // memset(&result, 0, sizeof(s21_decimal));
  // res = s21_add(value_1, value_2, &result);
  // ck_assert_int_eq(res, -INFINITY);
}
END_TEST

START_TEST(part1_add_one_greater) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  value_1.bits[0] = 540;
  value_2.bits[0] = 560;
  s21_decimal test = {{20}};
  s21_setSign(&value_2, 1);
  s21_add(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(s21_getSign(result), 1);
}
END_TEST

START_TEST(part1_add_one_sign) {
  s21_decimal value_1 = {{150}};
  s21_decimal value_2 = {{50}};
  s21_decimal result = {0};
  s21_decimal test = {{100}};
  s21_setSign(&value_1, 1);
  s21_add(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(s21_getPower(result), 0);
  ck_assert_int_eq(s21_getSign(result), 1);
  s21_setSign(&value_1, 0);
  s21_setSign(&value_2, 1);
  memset(&result, 0, sizeof(s21_decimal));
  s21_add(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(s21_getPower(result), 0);
  ck_assert_int_eq(s21_getSign(result), 0);
}
END_TEST

// sub

START_TEST(part1_sub_normal) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  value_1.bits[0] = 155;
  value_2.bits[0] = 55;
  s21_sub(value_1, value_2, &result);
  s21_decimal test = {0};
  test.bits[0] = 100;
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  memset(&result, 0, sizeof(s21_decimal));
  value_1.bits[0] = 50;
  value_2.bits[0] = 150;
  s21_sub(value_1, value_2, &result);
  int sign = s21_getSign(result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(sign, 1);
  memset(&result, 0, sizeof(s21_decimal));
  s21_setPower(&value_2, 2);
  test.bits[0] = 4850;
  s21_sub(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(s21_getPower(result), 2);
  ck_assert_uint_eq(s21_getSign(result), 0);
}
END_TEST

START_TEST(part1_sub_inf) {
  // s21_decimal value_1 = {0};
  // s21_decimal value_2 = {0};
  // s21_decimal result = {0};
  // value_1.bits[0] = 2147483647;
  // value_1.bits[1] = 2147483647;
  // value_1.bits[2] = 2147483647;
  // value_2.bits[0] = 55;
  // s21_setSign(&value_1, 1);
  // int res = s21_sub(value_1, value_2, &result);
  // ck_assert_uint_eq(res, -INFINITY);
}
END_TEST

START_TEST(part1_sub_one_sign) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  value_1.bits[0] = 150;
  value_2.bits[0] = 50;
  s21_setSign(&value_1, 1);
  s21_sub(value_1, value_2, &result);
  s21_decimal test = {0};
  test.bits[0] = 200;
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  int sign = s21_getSign(result);
  ck_assert_int_eq(sign, 1);
  memset(&result, 0, sizeof(s21_decimal));
  s21_setSign(&value_1, 0);
  s21_setSign(&value_2, 1);
  s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  int sign1 = s21_getSign(result);
  ck_assert_int_eq(sign1, 0);
}
END_TEST

START_TEST(part1_sub_two_sign) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  value_1.bits[0] = 150;
  value_2.bits[0] = 50;
  s21_setSign(&value_1, 1);
  s21_setSign(&value_2, 1);

  s21_sub(value_1, value_2, &result);
  s21_decimal test = {0};
  test.bits[0] = 100;
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  int sign = s21_getSign(result);
  ck_assert_int_eq(sign, 1);
  memset(&result, 0, sizeof(s21_decimal));
  s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  int sign1 = s21_getSign(result);
  ck_assert_int_eq(sign1, 1);
  value_1.bits[0] = 50;
  value_2.bits[0] = 150;
  memset(&result, 0, sizeof(s21_decimal));
  s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  sign1 = s21_getSign(result);
  ck_assert_int_eq(sign1, 0);
}
END_TEST

// mult

START_TEST(part1_mult_value_1_is_one) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 1;
  value_2.bits[0] = 10;
  test.bits[0] = 10;
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  s21_setSign(&value_1, 1);
  memset(&result, 0, sizeof(s21_decimal));
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(s21_getSign(result), 1);
}
END_TEST

START_TEST(part1_mult_value_2_is_one) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 15;
  value_2.bits[0] = 1;
  test.bits[0] = 15;
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
}
END_TEST

START_TEST(part1_mult_value_1_is_zero) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 0;
  value_2.bits[0] = 100;
  test.bits[0] = 0;
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
}
END_TEST

START_TEST(part1_mult_value_2_is_zero) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 7;
  value_2.bits[0] = 0;
  test.bits[0] = 0;
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
}
END_TEST

START_TEST(part1_mult_max) {
  // s21_decimal value_1 = {0};
  // s21_decimal value_2 = {0};
  // s21_decimal result = {0};
  // s21_decimal test = {0};
  // value_1.bits[0] = 2147483647;
  // value_1.bits[1] = 2147483647;
  // value_1.bits[2] = 2147483647;
  // value_2.bits[0] = 5;
  // test.bits[0] = 2147483645;
  // test.bits[1] = 2147483647;
  // test.bits[2] = 2147483647;
  // s21_setPower(&value_2, 1);
  // int res = s21_mul(value_1, value_2, &result);
  // ck_assert_uint_eq(result.bits[0], test.bits[0]);
  // ck_assert_uint_eq(s21_getPower(result), 0);
  // ck_assert_uint_eq(s21_getSign(result), 0);
  // ck_assert_uint_eq(res, 0);
}
END_TEST

START_TEST(part1_mult_big_power) {
  // s21_decimal value_1 = {0};
  // s21_decimal value_2 = {0};
  // s21_decimal result = {0};
  // s21_decimal test = {0};
  // value_1.bits[0] = 2147483647;
  // value_2.bits[0] = 255;
  // test.bits[0] = 4294967041;
  // test.bits[1] = 254;
  // s21_setPower(&value_2, 10);
  // int res = s21_mul(value_1, value_2, &result);
  // ck_assert_uint_eq(result.bits[0], test.bits[0]);
  // ck_assert_uint_eq(s21_getPower(result), 10);
  // ck_assert_uint_eq(s21_getSign(result), 0);
  // ck_assert_uint_eq(res, 0);
}
END_TEST

START_TEST(part1_mult_big_negative_over) {
  // s21_decimal value_1 = {0};
  // s21_decimal value_2 = {0};
  // s21_decimal result = {0};
  // value_1.bits[0] = 2147483647;
  // value_1.bits[1] = 2147483647;
  // value_1.bits[2] = 2147483647;
  // value_2.bits[0] = 15;
  // s21_setPower(&value_2, 1);
  // s21_setSign(&value_2, 1);
  // int res = s21_mul(value_1, value_2, &result);
  // ck_assert_uint_eq(res, -INFINITY);
}
END_TEST

START_TEST(part1_mult_big_over) {
  // s21_decimal value_1 = {0};
  // s21_decimal value_2 = {0};
  // s21_decimal result = {0};
  // value_1.bits[0] = 2147483647;
  // value_1.bits[1] = 2147483647;
  // value_1.bits[2] = 2147483647;
  // value_2.bits[0] = 15;
  // s21_setPower(&value_2, 1);
  // int res = s21_mul(value_1, value_2, &result);
  // ck_assert_uint_eq(res, INFINITY);
}
END_TEST

START_TEST(part1_mult_norm) {
  // s21_decimal value_1 = {0};
  // s21_decimal value_2 = {0};
  // s21_decimal result = {0};
  // value_1.bits[0] = 2147483647;
  // value_1.bits[1] = 2147483647;
  // value_1.bits[2] = 2147483647;
  // value_2.bits[0] = 15;
  // s21_setPower(&value_2, 4);
  // int res = s21_mul(value_1, value_2, &result);
  // ck_assert_uint_eq(s21_getPower(result), 2);
  // ck_assert_uint_eq(res, OK);
}
END_TEST

START_TEST(part1_mult_value_1_is_minus) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  s21_setSign(&value_1, 1);
  value_1.bits[0] = 15;
  value_2.bits[0] = 1;
  test.bits[0] = 15;
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(s21_getSign(result), 1);
}
END_TEST

START_TEST(part1_mult_value_2_is_minus) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 15;
  s21_setSign(&value_2, 1);
  value_2.bits[0] = 1;
  test.bits[0] = 15;
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(s21_getSign(result), 1);
}
END_TEST

START_TEST(part1_mult_value_1_is_zero_minus) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  s21_setSign(&value_1, 1);
  value_1.bits[0] = 0;
  value_2.bits[0] = 100;
  test.bits[0] = 0;
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(s21_getSign(result), 1);
}
END_TEST

START_TEST(part1_mult_value_2_is_zero_minus) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 7;
  s21_setSign(&value_2, 1);
  value_2.bits[0] = 0;
  test.bits[0] = 0;
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(s21_getSign(result), 1);
}
END_TEST

START_TEST(part1_mult_value_1_2_is_minus) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  s21_setSign(&value_1, 1);
  s21_setSign(&value_2, 1);
  value_1.bits[0] = 0;
  value_2.bits[0] = 100;
  test.bits[0] = 0;
  s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(s21_getSign(result), 0);
}
END_TEST

START_TEST(part1_mult_max_1) {
  // s21_decimal value_1 = {0};
  // s21_decimal value_2 = {0};
  // s21_decimal result = {0};
  // s21_decimal test = {0};
  // value_1.bits[0] = 2147483647;
  // value_1.bits[1] = 2147483647;
  // value_1.bits[2] = 2147483647;
  // s21_setSign(&value_1, 1);
  // value_2.bits[0] = 5;
  // s21_setSign(&value_2, 1);
  // test.bits[0] = 2147483645;
  // test.bits[1] = 2147483647;
  // test.bits[2] = 2147483647;
  // s21_setPower(&value_2, 1);
  // int res = s21_mul(value_1, value_2, &result);
  // ck_assert_uint_eq(result.bits[0], test.bits[0]);
  // ck_assert_uint_eq(s21_getPower(result), 0);
  // ck_assert_uint_eq(s21_getSign(result), 0);
  // ck_assert_uint_eq(res, 0);
}
END_TEST

START_TEST(part1_mult_max_2) {
  // s21_decimal value_1 = {0};
  // s21_decimal value_2 = {0};
  // s21_decimal result = {0};
  // s21_decimal test = {0};
  // value_1.bits[0] = 2147483647;
  // s21_setSign(&value_1, 1);
  // value_1.bits[1] = 2147483647;
  // value_1.bits[2] = 2147483647;
  // value_2.bits[0] = 5;
  // test.bits[0] = 2147483645;
  // test.bits[1] = 2147483647;
  // test.bits[2] = 2147483647;
  // s21_setPower(&value_2, 1);
  // int res = s21_mul(value_1, value_2, &result);
  // ck_assert_uint_eq(result.bits[0], test.bits[0]);
  // ck_assert_uint_eq(s21_getPower(result), 0);
  // ck_assert_uint_eq(s21_getSign(result), 1);
  // ck_assert_uint_eq(res, 0);
}
END_TEST

START_TEST(part1_mult_max_3) {
  // s21_decimal value_1 = {0};
  // s21_decimal value_2 = {0};
  // s21_decimal result = {0};
  // s21_decimal test = {0};
  // s21_setSign(&value_1, 1);
  // value_1.bits[0] = 2147483647;
  // value_1.bits[1] = 2147483647;
  // value_1.bits[2] = 2147483647;
  // value_2.bits[0] = 5;
  // test.bits[0] = 2147483645;
  // test.bits[1] = 2147483647;
  // test.bits[2] = 2147483647;
  // s21_setPower(&value_2, 1);
  // int res = s21_mul(value_1, value_2, &result);
  // ck_assert_uint_eq(result.bits[0], test.bits[0]);
  // ck_assert_uint_eq(s21_getPower(result), 0);
  // ck_assert_uint_eq(s21_getSign(result), 1);
  // ck_assert_uint_eq(res, 0);
}
END_TEST

// div

START_TEST(part1_div_zero) {
  // s21_decimal value_1 = {0};
  // s21_decimal value_2 = {0};
  // s21_decimal result = {0};
  // value_1.bits[0] = 150;
  // value_2.bits[0] = 0;

  // int result1 = s21_div(value_1, value_2, &result);
  // ck_assert_uint_eq(result1, NAN);
  // s21_setSign(&value_2, 1);
  // ck_assert_uint_eq(result1, NAN);
}
END_TEST

// mod

// COMPARISON

// less

START_TEST(part2_less_null) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[0] = 0;
  value_2.bits[0] = 0;
  ck_assert_int_eq(s21_is_less(value_1, value_2), FALSE);
  s21_setSign(&value_2, 1);
  ck_assert_int_eq(s21_is_less(value_1, value_2), FALSE);
}
END_TEST

START_TEST(part2_less_normal) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  for (int i = 0; i < 50; i++) {
    for (int j = 2; j < 52; j++) {
      for (int i = 0, j = 2; i < 50 || j < 51; i++, j++) {
        value_1.bits[0] = i;
        value_2.bits[0] = j;
        // printf("/// value_1 = %d, value_2 = %d \n", value_1.bits[0],
        //        value_2.bits[0]);
        ck_assert_int_eq(s21_is_less(value_1, value_2), TRUE);
        ck_assert_int_eq(s21_is_less(value_2, value_1), FALSE);
      }
    }
  }
}
END_TEST

START_TEST(part2_less_negative) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[0] = 20;
  value_2.bits[0] = 5;
  s21_setSign(&value_1, 1);
  ck_assert_int_eq(s21_is_less(value_1, value_2), TRUE);

  s21_setSign(&value_1, 0);
  s21_setSign(&value_2, 1);

  for (int i = 50; i < 0; i++) {
    for (int j = 48; j < 2; j++) {
      value_1.bits[0] = i;
      value_2.bits[0] = j;
      // printf("/// value_1 = %d, value_2 = %d \n", value_1.bits[0],
      //        value_2.bits[0]);
      ck_assert_int_eq(s21_is_less(value_1, value_2), TRUE);
      ck_assert_int_eq(s21_is_less(value_2, value_1), FALSE);
    }
  }
}
END_TEST

START_TEST(part2_less_pow) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[0] = 50;
  value_2.bits[0] = 30;
  s21_setPower(&value_1, 8);
  s21_setPower(&value_2, 8);
  ck_assert_int_eq(s21_is_less(value_1, value_2), FALSE);
  s21_setPower(&value_2, 0);
  ck_assert_int_eq(s21_is_less(value_1, value_2), TRUE);
}
END_TEST

// less or equal

START_TEST(part2_less_or_equal_normal) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  for (int i = 0, j = 1; i < 51 || j < 52; i++, j++) {
    value_1.bits[0] = i;
    value_2.bits[0] = j;
    ck_assert_int_eq(s21_is_less_or_equal(value_1, value_2), TRUE);
  }
  for (int i = 0, j = 0; i < 52 || j < 52; i++, j++) {
    value_1.bits[0] = i;
    value_2.bits[0] = j;
    ck_assert_int_eq(s21_is_less_or_equal(value_1, value_2), TRUE);
  }
}
END_TEST

START_TEST(part2_less_or_equal_with_sign) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[0] = 123450;
  value_2.bits[0] = 123450;

  s21_setSign(&value_2, 1);
  ck_assert_int_eq(s21_is_less_or_equal(value_1, value_2), FALSE);

  s21_setSign(&value_1, 1);
  ck_assert_int_eq(s21_is_less_or_equal(value_1, value_2), TRUE);

  s21_setSign(&value_2, 0);
  ck_assert_int_eq(s21_is_less_or_equal(value_1, value_2), TRUE);
}
END_TEST

// greater

START_TEST(part2_greater_null) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[0] = 0;
  value_2.bits[0] = 0;
  ck_assert_int_eq(s21_is_greater(value_1, value_2), FALSE);
  s21_setSign(&value_2, 1);
  ck_assert_int_eq(s21_is_greater(value_1, value_2), FALSE);
}
END_TEST

START_TEST(part2_greater_normal) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  for (int i = 1, j = 2; i < 50 || j < 51; i++, j++) {
    value_1.bits[0] = i;
    value_2.bits[0] = j;
    ck_assert_int_eq(s21_is_greater(value_1, value_2), FALSE);
    ck_assert_int_eq(s21_is_greater(value_2, value_1), TRUE);
  }
}
END_TEST

START_TEST(part2_greater_negative) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[0] = 20;
  value_2.bits[0] = 5;
  s21_setSign(&value_1, 1);
  ck_assert_int_eq(s21_is_greater(value_1, value_2), FALSE);
  s21_setSign(&value_1, 0);
  s21_setSign(&value_2, 1);
  ck_assert_int_eq(s21_is_greater(value_1, value_2), TRUE);
}
END_TEST

START_TEST(part2_greater_two_negative) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[0] = 20;
  value_2.bits[0] = 5;
  s21_setSign(&value_1, 1);
  s21_setSign(&value_2, 1);
  ck_assert_int_eq(s21_is_greater(value_1, value_2), FALSE);
}
END_TEST

START_TEST(part2_greater_pow) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[0] = 50;
  value_2.bits[0] = 30;
  s21_setPower(&value_1, 8);
  s21_setPower(&value_2, 8);
  ck_assert_int_eq(s21_is_greater(value_1, value_2), TRUE);
  s21_setPower(&value_2, 0);
  ck_assert_int_eq(s21_is_greater(value_1, value_2), FALSE);
}
END_TEST

// greater or equal

START_TEST(part2_greater_or_equal_normal) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  for (int i = 0, j = 1; i < 51 || j < 52; i++, j++) {
    value_1.bits[0] = i;
    value_2.bits[0] = j;
    ck_assert_int_eq(s21_is_greater_or_equal(value_1, value_2), FALSE);
  }
  for (int i = 0, j = 0; i < 52 || j < 52; i++, j++) {
    value_1.bits[0] = i;
    value_2.bits[0] = j;
    ck_assert_int_eq(s21_is_greater_or_equal(value_1, value_2), TRUE);
  }
}
END_TEST

START_TEST(part2_greater_or_equal_with_sign) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[0] = 123450;
  value_2.bits[0] = 123450;
  s21_setSign(&value_2, 1);
  ck_assert_int_eq(s21_is_greater_or_equal(value_1, value_2), TRUE);
  s21_setSign(&value_1, 1);
  ck_assert_int_eq(s21_is_greater_or_equal(value_1, value_2), TRUE);
  s21_setSign(&value_2, 0);
  ck_assert_int_eq(s21_is_greater_or_equal(value_1, value_2), FALSE);
}
END_TEST

// equal

START_TEST(part2_equal_1) {
  s21_decimal a = {{56, 0}}, b = {{56, 0}};
  ck_assert_uint_eq(s21_is_equal(a, b), TRUE);
}
END_TEST

START_TEST(part2_equal_2) {
  s21_decimal a = {{0, 0, 0, 1}}, b = {{0, 0, 0, 2147483647}};
  ck_assert_uint_eq(s21_is_equal(a, b), TRUE);
}
END_TEST

START_TEST(part2_equal_3) {
  s21_decimal a = {{0}}, b = {{0}};
  ck_assert_uint_eq(s21_is_equal(a, b), TRUE);
}
END_TEST

START_TEST(part2_equal_4) {
  s21_decimal a = {{111, 111, 122, 1}}, b = {{111, 111, 122, 1}};
  ck_assert_uint_eq(s21_is_equal(a, b), TRUE);
}
END_TEST

START_TEST(part2_equal_5) {
  s21_decimal a = {{111, 11231, 12332, 12222}}, b = {{111, 111, 122, 1}};
  ck_assert_uint_eq(s21_is_equal(a, b), FALSE);
}
END_TEST

START_TEST(part2_equal_6) {
  s21_decimal a = {{111, 11, 12332, 1222222}},
              b = {{119981, 1100001, 122, 1000001}};
  ck_assert_uint_eq(s21_is_equal(a, b), FALSE);
}
END_TEST

// not equal

START_TEST(part2_notequal_1) {
  s21_decimal a = {{56, 0}}, b = {{56, 0}};
  ck_assert_uint_eq(s21_is_not_equal(a, b), FALSE);
}
END_TEST

START_TEST(part2_notequal_2) {
  s21_decimal a = {{0, 0, 0, 2147483647}}, b = {{0, 0, 0, 2147483647}};
  ck_assert_uint_eq(s21_is_not_equal(a, b), FALSE);
}
END_TEST

START_TEST(part2_notequal_3) {
  s21_decimal a = {{0}}, b = {{0}};
  ck_assert_uint_eq(s21_is_not_equal(a, b), FALSE);
}
END_TEST

START_TEST(part2_notequal_4) {
  s21_decimal a = {{111, 111, 122, 1}}, b = {{111, 111, 122, 1}};
  ck_assert_uint_eq(s21_is_not_equal(a, b), FALSE);
}
END_TEST

START_TEST(part2_notequal_5) {
  s21_decimal a = {{111, 11231, 12332, 12222}}, b = {{111, 111, 122, 1}};
  ck_assert_uint_eq(s21_is_not_equal(a, b), TRUE);
}
END_TEST

START_TEST(part2_notequal_6) {
  s21_decimal a = {{111, 11, 12332, 1222222}},
              b = {{119981, 1100001, 122, 1000001}};
  ck_assert_uint_eq(s21_is_not_equal(a, b), TRUE);
}
END_TEST

// ANOTHER

// START_TEST(test_4_trunc_1) {
//   // test
// }
// END_TEST

START_TEST(part4_negate_normal) {
  s21_decimal value_1 = {{154345}};
  s21_decimal result = {0};
  s21_decimal test = {{154345}};
  s21_setSign(&value_1, 0);
  s21_negate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(s21_getSign(result), 1);
}
END_TEST

START_TEST(part4_negate_null) {
  s21_decimal value_1 = {{0}};
  s21_decimal result = {0};
  s21_decimal test = {0};
  s21_negate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(s21_getSign(result), 1);
}
END_TEST

START_TEST(part4_negate_negative) {
  s21_decimal value_1 = {{123455}};
  s21_decimal result = {0};
  s21_decimal test = {{123455}};
  s21_setSign(&value_1, 1);
  s21_negate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(s21_getSign(result), 0);
}
END_TEST

START_TEST(part4_negate_pow) {
  s21_decimal value_1 = {{123455}};
  s21_decimal result = {0};
  s21_decimal test = {{123455}};
  s21_setSign(&value_1, 1);
  s21_setPower(&value_1, 3);
  s21_negate(value_1, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(s21_getSign(result), 0);
  ck_assert_int_eq(s21_getPower(result), 3);
}
END_TEST

// SUITES

Suite *suite_1() {
  Suite *s = suite_create("suite_1");
  TCase *tc_add = tcase_create("tc_add");
  TCase *tc_sub = tcase_create("tc_sub");
  TCase *tc_mult = tcase_create("tc_mult");
  TCase *tc_div = tcase_create("tc_div");

  tcase_add_test(tc_add, part1_add_normal);
  tcase_add_test(tc_add, part1_add_both_neg);
  tcase_add_test(tc_add, part1_add_error);
  tcase_add_test(tc_add, part1_add_one_sign);
  tcase_add_test(tc_add, part1_add_one_greater);

  tcase_add_test(tc_sub, part1_sub_normal);
  tcase_add_test(tc_sub, part1_sub_inf);
  tcase_add_test(tc_sub, part1_sub_one_sign);
  tcase_add_test(tc_sub, part1_sub_two_sign);

  tcase_add_test(tc_mult, part1_mult_value_1_is_one);
  tcase_add_test(tc_mult, part1_mult_value_2_is_one);
  tcase_add_test(tc_mult, part1_mult_value_1_is_zero);
  tcase_add_test(tc_mult, part1_mult_value_2_is_zero);
  tcase_add_test(tc_mult, part1_mult_max);
  tcase_add_test(tc_mult, part1_mult_big_power);
  tcase_add_test(tc_mult, part1_mult_big_over);
  tcase_add_test(tc_mult, part1_mult_norm);
  tcase_add_test(tc_mult, part1_mult_big_negative_over);
  tcase_add_test(tc_mult, part1_mult_value_1_is_minus);
  tcase_add_test(tc_mult, part1_mult_value_2_is_minus);
  tcase_add_test(tc_mult, part1_mult_value_1_is_zero_minus);
  tcase_add_test(tc_mult, part1_mult_value_2_is_zero_minus);
  tcase_add_test(tc_mult, part1_mult_value_1_2_is_minus);
  tcase_add_test(tc_mult, part1_mult_max_1);
  tcase_add_test(tc_mult, part1_mult_max_2);
  tcase_add_test(tc_mult, part1_mult_max_3);

  tcase_add_test(tc_div, part1_div_zero);

  suite_add_tcase(s, tc_add);
  suite_add_tcase(s, tc_sub);
  suite_add_tcase(s, tc_mult);
  suite_add_tcase(s, tc_div);

  return s;
}

Suite *suite_2() {
  Suite *s = suite_create("suite_2");

  TCase *tc_less = tcase_create("tc_less");
  TCase *tc_less_or_equal = tcase_create("tc_less_or_equal");
  TCase *tc_greater = tcase_create("tc_greater");
  TCase *tc_greater_or_equal = tcase_create("tc_greater_or_equal");
  TCase *tc_equal = tcase_create("tc_equal");
  TCase *tc_notequal = tcase_create("tc_notequal");

  tcase_add_test(tc_less, part2_less_null);
  tcase_add_test(tc_less, part2_less_normal);
  tcase_add_test(tc_less, part2_less_negative);
  tcase_add_test(tc_less, part2_less_pow);

  tcase_add_test(tc_less_or_equal, part2_less_or_equal_normal);
  tcase_add_test(tc_less_or_equal, part2_less_or_equal_with_sign);

  tcase_add_test(tc_greater, part2_greater_null);
  tcase_add_test(tc_greater, part2_greater_normal);
  tcase_add_test(tc_greater, part2_greater_negative);
  tcase_add_test(tc_greater, part2_greater_pow);
  tcase_add_test(tc_greater, part2_greater_two_negative);

  tcase_add_test(tc_greater_or_equal, part2_greater_or_equal_normal);
  tcase_add_test(tc_greater_or_equal, part2_greater_or_equal_with_sign);

  tcase_add_test(tc_equal, part2_equal_1);
  tcase_add_test(tc_equal, part2_equal_2);
  tcase_add_test(tc_equal, part2_equal_3);
  tcase_add_test(tc_equal, part2_equal_4);
  tcase_add_test(tc_equal, part2_equal_5);
  tcase_add_test(tc_equal, part2_equal_6);

  tcase_add_test(tc_notequal, part2_notequal_1);
  tcase_add_test(tc_notequal, part2_notequal_2);
  tcase_add_test(tc_notequal, part2_notequal_3);
  tcase_add_test(tc_notequal, part2_notequal_4);
  tcase_add_test(tc_notequal, part2_notequal_5);
  tcase_add_test(tc_notequal, part2_notequal_6);

  suite_add_tcase(s, tc_equal);
  suite_add_tcase(s, tc_notequal);
  suite_add_tcase(s, tc_less);
  suite_add_tcase(s, tc_less_or_equal);
  suite_add_tcase(s, tc_greater);
  suite_add_tcase(s, tc_greater_or_equal);

  return s;
}

Suite *suite_4() {
  Suite *s = suite_create("suite_4");

  TCase *tc_negate = tcase_create("tc_negate");

  // tcase_add_test(tc1, test_4_trunc_1);

  tcase_add_test(tc_negate, part4_negate_normal);
  tcase_add_test(tc_negate, part4_negate_null);
  tcase_add_test(tc_negate, part4_negate_negative);
  tcase_add_test(tc_negate, part4_negate_pow);

  suite_add_tcase(s, tc_negate);

  return s;
}

int main() {
  printf("~~~~~~~~~\n");
  printf("\n");

  Suite *s_1 = suite_1();
  Suite *s_2 = suite_2();
  Suite *s_4 = suite_4();

  run_test(s_1);
  run_test(s_2);
  run_test(s_4);

  printf("\n");
  printf("~~~~~~~~~\n");

  return 0;
}
