#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/ice_sensors.h"
#include "../include/utils.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/* --- RPM Implementations --- */

bool rpm_from_pulses(double pulses_per_sec, int pulses_per_rev, double *rpm) {
    if (pulses_per_rev <= 0 || pulses_per_sec < 0.0) {
        return false;
    }
    *rpm = (pulses_per_sec * 60.0) / (double)pulses_per_rev;
    return true;
}

bool rpm_sync_motor(double frequency, int poles, double *rpm) {
    if (poles <= 0 || poles % 2 != 0 || frequency <= 0.0) {
        return false; /* Poles must be a positive even integer */
    }
    *rpm = (120.0 * frequency) / (double)poles;
    return true;
}

bool rpm_from_linear_velocity(double linear_speed_mps, double diameter_m, double *rpm) {
    if (diameter_m <= 0.0 || linear_speed_mps < 0.0) {
        return false;
    }
    double circumference = M_PI * diameter_m;
    *rpm = (linear_speed_mps * 60.0) / circumference;
    return true;
}

/* --- 4-20 mA Process Signal Scaler --- */

bool current_to_engineering_units(double current_ma, double lrv, double urv, double *eng_val) {
    if (current_ma < 3.5 || current_ma > 21.0) {
        /* Standard industrial NAMUR NE43 bounds check (3.8mA - 20.5mA is valid) */
        printf(" [!] Warning: Current %.2f mA is outside typical 4-20 mA linear range!\n", current_ma);
    }
    *eng_val = lrv + ((current_ma - 4.0) / 16.0) * (urv - lrv);
    return true;
}

bool engineering_units_to_current(double eng_val, double lrv, double urv, double *current_ma) {
    if (urv == lrv) {
        return false; /* Span cannot be zero */
    }
    *current_ma = 4.0 + ((eng_val - lrv) / (urv - lrv)) * 16.0;
    return true;
}

/* --- Sensor Data Analytics --- */

bool compute_sensor_stats(const double *readings, int count, SensorStats *stats) {
    if (!readings || count <= 0 || !stats) {
        return false;
    }

    stats->count = count;
    stats->min = readings[0];
    stats->max = readings[0];
    double sum = 0.0;

    for (int i = 0; i < count; i++) {
        if (readings[i] < stats->min) stats->min = readings[i];
        if (readings[i] > stats->max) stats->max = readings[i];
        sum += readings[i];
    }

    stats->mean = sum / count;
    stats->span = stats->max - stats->min;

    /* Compute standard deviation (sample variance if count > 1) */
    double var_sum = 0.0;
    for (int i = 0; i < count; i++) {
        double diff = readings[i] - stats->mean;
        var_sum += diff * diff;
    }

    if (count > 1) {
        stats->std_dev = sqrt(var_sum / (count - 1));
    } else {
        stats->std_dev = 0.0;
    }

    return true;
}

/* --- Menu Interfaces --- */

void run_rpm_menu(void) {
    int choice = 0;
    while (1) {
        print_header("RPM & MOTOR SPEED CALCULATOR");
        printf(" 1. Digital Tachometer / Optical Pulse Sensor\n");
        printf(" 2. AC Synchronous Motor Speed (Ns = 120 * f / P)\n");
        printf(" 3. Linear Conveyor / Roller Speed to RPM\n");
        printf(" 0. Back to Main Menu\n");
        print_divider('-', 58);

        if (!get_int_input(" Select calculation (0-3): ", &choice)) {
            continue;
        }

        if (choice == 0) {
            break;
        }

        double rpm = 0.0;

        switch (choice) {
            case 1: {
                double pps = 0.0;
                int ppr = 1;
                if (get_double_input(" Enter pulse frequency (pulses per second / Hz): ", &pps) &&
                    get_int_input(" Enter encoder resolution (pulses per revolution): ", &ppr)) {
                    if (rpm_from_pulses(pps, ppr, &rpm)) {
                        printf("\n [✓] Rotational Speed: %.2f RPM\n", rpm);
                        printf("     Frequency:        %.2f Rev/sec (Hz)\n", rpm / 60.0);
                        printf("     Angular Velocity: %.4f rad/s\n", (rpm * 2.0 * M_PI) / 60.0);
                    } else {
                        printf(" [!] Error: Invalid pulse inputs (PPR must be > 0).\n");
                    }
                }
                break;
            }
            case 2: {
                double freq = 50.0;
                int poles = 4;
                if (get_double_input(" Enter supply frequency in Hz [e.g. 50 or 60]: ", &freq) &&
                    get_int_input(" Enter number of poles [must be even, e.g. 2, 4, 6, 8]: ", &poles)) {
                    if (rpm_sync_motor(freq, poles, &rpm)) {
                        printf("\n [✓] Synchronous Speed (Ns): %.2f RPM\n", rpm);
                    } else {
                        printf(" [!] Error: Number of poles must be a positive even integer.\n");
                    }
                }
                break;
            }
            case 3: {
                double vel = 0.0, dia = 0.0;
                if (get_double_input(" Enter linear velocity (m/s): ", &vel) &&
                    get_double_input(" Enter wheel/roller diameter (meters): ", &dia)) {
                    if (rpm_from_linear_velocity(vel, dia, &rpm)) {
                        printf("\n [✓] Shaft Rotational Speed: %.2f RPM\n", rpm);
                    } else {
                        printf(" [!] Error: Diameter must be strictly greater than 0.\n");
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
        print_divider('-', 58);

        if (!get_int_input(" Select option (0-2): ", &choice)) {
            continue;
        }

        if (choice == 0) {
            break;
        }

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
            double current_ma = 0.0, pv = 0.0;
            if (get_double_input(" Enter signal current (4.0 to 20.0 mA): ", &current_ma)) {
                current_to_engineering_units(current_ma, lrv, urv, &pv);
                double pct = ((current_ma - 4.0) / 16.0) * 100.0;
                printf("\n [✓] Scaled Process Variable (PV): %.4f\n", pv);
                printf("     Process Percentage:          %.2f %%\n", pct);
            }
        } else if (choice == 2) {
            double pv = 0.0, current_ma = 0.0;
            if (get_double_input(" Enter Process Variable (PV) value: ", &pv)) {
                if (engineering_units_to_current(pv, lrv, urv, &current_ma)) {
                    double pct = ((pv - lrv) / (urv - lrv)) * 100.0;
                    printf("\n [✓] Output Current Signal: %.4f mA\n", current_ma);
                    printf("     Process Percentage:    %.2f %%\n", pct);
                }
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
    print_divider('-', 58);

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
            /* retry until valid */
        }
    }

    SensorStats stats;
    if (compute_sensor_stats(readings, count, &stats)) {
        printf("\n [✓] SENSOR STATISTICAL ANALYSIS RESULTS:\n");
        print_divider('-', 45);
        printf("  - Sample Count (N):       %d\n", stats.count);
        printf("  - Minimum Reading:        %.4f\n", stats.min);
        printf("  - Maximum Reading:        %.4f\n", stats.max);
        printf("  - Span / Dynamic Range:   %.4f\n", stats.span);
        printf("  - Average (Mean):         %.4f\n", stats.mean);
        printf("  - Standard Deviation (σ): %.4f\n", stats.std_dev);
        print_divider('-', 45);
    }

    free(readings);
    wait_for_enter();
}
