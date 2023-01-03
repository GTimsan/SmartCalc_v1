#include <check.h>

#include "calc.h"

START_TEST(VALIDATION) {
    char str[20] = "(((5 / 4)))";
    int first = validator(str);   
    ck_assert_int_eq(first, 0);
    char str2[10] = "(5 / -4)";
    first = validator(str2);   
    ck_assert_int_eq(first / 1000, 8);
    char str3[10] = "(5 / 4-)";
    first = validator(str3);   
    ck_assert_int_eq(first / 1000, 8);
    char str4[10] = "(-5 / 4)";
    first = validator(str4);   
    ck_assert_int_eq(first, 0);
    char str5[50] = "-(5 / 4)";
    first = validator(str5);
    ck_assert_int_eq(first / 1000, 8);
    char str6[50] = "(-(5 / 4))";
    first = validator(str6);   
    ck_assert_int_eq(first, 0);
    char str7[50] = "(-(5 / 4)";
    first = validator(str7);   
    ck_assert_int_eq(first, 9);
    char str8[50] = "(-(5 / 4)) - (-5 * 4)";
    first = validator(str8);   
    ck_assert_int_eq(first, 0);
    char str9[50] = "(-(8/4))-(-5*4)";
    first = validator(str9);   
    ck_assert_int_eq(first, 0);
    // ----------------------------------------
    char str10[50] = "(3mod4)-(-5 mod 2) / ( 3 mod 3 )";
    first = validator(str10);   
    ck_assert_int_eq(first, 0);
    char str11[100] = "4 * sin(5) / (cos(-3 ))/tan(5*asin(acos(432 - 23)))";;
    first = validator(str11);   
    ck_assert_int_eq(first, 0);
    char str12[50] = "atan(-4 * ln(42.3)/log(-3)^sqrt(+5))";
    first = validator(str12);   
    ck_assert_int_eq(first, 0);

}
END_TEST

START_TEST(ADD) {
    char str[50] = "6.432 + 5.666 + 10.1 * 5.34 + 4.54";
    double result;
    int error = smart_calc_v_1(str, &result);   
    ck_assert_int_eq(error, 0);
    double second = 70.572;
    ck_assert_double_eq_tol(result, second, 1e-9);
    
    char str2[50] = "(6.432+5.666)+10.1*(5.34+4.54)";
    second = 111.886;
    error = smart_calc_v_1(str2, &result);   
    ck_assert_int_eq(error, 0);
    ck_assert_double_eq_tol(result, second, 1e-9);
}
END_TEST

START_TEST(UNARY_ADD) {
    char str[50] = "(+6.432) + (5.666 + (+10.1)) + ((+5.34) + 4.54)";
    double result;
    int error = smart_calc_v_1(str, &result);   
    ck_assert_int_eq(error, 0);
    double second = 32.078;
    ck_assert_double_eq_tol(result, second, 1e-9);
    
    char str2[50] = "(+(+6.432+5.666))+10.1+(+(5.34+4.54))";
    second = 32.078;
    error = smart_calc_v_1(str2, &result);   
    ck_assert_int_eq(error, 0);
    ck_assert_double_eq_tol(result, second, 1e-9);
}
END_TEST


START_TEST(SUB) {
    char str[50] = "6.432 - 5.666 - 10.1 * 5.34 - 4.54";
    double result;
    int error = smart_calc_v_1(str, &result);   
    ck_assert_int_eq(error, 0);
    double second = -57.708;
    ck_assert_double_eq_tol(result, second, 1e-9);
    
    char str2[50] = "(6.432-5.666)-10.1*(5.34-4.54)";
    second = -7.314;
    error = smart_calc_v_1(str2, &result);   
    ck_assert_int_eq(error, 0);
    ck_assert_double_eq_tol(result, second, 1e-9);
}
END_TEST


START_TEST(UNARY_SUB) {
    char str[60] = "(-6.432) - (5.666 - (-10.1)) - (-(-5.34 - (-4.54)))";
    double result;
    int error = smart_calc_v_1(str, &result);   
    ck_assert_int_eq(error, 0);
    double second = -22.998;
    ck_assert_double_eq_tol(result, second, 1e-9);
    
    char str2[50] = "(-(-6.432-5.666))-10.1* (-(5.34-4.54))";
    second = 20.178;
    error = smart_calc_v_1(str2, &result);   
    ck_assert_int_eq(error, 0);
    ck_assert_double_eq_tol(result, second, 1e-9);
}
END_TEST


START_TEST(MULT) {
    char str[60] = "6.432 * (5.666 * 10.1) * (5.34 * 4.54)";
    double result;
    int error = smart_calc_v_1(str, &result);   
    ck_assert_int_eq(error, 0);
    double second = 8923.62044005632;
    ck_assert_double_eq_tol(result, second, 1e-9);
    
    char str2[50] = "(-(6.432*5.666))*10.1* (-(5.34*4.54))";
    second = 8923.62044005632;
    error = smart_calc_v_1(str2, &result);   
    ck_assert_int_eq(error, 0);
    ck_assert_double_eq_tol(result, second, 1e-9);

    char str3[50] = "(-(6.432*(-5.666)))*10.1* (-(-(5.34*4.54)))";
    second = 8923.62044005632;
    error = smart_calc_v_1(str3, &result);   
    ck_assert_int_eq(error, 0);
    ck_assert_double_eq_tol(result, second, 1e-9);
}
END_TEST


START_TEST(DIV) {
    char str[60] = "6.432 / (5.666 / 10.1) / (5.34 / 4.54)";
    double result;
    int error = smart_calc_v_1(str, &result);   
    ck_assert_int_eq(error, 0);
    double second = 9.7477736310021933;
    ck_assert_double_eq_tol(result, second, 1e-9);
    
    char str2[50] = "(-(6.432/5.666))/10.1/ (-(5.34/4.54))";
    second = 0.0955570398098441;
    error = smart_calc_v_1(str2, &result);   
    ck_assert_int_eq(error, 0);
    ck_assert_double_eq_tol(result, second, 1e-9);

    char str3[50] = "(-(6.432/(-5.666)))/10.1/ (-(-(5.34/4.54)))";
    second = 0.0955570398098441;
    error = smart_calc_v_1(str3, &result);   
    ck_assert_int_eq(error, 0);
    ck_assert_double_eq_tol(result, second, 1e-9);
}
END_TEST

START_TEST(POW) {
    char str[60] = "2 ^(8^((-2) + 2)) ^ 2";
    double result;
    int error = smart_calc_v_1(str, &result);   
    ck_assert_int_eq(error, 0);
    double second = 4;
    ck_assert_double_eq_tol(result, second, 1e-9);
    
    char str2[50] = "2 ^ 2 ^ 3";
    second = 64;
    error = smart_calc_v_1(str2, &result);   
    ck_assert_int_eq(error, 0);
    ck_assert_double_eq_tol(result, second, 1e-9);
}
END_TEST

START_TEST(SIN) {
    char str[60] = "sin(sin(5 - 2) * sin(sin(5)))";
    double result;
    int error = smart_calc_v_1(str, &result);   
    ck_assert_int_eq(error, 0);
    double second = sin(sin(5 - 2) * sin(sin(5)));
    ck_assert_double_eq_tol(result, second, 1e-9);
}
END_TEST

START_TEST(COS) {
    char str[60] = "cos(cos(5 - 2) * cos(cos(5)))";
    double result;
    int error = smart_calc_v_1(str, &result);   
    ck_assert_int_eq(error, 0);
    double second = cos(cos(5 - 2) * cos(cos(5)));
    ck_assert_double_eq_tol(result, second, 1e-9);
}
END_TEST

START_TEST(TAN) {
    char str[60] = "tan(tan(5 - 2) * tan(tan(5)))";
    double result;
    int error = smart_calc_v_1(str, &result);   
    ck_assert_int_eq(error, 0);
    double second = tan(tan(5 - 2) * tan(tan(5)));
    ck_assert_double_eq_tol(result, second, 1e-9);
}
END_TEST

START_TEST(ASIN) {
    char str[60] = "asin(0.2)";
    double result;
    int error = smart_calc_v_1(str, &result);   
    ck_assert_int_eq(error, 0);
    double second = asin(0.2);
    ck_assert_double_eq_tol(result, second, 1e-9);
}
END_TEST

START_TEST(ACOS) {
    char str[60] = "acos(0.003)";
    double result;
    int error = smart_calc_v_1(str, &result);   
    ck_assert_int_eq(error, 0);
    double second = acos(0.003);
    ck_assert_double_eq_tol(result, second, 1e-9);
}
END_TEST

START_TEST(ATAN) {
    char str[60] = "atan(atan(5 - 2) * atan(atan(5)))";
    double result;
    int error = smart_calc_v_1(str, &result);   
    ck_assert_int_eq(error, 0);
    double second = atan(atan(5 - 2) * atan(atan(5)));
    ck_assert_double_eq_tol(result, second, 1e-9);
}
END_TEST
START_TEST(LN) {
    char str[60] = "ln(0.003)";
    double result;
    int error = smart_calc_v_1(str, &result);   
    ck_assert_int_eq(error, 0);
    double second = log(0.003);
    ck_assert_double_eq_tol(result, second, 1e-9);
}
END_TEST
START_TEST(LOG) {
    char str[60] = "log(0.003)";
    double result;
    int error = smart_calc_v_1(str, &result);   
    ck_assert_int_eq(error, 0);
    double second = log10(0.003);
    ck_assert_double_eq_tol(result, second, 1e-9);
}
END_TEST
START_TEST(SQRT) {
    char str[60] = "sqrt(8)";
    double result;
    int error = smart_calc_v_1(str, &result);   
    ck_assert_int_eq(error, 0);
    double second = sqrt(8);
    ck_assert_double_eq_tol(result, second, 1e-9);
}
END_TEST

Suite *s21_calc_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("s21_smart_calc");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, VALIDATION);
  tcase_add_test(tc_core, ADD);
  tcase_add_test(tc_core, UNARY_ADD);
  tcase_add_test(tc_core, SUB);
  tcase_add_test(tc_core, UNARY_SUB);
  tcase_add_test(tc_core, MULT);
  tcase_add_test(tc_core, DIV);
  tcase_add_test(tc_core, POW);
  tcase_add_test(tc_core, SIN);
  tcase_add_test(tc_core, COS);
  tcase_add_test(tc_core, TAN);
  tcase_add_test(tc_core, ASIN);
  tcase_add_test(tc_core, ACOS);
  tcase_add_test(tc_core, ATAN);
  tcase_add_test(tc_core, LN);
  tcase_add_test(tc_core, LOG);
  tcase_add_test(tc_core, SQRT);

  suite_add_tcase(s, tc_core);
  return s;
}

int main() {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = s21_calc_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? 0 : 1;
}
