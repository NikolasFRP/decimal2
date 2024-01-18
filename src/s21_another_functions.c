#include "s21_decimal.h"
// Округляет указанное Decimal число до ближайшего целого числа в сторону
// отрицательной
int s21_floor(s21_decimal value, s21_decimal *result) {
  // выставляет все нули
  s21_set_null_decimal(result);
  // округление по нижней границе
  s21_truncate(value, result);
  // Это условие проверяет знак числа value и сравнивает усеченное значение
  if (s21_get_sign(value) && !s21_is_equal(*result, value))
  //  Если исходное число отрицательное и после усечения результат не совпадает
  //  с исходным числом, к результату прибавляется -1. Функция всегда возвращает
  //  0.
  {
    s21_sub(*result, ((s21_decimal){{1, 0, 0, 0}}), result);
  }
  return 0;
}
// Округляет Decimal до ближайшего целого числа.
int s21_round(s21_decimal value, s21_decimal *result) {
  // устанавливает значение result в ноль
  s21_set_null_decimal(result);
  // объявление переменных для хранения временных значений
  long double fl_to_round = 0.0;
  long double difference = 0;
  // конвертация значения value в тип long double и сохранение в переменной
  // fl_to_round
  s21_from_decimal_to_double(value, &fl_to_round);
  // округление
  fl_to_round = round(fl_to_round);
  // если число отрицательно
  if (fl_to_round < 0.0) {
    // устанавливает 127 бит в еденицу (чтобы было положительным)
    s21_set_bit_on_index(result, 127, 1);
    // умножает все число на -1 делая его положительным
    fl_to_round *= -1;
  }
  // округляется вниз и затем делится на 2. Это выполняется для получения
  // следующего бита числа. Округление вниз гарантирует, что мы получаем
  // целочисленное значение при делении на 2. Разница между fl_to_round и его
  // округленным значением используется для определения, является ли следующий
  // бит равным 1. Если difference больше 0, это означает, что есть дробная
  // часть, и следующий бит должен быть установлен в 1.
  // происходит установка соответствующего бита в результате. Если difference
  // больше 0, то бит устанавливается в 1, иначе он устанавливается в 0.
  for (int i = 0; fl_to_round >= 1 && i < START_INFO; i++) {
    fl_to_round = floor(fl_to_round) / 2;
    difference = fl_to_round - floor(fl_to_round);
    if (difference > 0.0) {
      s21_set_bit_on_index(result, i, 1);
    } else {
      s21_set_bit_on_index(result, i, 0);
    }
  }
  s21_set_scale(result, 0);
  return 0;
}
// Возвращает целые цифры указанного Decimal числа; любые дробные цифры
// отбрасываются, включая конечные нули.
int s21_truncate(s21_decimal value, s21_decimal *result) {
  // устанавливает значение result в ноль
  s21_set_null_decimal(result);
  // ставим дефолт в ноль
  float difference = 0;
  // если масштаб числа value не равен нулю
  if (s21_get_scale(value)) {
    // конвертация значения value в тип long double и сохранение в переменной
    // fl_to_int
    long double fl_to_int = 0.0;
    s21_from_decimal_to_double(value, &fl_to_int);
    // округление вниз
    fl_to_int = trunc(fl_to_int);
    // если усеченное значение отрицательное, устанавливается соответствующий
    // бит в result
    // и fl_to_int делается положительным
    if (fl_to_int < 0.0) {
      s21_set_bit_on_index(result, 127, 1);

      fl_to_int *= -1;
    }
    // округляется вниз и затем делится на 2. Это выполняется для получения
    // следующего бита числа. Округление вниз гарантирует, что мы получаем
    // целочисленное значение при делении на 2.
    // Разница между fl_to_round и его округленным значением используется для
    // определения, является ли следующий бит равным 1. Если difference больше
    // 0, это означает, что есть дробная часть, и следующий бит должен быть
    // установлен в 1.
    // происходит установка соответствующего бита в результате. Если difference
    // больше 0, то бит устанавливается в 1, иначе он устанавливается в 0.
    for (int i = 0; fl_to_int >= 1 && i < START_INFO; i++) {
      fl_to_int = floor(fl_to_int) / 2;
      difference = fl_to_int - floor(fl_to_int);
      if (difference > 0.0) {
        s21_set_bit_on_index(result, i, 1);
      } else {
        s21_set_bit_on_index(result, i, 0);
      }
    }
    s21_set_scale(result, 0);
  } else {
    // копирование битов value в result
    for (int i = 0; i < 4; ++i) {
      result->bits[i] = value.bits[i];
    }
  }
  return 0;
}
// Возвращает результат умножения указанного Decimal на -1. (смена знака)
int s21_negate(s21_decimal dec, s21_decimal *result) {
  // задаем все нули
  s21_set_null_decimal(result);
  // получение знака числа
  int sign = s21_get_sign(dec);
  // копирование
  *result = dec;
  // 0 - отрицательно, 1 - положительное
  if (sign == 1) {
    s21_set_bit_on_index(result, 127, 0);

  } else {
    s21_set_bit_on_index(result, 127, 1);
  }
  return 0;
}
