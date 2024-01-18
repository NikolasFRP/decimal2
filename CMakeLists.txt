cmake_minimum_required(VERSION 3.26)
project(decimal2 C)

set(CMAKE_C_STANDARD 11)

include_directories(src)
include_directories(src/unit_tests)

add_executable(decimal2
        src/main.c
        src/s21_another_functions.c
        src/s21_arithmetic.c
        src/s21_comparison.c
        src/s21_converters.c
        src/s21_decimal.h
        src/s21_get_set.c
        src/s21_normalize.c
        src/s21_rand_r.c
        src/s21_zero_decimal.c)
  add_executable(test
          src/unit_tests/s21_add_test.c
          src/unit_tests/s21_decimal_test.c
          src/unit_tests/s21_decimal_test.h
          src/unit_tests/s21_div_test.c
          src/unit_tests/s21_float_to_decimal_test.c
          src/unit_tests/s21_floor_test.c
          src/unit_tests/s21_from_decimal_to_float_test.c
          src/unit_tests/s21_from_decimal_to_int_test.c
          src/unit_tests/s21_from_int_to_decimal_test.c
          src/unit_tests/s21_is_equal.c
          src/unit_tests/s21_is_greater_or_equal_test.c
          src/unit_tests/s21_is_greater_test.c
          src/unit_tests/s21_is_less_or_equal_test.c
          src/unit_tests/s21_is_less_test.c
          src/unit_tests/s21_is_not_equal_test.c
          src/unit_tests/s21_mod_test.c
          src/unit_tests/s21_mul_test.c
          src/unit_tests/s21_negate_test.c
          src/unit_tests/s21_round_test.c
          src/unit_tests/s21_round_test2.c
          src/unit_tests/s21_sub_test.c
          src/unit_tests/s21_truncate_test.c
          src/unit_tests/s21_truncate_test2.c
          src/s21_another_functions.c
          src/s21_arithmetic.c
          src/s21_comparison.c
          src/s21_converters.c
          src/s21_decimal.h
          src/s21_get_set.c
          src/s21_normalize.c
          src/s21_rand_r.c
          src/s21_zero_decimal.c
  )

target_link_libraries(decimal2 PRIVATE  check subunit m)
target_link_libraries(test PRIVATE check subunit m)
