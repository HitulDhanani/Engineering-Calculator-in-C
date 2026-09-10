#include <stdio.h>
#include <math.h>
#include "../include/calculator.h"
#include "../include/utils.h"

double add(double a, double b) {
    return a + b;
}

double subtract(double a, double b) {
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

bool divide(double a, double b, double *result) {
    if (b == 0.0) {
        return false; /* Prevent division by zero */
    }
    *result = a / b;
    return true;
}

double power(double base, double exponent) {
    return pow(base, exponent);
}

bool square_root(double val, double *result) {
    if (val < 0.0) {
        return false; /* Prevent imaginary results in real calculator */
    }
    *result = sqrt(val);
    return true;
}

bool modulo_op(long long a, long long b, long long *result) {
    if (b == 0) {
        return false;
    }
    *result = a % b;
    return true;
}

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
        print_divider('-', 58);

        if (!get_int_input(" Select option (0-7): ", &choice)) {
            continue;
        }

        if (choice == 0) {
            break;
        }

        double a = 0.0, b = 0.0, res = 0.0;

        switch (choice) {
            case 1:
                if (get_double_input(" Enter first number (a): ", &a) &&
                    get_double_input(" Enter second number (b): ", &b)) {
                    printf(" Result: %.6g + %.6g = %.6g\n", a, b, add(a, b));
                }
                break;
            case 2:
                if (get_double_input(" Enter first number (a): ", &a) &&
                    get_double_input(" Enter second number (b): ", &b)) {
                    printf(" Result: %.6g - %.6g = %.6g\n", a, b, subtract(a, b));
                }
                break;
            case 3:
                if (get_double_input(" Enter first number (a): ", &a) &&
                    get_double_input(" Enter second number (b): ", &b)) {
                    printf(" Result: %.6g * %.6g = %.6g\n", a, b, multiply(a, b));
                }
                break;
            case 4:
                if (get_double_input(" Enter numerator (a): ", &a) &&
                    get_double_input(" Enter denominator (b): ", &b)) {
                    if (divide(a, b, &res)) {
                        printf(" Result: %.6g / %.6g = %.6g\n", a, b, res);
                    } else {
                        printf(" [!] Error: Division by zero is undefined!\n");
                    }
                }
                break;
            case 5:
                if (get_double_input(" Enter base (a): ", &a) &&
                    get_double_input(" Enter exponent (b): ", &b)) {
                    printf(" Result: %.6g ^ %.6g = %.6g\n", a, b, power(a, b));
                }
                break;
            case 6:
                if (get_double_input(" Enter value (a): ", &a)) {
                    if (square_root(a, &res)) {
                        printf(" Result: sqrt(%.6g) = %.6g\n", a, res);
                    } else {
                        printf(" [!] Error: Square root of a negative number is undefined for real numbers.\n");
                    }
                }
                break;
            case 7: {
                int int_a = 0, int_b = 0;
                long long mod_res = 0;
                if (get_int_input(" Enter integer dividend (a): ", &int_a) &&
                    get_int_input(" Enter integer divisor (b): ", &int_b)) {
                    if (modulo_op(int_a, int_b, &mod_res)) {
                        printf(" Result: %d %% %d = %lld\n", int_a, int_b, mod_res);
                    } else {
                        printf(" [!] Error: Modulo by zero is undefined!\n");
                    }
                }
                break;
            }
            default:
                printf(" [!] Error: Invalid selection. Choose between 0 and 7.\n");
                break;
        }

        wait_for_enter();
    }
}
