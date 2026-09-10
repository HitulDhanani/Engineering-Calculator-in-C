#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/* Arithmetic Function Prototypes */
double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
bool divide(double a, double b, double *result);
double power(double base, double exponent);
bool square_root(double val, double *result);
bool modulo_op(long long a, long long b, long long *result);

/* Menu Runner */
void run_arithmetic_menu(void);

#endif /* CALCULATOR_H */
