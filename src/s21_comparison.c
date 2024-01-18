#include "s21_decimal.h"

// позволяет циклически переключать значение переменной между 1 и 2.
void s21_comparison_reverse(int *flag) {
  if (*flag == 1) {
    *flag = 2;
  } else if (*flag == 2) {
    *flag = 1;
  }
}

// 0 - числа равны побитово
// 1 - первое больше побитово
// 2 - второе больше побитово
int s21_comparison_bits(s21_decimal d1, s21_decimal d2) {
  // хранение значений чисел в битах
  int bit1 = 0;
  int bit2 = 0;
  // flag - для указания результата сравнения.
  int flag = 0;
  // Цикл проходит по битам чисел начиная с 95-го (и до 0) и прекращается, если
  // флаг становится ненулевым.
  for (int i = 95; i >= 0 && !flag; --i) {
    // Получение битов чисел d1 и d2 на текущем индексе i.
    bit1 = s21_get_bit_on_index(d1, i);
    bit2 = s21_get_bit_on_index(d2, i);
    // Сравнение битов. Если бит1 больше бит2, устанавливается флаг в 1.
    // Если бит1 меньше бит2, устанавливается флаг в 2.
    if (bit1 > bit2) {
      flag = 1;
    } else if (bit1 < bit2) {
      flag = 2;
    }
  }
  return flag;
}

// сравнение флагов
// 0 - раны
// 1 - первый больше
// 2 - второй больше
int s21_greater_num(int a, int b) {
  int flag = 0;
  if (a > b) {
    flag = 1;
  } else if (a < b) {
    flag = 2;
  } else if (a == b) {
    flag = 0;
  }
  return flag;
}

// Сравнение чисел с учетом знака и масштаба
int s21_comparison(s21_decimal d1, s21_decimal d2) {
  // для хранения результата сравнения.
  int flag = 0;
  // вычесление и извлечение экспоненты/масштаба далее вычисление их раницы
  int scale_dif = (s21_get_scale(d1) - s21_get_scale(d2));
  // Нормализация, выравнивание чисел по масштабу, чтобы их представление было
  // корректным для последующего сравнения
  s21_normalize(&d1, &d2);
  // Сравнение абсолютных значений чисел d1 и d2 и установка флага на основе
  // результата.
  flag = s21_greater_num(!s21_get_sign(d1), !s21_get_sign(d2));
  // если совпадают
  if (flag == 0) {
    // если  разница в масштабах неотрицательна
    if (scale_dif >= 0) {
      // измеряем и задаем флаг
      flag = s21_comparison_bits(d1, d2);
    } else {
      // если разница в масштабах отрицательна, то делаем положительной
      scale_dif = -scale_dif;
      flag = s21_comparison_bits(d2, d1);
      // задаем новый флаг сравнением побитово
      s21_comparison_reverse(&flag);
    }
    // Инверсия результата, если оба числа отрицательны.
    if (s21_get_sign(d1) && s21_get_sign(d2)) {
      s21_comparison_reverse(&flag);
    }
  } else {
    // Если флаг не равен 0 (различаются абсолютные значения), и оба числа равны
    // нулю, устанавливается флаг в 0.
    if (d1.bits[0] == 0 && d1.bits[1] == 0 && d1.bits[2] == 0 &&
        d2.bits[0] == 0 && d2.bits[1] == 0 && d2.bits[2] == 0) {
      flag = 0;
    }
  }
  return flag;
}
// сравнение двух чисел типа децимал
// 1 - первый больше
// 2 - второй больше
// 0 - равны
int s21_is_less(s21_decimal d1, s21_decimal d2) {
  return (s21_comparison(d1, d2) == 2) ? 1 : 0;
}

// проверка д1 меньше или равно д2
// д1 меньше 2
// д1 равно 0
// д1 больше 1
int s21_is_less_or_equal(s21_decimal d1, s21_decimal d2) {
  return (s21_comparison(d1, d2) == 2) || (s21_comparison(d1, d2) == 0) ? 1 : 0;
}

// д1 больше д2
// д1 меньше 2
// д1 равно 0
// д1 больше 1
int s21_is_greater(s21_decimal d1, s21_decimal d2) {
  return (s21_comparison(d1, d2) == 1) ? 1 : 0;
}

// д1 больше или равно д2
// д1 меньше 2
// д1 равно 0
// д1 больше 1
int s21_is_greater_or_equal(s21_decimal d1, s21_decimal d2) {
  return (s21_comparison(d1, d2) == 1) || (s21_comparison(d1, d2) == 0) ? 1 : 0;
}

// д1 равно д2
// д1 меньше 2
// д1 равно 0
// д1 больше 1
int s21_is_equal(s21_decimal d1, s21_decimal d2) {
  return (s21_comparison(d1, d2) == 0) ? 1 : 0;
}

// д1 не такой же как д2
// д1 меньше 2
// д1 равно 0
// д1 больше 1
int s21_is_not_equal(s21_decimal d1, s21_decimal d2) {
  return (s21_comparison(d1, d2) == 0) ? 0 : 1;
}
