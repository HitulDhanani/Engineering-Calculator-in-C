#ifndef UNITS_H
#define UNITS_H

#include <stdbool.h>

/* Temperature Conversions */
double celsius_to_fahrenheit(double c);
double fahrenheit_to_celsius(double f);
double celsius_to_kelvin(double c);
double kelvin_to_celsius(double k);
double fahrenheit_to_kelvin(double f);
double kelvin_to_fahrenheit(double k);

/* Pressure Units (Common in Instrumentation & Control) */
/* Base unit internally: Pascal (Pa) */
double bar_to_pascal(double bar);
double pascal_to_bar(double pa);
double psi_to_pascal(double psi);
double pascal_to_psi(double pa);
double mmhg_to_pascal(double mmhg);
double pascal_to_mmhg(double pa);

/* Menu Runners */
void run_temperature_menu(void);
void run_pressure_menu(void);
void run_unit_conversion_menu(void);

#endif /* UNITS_H */
