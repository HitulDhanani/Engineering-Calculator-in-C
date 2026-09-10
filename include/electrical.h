#ifndef ELECTRICAL_H
#define ELECTRICAL_H

#include <stdbool.h>

/* Ohm's Law: V = I * R */
double ohms_law_voltage(double current, double resistance);
bool ohms_law_current(double voltage, double resistance, double *current);
bool ohms_law_resistance(double voltage, double current, double *resistance);

/* Electrical Power: P = V * I = I^2 * R = V^2 / R */
double power_from_vi(double voltage, double current);
double power_from_ir(double current, double resistance);
bool power_from_vr(double voltage, double resistance, double *power);

/* Menu Runners */
void run_ohms_law_menu(void);
void run_power_menu(void);

#endif /* ELECTRICAL_H */
