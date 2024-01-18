//
// Created by nikolay on 1/18/24.
//

#include <stdio.h>
#include <math.h>
#include "s21_decimal.h"
#include <check.h>

int main(){
    printf("hi\n");
    s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
    s21_decimal val2 = {{2, 0, 0, 0}};
    s21_decimal res = {{0}};
    printf("expected - got  :  %d - %d\n",0, s21_mul(val1, val2, &res));
    return 0;
}