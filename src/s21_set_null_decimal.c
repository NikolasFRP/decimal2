#include "s21_decimal.h"

void s21_set_null_decimal(s21_decimal *dst) {
  dst->bits[0] = dst->bits[1] = dst->bits[2] = dst->bits[3] = 0;
}

// указатель на структуру в качестве аргумента
// g