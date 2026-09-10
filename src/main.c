#include <stdio.h>
#include <stdlib.h>
#include "../include/calculator.h"
#include "../include/electrical.h"
#include "../include/units.h"
#include "../include/ice_sensors.h"
#include "../include/utils.h"

static void print_banner(void) {
    printf("\n");
    print_divider('=', 64);
    printf("     ENGINEERING CALCULATOR IN C - INSTRUMENTATION EDITION     \n");
    printf("       [ Designed for Instrumentation & Control Engineers ]     \n");
    print_divider('=', 64);
}

int main(void) {
    int choice = -1;

    while (1) {
        print_banner();
        printf(" 1. 🔢 Basic Arithmetic & Math Operations\n");
        printf(" 2. 🌡️  Temperature Conversion (Celsius, Fahrenheit, Kelvin)\n");
        printf(" 3. ⚡ Ohm's Law Calculator (V = I * R)\n");
        printf(" 4. 🔌 Electrical Power Calculator (P = V*I, I^2*R, V^2/R)\n");
        printf(" 5. 📐 Unit Conversion (Pressure: Bar, PSI, Pa, mmHg & Length)\n");
        printf(" 6. ⚙️  RPM & Motor Speed Calculation (Tachometer, AC Motor)\n");
        printf(" 7. 📊 Sensor Readings Analytics (Mean, Min, Max, Std Dev)\n");
        printf(" 8. 🎛️  4-20 mA Process Signal Scaler (Current Loop to PV)\n");
        printf(" 0. 🚪 Exit\n");
        print_divider('-', 64);

        if (!get_int_input(" Enter your choice [0-8]: ", &choice)) {
            continue;
        }

        switch (choice) {
            case 1:
                run_arithmetic_menu();
                break;
            case 2:
                run_temperature_menu();
                break;
            case 3:
                run_ohms_law_menu();
                break;
            case 4:
                run_power_menu();
                break;
            case 5:
                run_unit_conversion_menu();
                break;
            case 6:
                run_rpm_menu();
                break;
            case 7:
                run_sensor_analytics_menu();
                break;
            case 8:
                run_signal_scaling_menu();
                break;
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
