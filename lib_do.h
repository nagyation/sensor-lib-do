/*
  Copyright (C) 2019 Conative Labs
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program. If not, see <https://www.gnu.org/licenses/>
*/

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
	do_read,
	do_get_temperature,
	do_set_temperature,
	do_get_salinity,
	do_set_salinity,
	do_get_pressure,
	do_set_pressure,
	do_cal_atm,
	do_cal_zero,
	do_cal_get,
	do_cal_clear,
	do_reset,
} lib_do_cmd_t;

void lib_do_init(lib_do_params_t *params_struct);
void lib_do_cmd(lib_do_cmd_t command, void *output_buffer);

#endif
