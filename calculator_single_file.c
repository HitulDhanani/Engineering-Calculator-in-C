/**
 * ============================================================================
 * Engineering Calculator in C (Instrumentation & Control Engineering Edition)
 * ============================================================================
 * Standalone Single-File Version
 * Ideal for single-file compilation, OnlineGDB, Turbo C++, Code::Blocks, Dev-C++
 * 
 * Features:
 *   1. Arithmetic & Safe Math (Zero-division & domain safety)
 *   2. Temperature Conversions (Celsius, Fahrenheit, Kelvin)
 *   3. Ohm's Law (V = IR, I = V/R, R = V/I)
 *   4. Electrical Power (P = VI, P = I^2*R, P = V^2/R)
 *   5. Instrumentation Unit Conversions (Pressure: Bar, PSI, Pa, mmHg; Length)
 *   6. RPM & Motor Speed (Tachometer pulse, AC Synchronous Motor, Linear speed)
 *   7. Sensor Data Analytics (Mean, Min, Max, Span, Standard Deviation)
 *   8. 4-20 mA Industrial Process Signal Scaling (Transmitter loop to PV)
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/* ============================================================================
 * SECTION 1: UTILITIES & SAFE INPUT HANDLING
 * ============================================================================ */

void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* Discard */
    }
}

void print_divider(char ch, int length) {
    for (int i = 0; i < length; i++) {
        putchar(ch);
    }
    putchar('\n');
}

void print_header(const char *title) {
    printf("\n");
    print_divider('=', 60);
    printf("  %s\n", title);
    print_divider('=', 60);
}

void wait_for_enter(void) {
    printf("\nPress [ENTER] to return to the menu...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* wait */
    }
}

bool get_int_input(const char *prompt, int *output) {
    char buffer[128];
    printf("%s", prompt);
    if (!fgets(buffer, sizeof(buffer), stdin)) {
        return false;
    }
    char *endptr;
    long val = strtol(buffer, &endptr, 10);
    while (*endptr == ' ' || *endptr == '\t' || *endptr == '\r') endptr++;
    if (endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
        printf(" [!] Error: Invalid integer. Please try again.\n");
        return false;
    }
    *output = (int)val;
    return true;
}

bool get_double_input(const char *prompt, double *output) {
    char buffer[128];
    printf("%s", prompt);
    if (!fgets(buffer, sizeof(buffer), stdin)) {
        return false;
    }
    char *endptr;
    double val = strtod(buffer, &endptr);
    while (*endptr == ' ' || *endptr == '\t' || *endptr == '\r') endptr++;
    if (endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
        printf(" [!] Error: Invalid numerical value. Please try again.\n");
        return false;
    }
    *output = val;
    return true;
}

/* ============================================================================
 * SECTION 2: ARITHMETIC & BASIC MATHEMATICS
 * ============================================================================ */

void run_arithmetic_menu(void) {
    int choice = 0;
    while (1) {
        print_header("ARITHMETIC & BASIC MATHEMATICS");
        printf(" 1. Addition (a + b)\n");
        printf(" 2. Subtraction (a - b)\n");
        printf(" 3. Multiplication (a * b)\n");
        printf(" 4. Division (a / b)\n");
        printf(" 5. Power (a ^ b)\n");
        printf(" 6. Square Root (sqrt(a))\n");
        printf(" 7. Modulo (a %% b) [Integers]\n");
        printf(" 0. Back to Main Menu\n");
        print_divider('-', 60);

        if (!get_int_input(" Select option (0-7): ", &choice)) continue;
        if (choice == 0) break;

        double a = 0.0, b = 0.0;
        switch (choice) {
            case 1:
                if (get_double_input(" Enter number (a): ", &a) && get_double_input(" Enter number (b): ", &b))
                    printf("\n [✓] Result: %.6g + %.6g = %.6g\n", a, b, a + b);
                break;
            case 2:
                if (get_double_input(" Enter number (a): ", &a) && get_double_input(" Enter number (b): ", &b))
                    printf("\n [✓] Result: %.6g - %.6g = %.6g\n", a, b, a - b);
                break;
            case 3:
                if (get_double_input(" Enter number (a): ", &a) && get_double_input(" Enter number (b): ", &b))
                    printf("\n [✓] Result: %.6g * %.6g = %.6g\n", a, b, a * b);
                break;
            case 4:
                if (get_double_input(" Enter numerator (a): ", &a) && get_double_input(" Enter denominator (b): ", &b)) {
                    if (b == 0.0) {
                        printf(" [!] Error: Division by zero is undefined!\n");
                    } else {
                        printf("\n [✓] Result: %.6g / %.6g = %.6g\n", a, b, a / b);
                    }
                }
                break;
            case 5:
                if (get_double_input(" Enter base (a): ", &a) && get_double_input(" Enter exponent (b): ", &b))
                    printf("\n [✓] Result: %.6g ^ %.6g = %.6g\n", a, b, pow(a, b));
                break;
            case 6:
                if (get_double_input(" Enter value (a): ", &a)) {
                    if (a < 0.0) {
                        printf(" [!] Error: Square root of a negative number is undefined for real numbers.\n");
                    } else {
                        printf("\n [✓] Result: sqrt(%.6g) = %.6g\n", a, sqrt(a));
                    }
                }
                break;
            case 7: {
                int ia = 0, ib = 0;
                if (get_int_input(" Enter integer dividend (a): ", &ia) && get_int_input(" Enter integer divisor (b): ", &ib)) {
                    if (ib == 0) {
                        printf(" [!] Error: Modulo by zero is undefined!\n");
                    } else {
                        printf("\n [✓] Result: %d %% %d = %d\n", ia, ib, ia % ib);
                    }
                }
                break;
            }
            default:
                printf(" [!] Error: Invalid selection.\n");
                break;
        }
        wait_for_enter();
    }
}

/* ============================================================================
 * SECTION 3: ELECTRICAL CALCULATIONS (OHM'S LAW & POWER)
 * ============================================================================ */

void run_ohms_law_menu(void) {
    int choice = 0;
    while (1) {
        print_header("OHM'S LAW CALCULATOR (V = I * R)");
        printf(" 1. Calculate Voltage    [ V = I * R ]\n");
        printf(" 2. Calculate Current    [ I = V / R ]\n");
        printf(" 3. Calculate Resistance [ R = V / I ]\n");
        printf(" 0. Back to Main Menu\n");
        print_divider('-', 60);

        if (!get_int_input(" Select option (0-3): ", &choice)) continue;
        if (choice == 0) break;

        double v = 0.0, i = 0.0, r = 0.0;
        switch (choice) {
            case 1:
                if (get_double_input(" Enter Current (I) in Amperes [A]: ", &i) &&
                    get_double_input(" Enter Resistance (R) in Ohms [Ω]: ", &r)) {
                    printf("\n [✓] Calculated Voltage (V): %.6g Volts (V)\n", i * r);
                }
                break;
            case 2:
                if (get_double_input(" Enter Voltage (V) in Volts [V]: ", &v) &&
                    get_double_input(" Enter Resistance (R) in Ohms [Ω]: ", &r)) {
                    if (r == 0.0) {
                        printf(" [!] Error: Resistance cannot be 0 Ohms (short circuit)!\n");
                    } else {
                        double cur = v / r;
                        printf("\n [✓] Calculated Current (I): %.6g Amperes (A)\n", cur);
                        printf("     Equivalent in mA:      %.6g mA\n", cur * 1000.0);
                    }
                }
                break;
            case 3:
                if (get_double_input(" Enter Voltage (V) in Volts [V]: ", &v) &&
                    get_double_input(" Enter Current (I) in Amperes [A]: ", &i)) {
                    if (i == 0.0) {
                        printf(" [!] Error: Current cannot be 0 Amperes (open circuit)!\n");
                    } else {
                        double res = v / i;
                        printf("\n [✓] Calculated Resistance (R): %.6g Ohms (Ω)\n", res);
                        printf("     Equivalent in kΩ:          %.6g kΩ\n", res / 1000.0);
                    }
                }
                break;
            default:
                printf(" [!] Error: Invalid selection.\n");
                break;
        }
        wait_for_enter();
    }
}

void run_power_menu(void) {
    int choice = 0;
    while (1) {
        print_header("ELECTRICAL POWER CALCULATOR (P = V * I)");
        printf(" 1. Calculate Power using Voltage and Current (P = V * I)\n");
        printf(" 2. Calculate Power using Current and Resistance (P = I^2 * R)\n");
        printf(" 3. Calculate Power using Voltage and Resistance (P = V^2 / R)\n");
        printf(" 0. Back to Main Menu\n");
        print_divider('-', 60);

        if (!get_int_input(" Select option (0-3): ", &choice)) continue;
        if (choice == 0) break;

        double v = 0.0, i = 0.0, r = 0.0, p = 0.0;
        switch (choice) {
            case 1:
                if (get_double_input(" Enter Voltage (V) in Volts [V]: ", &v) &&
                    get_double_input(" Enter Current (I) in Amperes [A]: ", &i)) {
                    p = v * i;
                    printf("\n [✓] Dissipated Power (P): %.6g Watts (W)\n", p);
                    printf("     Equivalent in kW:     %.6g kW\n", p / 1000.0);
                }
                break;
            case 2:
                if (get_double_input(" Enter Current (I) in Amperes [A]: ", &i) &&
                    get_double_input(" Enter Resistance (R) in Ohms [Ω]: ", &r)) {
                    p = i * i * r;
                    printf("\n [✓] Dissipated Power (P): %.6g Watts (W)\n", p);
                    printf("     Equivalent in kW:     %.6g kW\n", p / 1000.0);
                }
                break;
            case 3:
                if (get_double_input(" Enter Voltage (V) in Volts [V]: ", &v) &&
                    get_double_input(" Enter Resistance (R) in Ohms [Ω]: ", &r)) {
                    if (r == 0.0) {
                        printf(" [!] Error: Resistance cannot be 0 Ohms!\n");
                    } else {
                        p = (v * v) / r;
                        printf("\n [✓] Dissipated Power (P): %.6g Watts (W)\n", p);
                        printf("     Equivalent in kW:     %.6g kW\n", p / 1000.0);
                    }
                }
                break;
            default:
                printf(" [!] Error: Invalid selection.\n");
                break;
        }
        wait_for_enter();
    }
}

/* ============================================================================
 * SECTION 4: INSTRUMENTATION UNIT CONVERSIONS
 * ============================================================================ */

void run_temperature_menu(void) {
    int choice = 0;
    while (1) {
        print_header("TEMPERATURE CONVERTER");
        printf(" 1. Celsius    --> Fahrenheit\n");
        printf(" 2. Fahrenheit --> Celsius\n");
        printf(" 3. Celsius    --> Kelvin\n");
        printf(" 4. Kelvin     --> Celsius\n");
        printf(" 5. Fahrenheit --> Kelvin\n");
        printf(" 6. Kelvin     --> Fahrenheit\n");
        printf(" 0. Back to Main Menu\n");
        print_divider('-', 60);

        if (!get_int_input(" Select conversion (0-6): ", &choice)) continue;
        if (choice == 0) break;

        double val = 0.0;
        if (!get_double_input(" Enter temperature value: ", &val)) continue;

        switch (choice) {
            case 1: printf("\n [✓] %.4f °C = %.4f °F\n", val, (val * 9.0 / 5.0) + 32.0); break;
            case 2: printf("\n [✓] %.4f °F = %.4f °C\n", val, (val - 32.0) * 5.0 / 9.0); break;
            case 3: printf("\n [✓] %.4f °C = %.4f K\n", val, val + 273.15); break;
            case 4: printf("\n [✓] %.4f K = %.4f °C\n", val, val - 273.15); break;
            case 5: printf("\n [✓] %.4f °F = %.4f K\n", val, (val - 32.0) * 5.0 / 9.0 + 273.15); break;
            case 6: printf("\n [✓] %.4f K = %.4f °F\n", val, (val - 273.15) * 9.0 / 5.0 + 32.0); break;
            default: printf(" [!] Error: Invalid selection.\n"); break;
        }
        wait_for_enter();
    }
}

void run_pressure_menu(void) {
    int choice = 0;
    while (1) {
        print_header("INSTRUMENTATION PRESSURE CONVERTER");
        printf(" 1. Bar                  --> Pascal, kPa, PSI, mmHg\n");
        printf(" 2. PSI (Pounds/sq inch) --> Pascal, kPa, Bar, mmHg\n");
        printf(" 3. Pascal (Pa)          --> kPa, Bar, PSI, mmHg\n");
        printf(" 4. mmHg (Torr)          --> Pascal, Bar, PSI\n");
        printf(" 0. Back to Unit Conversion Menu\n");
        print_divider('-', 60);

        if (!get_int_input(" Select source unit (0-4): ", &choice)) continue;
        if (choice == 0) break;

        double input_val = 0.0;
        if (!get_double_input(" Enter pressure value: ", &input_val)) continue;

        double pa = 0.0;
        switch (choice) {
            case 1: pa = input_val * 100000.0; break;
            case 2: pa = input_val * 6894.757293168; break;
            case 3: pa = input_val; break;
            case 4: pa = input_val * 133.322387415; break;
            default:
                printf(" [!] Error: Invalid selection.\n");
                wait_for_enter();
                continue;
        }

        printf("\n [✓] Equivalent Pressures across Industrial Units:\n");
        print_divider('-', 45);
        printf("  - Pascal (Pa):       %.4f Pa\n", pa);
        printf("  - Kilopascal (kPa):  %.4f kPa\n", pa / 1000.0);
        printf("  - Bar:               %.6f bar\n", pa / 100000.0);
        printf("  - PSI:               %.4f psi\n", pa / 6894.757293168);
        printf("  - mmHg (Torr):       %.2f mmHg\n", pa / 133.322387415);
        printf("  - Standard Atm:      %.4f atm\n", pa / 101325.0);
        print_divider('-', 45);
        wait_for_enter();
    }
}

void run_unit_conversion_menu(void) {
    int choice = 0;
    while (1) {
        print_header("UNIT CONVERSION HUB");
        printf(" 1. Temperature Conversion (Celsius, Fahrenheit, Kelvin)\n");
        printf(" 2. Pressure Conversion (Bar, PSI, Pascal, kPa, mmHg)\n");
        printf(" 0. Back to Main Menu\n");
        print_divider('-', 60);

        if (!get_int_input(" Select category (0-2): ", &choice)) continue;
        if (choice == 0) break;

        if (choice == 1) run_temperature_menu();
        else if (choice == 2) run_pressure_menu();
        else {
            printf(" [!] Invalid category choice.\n");
            wait_for_enter();
        }
    }
}

/* ============================================================================
 * SECTION 5: RPM, SENSOR ANALYTICS & 4-20mA SCALING
 * ============================================================================ */

void run_rpm_menu(void) {
    int choice = 0;
    while (1) {
        print_header("RPM & MOTOR SPEED CALCULATOR");
        printf(" 1. Digital Tachometer / Optical Pulse Sensor\n");
        printf(" 2. AC Synchronous Motor Speed (Ns = 120 * f / P)\n");
        printf(" 3. Linear Conveyor / Roller Speed to RPM\n");
        printf(" 0. Back to Main Menu\n");
        print_divider('-', 60);

        if (!get_int_input(" Select calculation (0-3): ", &choice)) continue;
        if (choice == 0) break;

        double rpm = 0.0;
        switch (choice) {
            case 1: {
                double pps = 0.0;
                int ppr = 1;
                if (get_double_input(" Enter pulse frequency (pulses/sec or Hz): ", &pps) &&
                    get_int_input(" Enter encoder resolution (pulses/revolution): ", &ppr)) {
                    if (ppr <= 0 || pps < 0.0) {
                        printf(" [!] Error: PPR must be > 0 and pulse frequency >= 0.\n");
                    } else {
                        rpm = (pps * 60.0) / (double)ppr;
                        printf("\n [✓] Rotational Speed: %.2f RPM\n", rpm);
                        printf("     Frequency:        %.2f Rev/sec (Hz)\n", rpm / 60.0);
                        printf("     Angular Velocity: %.4f rad/s\n", (rpm * 2.0 * M_PI) / 60.0);
                    }
                }
                break;
            }
            case 2: {
                double freq = 50.0;
                int poles = 4;
                if (get_double_input(" Enter supply frequency in Hz [50 or 60]: ", &freq) &&
                    get_int_input(" Enter number of poles [even, e.g. 2, 4, 6, 8]: ", &poles)) {
                    if (poles <= 0 || poles % 2 != 0 || freq <= 0.0) {
                        printf(" [!] Error: Number of poles must be a positive even integer.\n");
                    } else {
                        rpm = (120.0 * freq) / (double)poles;
                        printf("\n [✓] Synchronous Speed (Ns): %.2f RPM\n", rpm);
                    }
                }
                break;
            }
            case 3: {
                double vel = 0.0, dia = 0.0;
                if (get_double_input(" Enter linear velocity (m/s): ", &vel) &&
                    get_double_input(" Enter wheel/roller diameter (meters): ", &dia)) {
                    if (dia <= 0.0 || vel < 0.0) {
                        printf(" [!] Error: Diameter must be strictly > 0.\n");
                    } else {
                        rpm = (vel * 60.0) / (M_PI * dia);
                        printf("\n [✓] Shaft Rotational Speed: %.2f RPM\n", rpm);
                    }
                }
                break;
            }
            default:
                printf(" [!] Error: Invalid selection.\n");
                break;
        }
        wait_for_enter();
    }
}

void run_signal_scaling_menu(void) {
    int choice = 0;
    while (1) {
        print_header("4-20 mA INDUSTRIAL PROCESS SIGNAL SCALER");
        printf(" 1. Convert 4-20 mA Loop Current -> Process Variable (PV)\n");
        printf(" 2. Convert Process Variable (PV) -> 4-20 mA Loop Current\n");
        printf(" 0. Back to Main Menu\n");
        print_divider('-', 60);

        if (!get_int_input(" Select option (0-2): ", &choice)) continue;
        if (choice == 0) break;

        double lrv = 0.0, urv = 100.0;
        printf("\n Transmitter Calibration Range:\n");
        if (!get_double_input(" - Enter Lower Range Value (LRV / 0%%): ", &lrv) ||
            !get_double_input(" - Enter Upper Range Value (URV / 100%%): ", &urv)) {
            continue;
        }

        if (lrv == urv) {
            printf(" [!] Error: URV cannot equal LRV (zero span).\n");
            wait_for_enter();
            continue;
        }

        if (choice == 1) {
            double ma = 0.0;
            if (get_double_input(" Enter signal current (4.0 to 20.0 mA): ", &ma)) {
                if (ma < 3.5 || ma > 21.0) {
                    printf(" [!] Warning: Current %.2f mA is outside typical 4-20 mA range!\n", ma);
                }
                double pv = lrv + ((ma - 4.0) / 16.0) * (urv - lrv);
                double pct = ((ma - 4.0) / 16.0) * 100.0;
                printf("\n [✓] Scaled Process Variable (PV): %.4f\n", pv);
                printf("     Process Percentage:          %.2f %%\n", pct);
            }
        } else if (choice == 2) {
            double pv = 0.0;
            if (get_double_input(" Enter Process Variable (PV) value: ", &pv)) {
                double ma = 4.0 + ((pv - lrv) / (urv - lrv)) * 16.0;
                double pct = ((pv - lrv) / (urv - lrv)) * 100.0;
                printf("\n [✓] Output Current Signal: %.4f mA\n", ma);
                printf("     Process Percentage:    %.2f %%\n", pct);
            }
        } else {
            printf(" [!] Error: Invalid selection.\n");
        }
        wait_for_enter();
    }
}

void run_sensor_analytics_menu(void) {
    print_header("SENSOR DATA ANALYTICS & TRANSDUCER STATS");
    printf(" Analyze multiple sensor readings (e.g. pressure samples, RTD temperatures).\n");
    print_divider('-', 60);

    int count = 0;
    if (!get_int_input(" Enter number of sensor samples to analyze (2 to 100): ", &count)) {
        wait_for_enter();
        return;
    }

    if (count < 2 || count > 100) {
        printf(" [!] Please choose between 2 and 100 samples.\n");
        wait_for_enter();
        return;
    }

    double *readings = (double *)malloc((size_t)count * sizeof(double));
    if (!readings) {
        printf(" [!] Memory allocation failed!\n");
        wait_for_enter();
        return;
    }

    printf("\n Enter %d sensor readings:\n", count);
    for (int i = 0; i < count; i++) {
        char prompt[64];
        snprintf(prompt, sizeof(prompt), "  Reading [%d/%d]: ", i + 1, count);
        while (!get_double_input(prompt, &readings[i])) {
            /* retry */
        }
    }

    double min = readings[0], max = readings[0], sum = 0.0;
    for (int i = 0; i < count; i++) {
        if (readings[i] < min) min = readings[i];
        if (readings[i] > max) max = readings[i];
        sum += readings[i];
    }
    double mean = sum / count;
    double var_sum = 0.0;
    for (int i = 0; i < count; i++) {
        double diff = readings[i] - mean;
        var_sum += diff * diff;
    }
    double std_dev = sqrt(var_sum / (count - 1));

    printf("\n [✓] SENSOR STATISTICAL ANALYSIS RESULTS:\n");
    print_divider('-', 45);
    printf("  - Sample Count (N):       %d\n", count);
    printf("  - Minimum Reading:        %.4f\n", min);
    printf("  - Maximum Reading:        %.4f\n", max);
    printf("  - Span / Dynamic Range:   %.4f\n", max - min);
    printf("  - Average (Mean):         %.4f\n", mean);
    printf("  - Standard Deviation (σ): %.4f\n", std_dev);
    print_divider('-', 45);

    free(readings);
    wait_for_enter();
}

/* ============================================================================
 * SECTION 6: MASTER ENTRY POINT
 * ============================================================================ */

int main(void) {
    int choice = -1;

    while (1) {
        printf("\n");
        print_divider('=', 64);
        printf("     ENGINEERING CALCULATOR IN C - INSTRUMENTATION EDITION     \n");
        printf("       [ Designed for Instrumentation & Control Engineers ]     \n");
        print_divider('=', 64);
        printf(" 1. 🔢 Basic Arithmetic & Math Operations\n");
        printf(" 2. 🌡️  Temperature Conversion (Celsius, Fahrenheit, Kelvin)\n");
        printf(" 3. ⚡ Ohm's Law Calculator (V = I * R)\n");
        printf(" 4. 🔌 Electrical Power Calculator (P = V*I, I^2*R, V^2/R)\n");
        printf(" 5. 📐 Unit Conversion (Pressure: Bar, PSI, Pa, mmHg)\n");
        printf(" 6. ⚙️  RPM & Motor Speed Calculation (Tachometer, AC Motor)\n");
        printf(" 7. 📊 Sensor Readings Analytics (Mean, Min, Max, Std Dev)\n");
        printf(" 8. 🎛️  4-20 mA Process Signal Scaler (Current Loop to PV)\n");
        printf(" 0. 🚪 Exit\n");
        print_divider('-', 64);

        if (!get_int_input(" Enter your choice [0-8]: ", &choice)) continue;

        switch (choice) {
            case 1: run_arithmetic_menu(); break;
            case 2: run_temperature_menu(); break;
            case 3: run_ohms_law_menu(); break;
            case 4: run_power_menu(); break;
            case 5: run_unit_conversion_menu(); break;
            case 6: run_rpm_menu(); break;
            case 7: run_sensor_analytics_menu(); break;
            case 8: run_signal_scaling_menu(); break;
            case 0:
                print_divider('=', 64);
                printf("  Thank you for using Engineering Calculator in C!\n");
                printf("  Happy Engineering & Good Luck with your ICE Journey!\n");
                print_divider('=', 64);
                printf("\n");
                return 0;
            default:
                printf(" [!] Invalid option. Please select a number between 0 and 8.\n");
                wait_for_enter();
                break;
        }
    }
    return 0;
}
