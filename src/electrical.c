#include <stdio.h>
#include <math.h>
#include "../include/electrical.h"
#include "../include/utils.h"

/* --- Ohm's Law Implementations --- */

double ohms_law_voltage(double current, double resistance) {
    return current * resistance;
}

bool ohms_law_current(double voltage, double resistance, double *current) {
    if (resistance == 0.0) {
        return false; /* Resistance cannot be 0 for finite current */
    }
    *current = voltage / resistance;
    return true;
}

bool ohms_law_resistance(double voltage, double current, double *resistance) {
    if (current == 0.0) {
        return false; /* Zero current implies infinite resistance / open circuit */
    }
    *resistance = voltage / current;
    return true;
}

/* --- Electrical Power Implementations --- */

double power_from_vi(double voltage, double current) {
    return voltage * current;
}

double power_from_ir(double current, double resistance) {
    return current * current * resistance;
}

bool power_from_vr(double voltage, double resistance, double *power) {
    if (resistance == 0.0) {
        return false;
    }
    *power = (voltage * voltage) / resistance;
    return true;
}

/* --- Menu Interfaces --- */

void run_ohms_law_menu(void) {
    int choice = 0;
    while (1) {
        print_header("OHM'S LAW CALCULATOR (V = I * R)");
        printf(" 1. Calculate Voltage    [ V = I * R ]\n");
        printf(" 2. Calculate Current    [ I = V / R ]\n");
        printf(" 3. Calculate Resistance [ R = V / I ]\n");
        printf(" 0. Back to Main Menu\n");
        print_divider('-', 58);

        if (!get_int_input(" Select option (0-3): ", &choice)) {
            continue;
        }

        if (choice == 0) {
            break;
        }

        double v = 0.0, i = 0.0, r = 0.0, result = 0.0;

        switch (choice) {
            case 1:
                if (get_double_input(" Enter Current (I) in Amperes [A]: ", &i) &&
                    get_double_input(" Enter Resistance (R) in Ohms [Ω]: ", &r)) {
                    v = ohms_law_voltage(i, r);
                    printf("\n [✓] Calculated Voltage (V): %.6g Volts (V)\n", v);
                }
                break;
            case 2:
                if (get_double_input(" Enter Voltage (V) in Volts [V]: ", &v) &&
                    get_double_input(" Enter Resistance (R) in Ohms [Ω]: ", &r)) {
                    if (ohms_law_current(v, r, &result)) {
                        printf("\n [✓] Calculated Current (I): %.6g Amperes (A)\n", result);
                        printf("     Equivalent in mA:      %.6g mA\n", result * 1000.0);
                    } else {
                        printf(" [!] Error: Resistance cannot be 0 Ohms (short circuit)!\n");
                    }
                }
                break;
            case 3:
                if (get_double_input(" Enter Voltage (V) in Volts [V]: ", &v) &&
                    get_double_input(" Enter Current (I) in Amperes [A]: ", &i)) {
                    if (ohms_law_resistance(v, i, &result)) {
                        printf("\n [✓] Calculated Resistance (R): %.6g Ohms (Ω)\n", result);
                        printf("     Equivalent in kΩ:          %.6g kΩ\n", result / 1000.0);
                    } else {
                        printf(" [!] Error: Current cannot be 0 Amperes (open circuit)!\n");
                    }
                }
                break;
            default:
                printf(" [!] Error: Invalid choice. Choose between 0 and 3.\n");
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
        print_divider('-', 58);

        if (!get_int_input(" Select option (0-3): ", &choice)) {
            continue;
        }

        if (choice == 0) {
            break;
        }

        double v = 0.0, i = 0.0, r = 0.0, p = 0.0;

        switch (choice) {
            case 1:
                if (get_double_input(" Enter Voltage (V) in Volts [V]: ", &v) &&
                    get_double_input(" Enter Current (I) in Amperes [A]: ", &i)) {
                    p = power_from_vi(v, i);
                    printf("\n [✓] Dissipated Power (P): %.6g Watts (W)\n", p);
                    printf("     Equivalent in kW:     %.6g kW\n", p / 1000.0);
                    printf("     Equivalent in mW:     %.6g mW\n", p * 1000.0);
                }
                break;
            case 2:
                if (get_double_input(" Enter Current (I) in Amperes [A]: ", &i) &&
                    get_double_input(" Enter Resistance (R) in Ohms [Ω]: ", &r)) {
                    p = power_from_ir(i, r);
                    printf("\n [✓] Dissipated Power (P): %.6g Watts (W)\n", p);
                    printf("     Equivalent in kW:     %.6g kW\n", p / 1000.0);
                }
                break;
            case 3:
                if (get_double_input(" Enter Voltage (V) in Volts [V]: ", &v) &&
                    get_double_input(" Enter Resistance (R) in Ohms [Ω]: ", &r)) {
                    if (power_from_vr(v, r, &p)) {
                        printf("\n [✓] Dissipated Power (P): %.6g Watts (W)\n", p);
                        printf("     Equivalent in kW:     %.6g kW\n", p / 1000.0);
                    } else {
                        printf(" [!] Error: Resistance cannot be 0 Ohms!\n");
                    }
                }
                break;
            default:
                printf(" [!] Error: Invalid choice. Choose between 0 and 3.\n");
                break;
        }

        wait_for_enter();
    }
}
