#include <stdio.h>
#include "../include/units.h"
#include "../include/utils.h"

/* --- Temperature Conversions --- */

double celsius_to_fahrenheit(double c) {
    return (c * 9.0 / 5.0) + 32.0;
}

double fahrenheit_to_celsius(double f) {
    return (f - 32.0) * 5.0 / 9.0;
}

double celsius_to_kelvin(double c) {
    return c + 273.15;
}

double kelvin_to_celsius(double k) {
    return k - 273.15;
}

double fahrenheit_to_kelvin(double f) {
    return (f - 32.0) * 5.0 / 9.0 + 273.15;
}

double kelvin_to_fahrenheit(double k) {
    return (k - 273.15) * 9.0 / 5.0 + 32.0;
}

/* --- Pressure Conversions (Base: Pascal) --- */

double bar_to_pascal(double bar) {
    return bar * 100000.0;
}

double pascal_to_bar(double pa) {
    return pa / 100000.0;
}

double psi_to_pascal(double psi) {
    return psi * 6894.757293168;
}

double pascal_to_psi(double pa) {
    return pa / 6894.757293168;
}

double mmhg_to_pascal(double mmhg) {
    return mmhg * 133.322387415;
}

double pascal_to_mmhg(double pa) {
    return pa / 133.322387415;
}

/* --- Menus --- */

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
        print_divider('-', 58);

        if (!get_int_input(" Select conversion (0-6): ", &choice)) {
            continue;
        }

        if (choice == 0) {
            break;
        }

        double val = 0.0;
        if (!get_double_input(" Enter temperature value: ", &val)) {
            continue;
        }

        switch (choice) {
            case 1:
                printf("\n [✓] %.4f °C = %.4f °F\n", val, celsius_to_fahrenheit(val));
                break;
            case 2:
                printf("\n [✓] %.4f °F = %.4f °C\n", val, fahrenheit_to_celsius(val));
                break;
            case 3:
                printf("\n [✓] %.4f °C = %.4f K\n", val, celsius_to_kelvin(val));
                break;
            case 4:
                printf("\n [✓] %.4f K = %.4f °C\n", val, kelvin_to_celsius(val));
                break;
            case 5:
                printf("\n [✓] %.4f °F = %.4f K\n", val, fahrenheit_to_kelvin(val));
                break;
            case 6:
                printf("\n [✓] %.4f K = %.4f °F\n", val, kelvin_to_fahrenheit(val));
                break;
            default:
                printf(" [!] Error: Invalid selection.\n");
                break;
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
        print_divider('-', 58);

        if (!get_int_input(" Select source unit (0-4): ", &choice)) {
            continue;
        }

        if (choice == 0) {
            break;
        }

        double input_val = 0.0;
        if (!get_double_input(" Enter pressure value: ", &input_val)) {
            continue;
        }

        double pa = 0.0;
        switch (choice) {
            case 1:
                pa = bar_to_pascal(input_val);
                break;
            case 2:
                pa = psi_to_pascal(input_val);
                break;
            case 3:
                pa = input_val;
                break;
            case 4:
                pa = mmhg_to_pascal(input_val);
                break;
            default:
                printf(" [!] Error: Invalid selection.\n");
                wait_for_enter();
                continue;
        }

        printf("\n [✓] Equivalent Pressures across Industrial Units:\n");
        print_divider('-', 45);
        printf("  - Pascal (Pa):       %.4f Pa\n", pa);
        printf("  - Kilopascal (kPa):  %.4f kPa\n", pa / 1000.0);
        printf("  - Bar:               %.6f bar\n", pascal_to_bar(pa));
        printf("  - PSI:               %.4f psi\n", pascal_to_psi(pa));
        printf("  - mmHg (Torr):       %.2f mmHg\n", pascal_to_mmhg(pa));
        printf("  - Standard Atm (atm):%.4f atm\n", pa / 101325.0);
        print_divider('-', 45);

        wait_for_enter();
    }
}

static void run_length_menu(void) {
    int choice = 0;
    while (1) {
        print_header("LENGTH & DIMENSIONAL CONVERTER");
        printf(" 1. Meters (m)       --> cm, mm, inches, feet\n");
        printf(" 2. Millimeters (mm) --> m, cm, inches, feet\n");
        printf(" 3. Inches (in)      --> m, cm, mm, feet\n");
        printf(" 4. Feet (ft)        --> m, cm, inches\n");
        printf(" 0. Back to Unit Conversion Menu\n");
        print_divider('-', 58);

        if (!get_int_input(" Select option (0-4): ", &choice)) {
            continue;
        }

        if (choice == 0) {
            break;
        }

        double val = 0.0;
        if (!get_double_input(" Enter length value: ", &val)) {
            continue;
        }

        double meters = 0.0;
        switch (choice) {
            case 1: meters = val; break;
            case 2: meters = val / 1000.0; break;
            case 3: meters = val * 0.0254; break;
            case 4: meters = val * 0.3048; break;
            default:
                printf(" [!] Invalid selection.\n");
                wait_for_enter();
                continue;
        }

        printf("\n [✓] Dimensional Equivalents:\n");
        print_divider('-', 45);
        printf("  - Meters (m):       %.6g m\n", meters);
        printf("  - Centimeters (cm): %.6g cm\n", meters * 100.0);
        printf("  - Millimeters (mm): %.6g mm\n", meters * 1000.0);
        printf("  - Inches (in):      %.4f in\n", meters / 0.0254);
        printf("  - Feet (ft):        %.4f ft\n", meters / 0.3048);
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
        printf(" 3. Length & Dimension Conversion (m, mm, in, ft)\n");
        printf(" 0. Back to Main Menu\n");
        print_divider('-', 58);

        if (!get_int_input(" Select category (0-3): ", &choice)) {
            continue;
        }

        if (choice == 0) {
            break;
        }

        switch (choice) {
            case 1:
                run_temperature_menu();
                break;
            case 2:
                run_pressure_menu();
                break;
            case 3:
                run_length_menu();
                break;
            default:
                printf(" [!] Invalid category choice.\n");
                wait_for_enter();
                break;
        }
    }
}
