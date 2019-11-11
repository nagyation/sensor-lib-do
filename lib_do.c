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


#include "lib_do.h"
#include "lib_do_config.h"

#include <math.h>

#define MAGIC_NUMBER_DEFAULT 0x61
#define ZERO_SHIFT_DEFUALT 0
#define SLOPE_DEFAULT 40.26f
#define DO_DEFAULT 14.62f

static lib_do_temperature_t temperature = 20;
static lib_do_pressure_t pressure = 760;
static lib_do_salinity_t salinity = 0;
static lib_do_params_t *params;

static void calibration_set_default(void) {
	params->zero_shift = ZERO_SHIFT_DEFUALT;
	params->slope = SLOPE_DEFAULT;
}

static void params_set_default(void) {
	params->magic_number = MAGIC_NUMBER_DEFAULT;
	calibration_set_default();
}

void lib_do_init(lib_do_params_t *ext_params) {
	params = ext_params;
	if(params->magic_number != MAGIC_NUMBER_DEFAULT)
		params_set_default();
}

void lib_do_cmd(lib_do_cmd_t cmd, void *buffer) {
	switch(cmd) {
		case do_read: {
			lib_do_reading_t *vals = buffer;
			float adc_val = sensor_mv();

			vals->oxygen = (adc_val - params->zero_shift)/params->slope;

			vals->sat = vals->oxygen;
			if(vals->sat  < 0)vals->sat  = 0;
			else vals->sat  *= 100;

			vals->oxygen *= DO_DEFAULT;
			//salinity compensation must be done first
			vals->oxygen -= (0.06084*pow(10.0,-0.02538*temperature)+0.03084)*salinity;
			if(vals->oxygen < 0)vals->oxygen = 0;
			else {
				//temperature compensation
				vals->oxygen *= 1+temperature*(-0.027474529313609+temperature*(0.00051630321897-0.000004542832887059*temperature));
				//pressure compensation
				vals->oxygen *= pressure * 0.001315789473684;
			}
		} break;
		case do_get_temperature:
			*(lib_do_temperature_t*)buffer = temperature;
		break;
		case do_set_temperature:
			temperature = *(lib_do_temperature_t*)buffer;
		break;
		case do_get_salinity:
			*(lib_do_salinity_t*)buffer = salinity;
		break;
		case do_set_salinity:
			salinity = *(lib_do_salinity_t*)buffer;
		break;
		case do_get_pressure:
			*(lib_do_pressure_t*)buffer = pressure;
		break;
		case do_set_pressure:
			pressure = *(lib_do_pressure_t*)buffer;
		break;
		case do_cal_atm:
			//atm calibration is basically the sensor voltage at 100% oxygen 0 salinity 0 temperature and atm pressure which corresponds to 14.62 DO
			params->slope = sensor_mv();
		break;
		case do_cal_zero:
			params->zero_shift = sensor_mv();
		break;
		case do_cal_get:
			((uint8_t *)buffer)[0] = 0;
			if(SLOPE_DEFAULT != params->slope)
				((uint8_t *)buffer)[0]++;
			if(0 != params->zero_shift)
				((uint8_t *)buffer)[0]++;
		break;
		case do_cal_clear:
			calibration_set_default();
		break;
		case do_reset:
			params_set_default();
		break;
	}
}
