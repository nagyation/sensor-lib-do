#ifndef lib_do_h
#define lib_do_h

#include <stdint.h>

typedef float lib_do_slope_t;
typedef float lib_do_zero_shift_t;
typedef float lib_do_oxygen_t;
typedef float lib_do_sat_t;
typedef float lib_do_temperature_t;
typedef float lib_do_salinity_t;
typedef float lib_do_pressure_t;

typedef struct lib_do_params_t {
	uint8_t magic_number;
	lib_do_zero_shift_t zero_shift;
	lib_do_slope_t slope;
} lib_do_params_t;

typedef struct lib_do_reading_t {
	lib_do_oxygen_t oxygen;
	lib_do_sat_t sat;
} lib_do_reading_t;

typedef enum lib_do_cmd_t {
	read,
	get_temperature,
	set_temperature,
	get_salinity,
	set_salinity,
	get_pressure,
	set_pressure,
	cal_atm,
	cal_zero,
	cal_get,
	cal_clear,
	reset,
} lib_do_cmd_t;

void lib_do_init(lib_do_params_t *params_struct);
void lib_do_cmd(lib_do_cmd_t command, void *output_buffer);

#endif
