#ifndef ICE_SENSORS_H
#define ICE_SENSORS_H

#include <stdbool.h>

/* Sensor Statistics Data Structure */
typedef struct {
    int count;
    double min;
    double max;
    double span;
    double mean;
    double std_dev;
} SensorStats;

/* RPM Calculations */
bool rpm_from_pulses(double pulses_per_sec, int pulses_per_rev, double *rpm);
bool rpm_sync_motor(double frequency, int poles, double *rpm);
bool rpm_from_linear_velocity(double linear_speed_mps, double diameter_m, double *rpm);

/* 4-20 mA Industrial Current Loop Scaler */
bool current_to_engineering_units(double current_ma, double lrv, double urv, double *eng_val);
bool engineering_units_to_current(double eng_val, double lrv, double urv, double *current_ma);

/* Sensor Data Analytics */
bool compute_sensor_stats(const double *readings, int count, SensorStats *stats);

/* Menu Runners */
void run_rpm_menu(void);
void run_sensor_analytics_menu(void);
void run_signal_scaling_menu(void);

#endif /* ICE_SENSORS_H */
