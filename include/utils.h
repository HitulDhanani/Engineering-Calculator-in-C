#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

/* Safe Input Helpers */
void clear_input_buffer(void);
bool get_int_input(const char *prompt, int *output);
bool get_double_input(const char *prompt, double *output);
void wait_for_enter(void);

/* UI & Formatting Helpers */
void print_header(const char *title);
void print_divider(char ch, int length);

#endif /* UTILS_H */
