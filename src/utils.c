#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/utils.h"

void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* Discard remaining characters in input stream */
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
    
    /* Skip trailing spaces */
    while (*endptr == ' ' || *endptr == '\t' || *endptr == '\r') {
        endptr++;
    }
    
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
    
    /* Skip trailing spaces */
    while (*endptr == ' ' || *endptr == '\t' || *endptr == '\r') {
        endptr++;
    }
    
    if (endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
        printf(" [!] Error: Invalid numerical value. Please try again.\n");
        return false;
    }
    
    *output = val;
    return true;
}

void wait_for_enter(void) {
    printf("\nPress [ENTER] to return to the menu...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* consume */
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
    print_divider('=', 58);
    printf("  %s\n", title);
    print_divider('=', 58);
}
