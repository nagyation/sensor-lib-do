#include "unity.h"
#include "lib_do.h"

#include "mock_lib_do_config_test.h"

#define MAGIC_NUMBER_DEFAULT 0x61


void setUP(void)
{
}

void tearDown(void)
{
}

void test_lib_do_init_withMagicNumberAlreadySet(void)
{
  lib_do_params_t params;

  params.slope = 13221;
  params.zero_shift = 13221;
  params.magic_number = MAGIC_NUMBER_DEFAULT; // mock the magic number 
  lib_do_init(&params);

  TEST_ASSERT_EQUAL_FLOAT(13221, params.slope);
  TEST_ASSERT_EQUAL_FLOAT(13221, params.zero_shift);
}

void test_lib_do_init_withoutMagicNumberAlreadySet(void)
{
  lib_do_params_t params;

  params.slope = 13221;
  params.zero_shift = 13221;
  lib_do_init(&params);

  TEST_ASSERT_EQUAL_FLOAT(40.26, params.slope);
  TEST_ASSERT_EQUAL_FLOAT(0, params.zero_shift);
}

void test_lib_do_cmd_ReadSatNegative(void)
{
  lib_do_params_t params;
  lib_do_reading_t reading;
  sensor_mv_ExpectAndReturn(-100);
  
  lib_do_init(&params);

  lib_do_cmd(do_read, &reading);

  TEST_ASSERT_EQUAL_FLOAT(0, reading.sat);
  TEST_ASSERT_EQUAL_FLOAT(0, reading.oxygen);
}

void test_lib_do_cmd_ReadSatValid(void)
{
  lib_do_params_t params;
  lib_do_reading_t reading;
  sensor_mv_ExpectAndReturn(100);
  
  lib_do_init(&params);

  lib_do_cmd(do_read, &reading);

  TEST_ASSERT_EQUAL_FLOAT(248.386, reading.sat);
  TEST_ASSERT_EQUAL_FLOAT(22.5396, reading.oxygen);
}

void test_lib_do_cmd_TemperatureSetAndGet(void)
{
  lib_do_params_t params;
  lib_do_temperature_t temp = 23.5, temp_val; 
  lib_do_init(&params);

  lib_do_cmd(do_set_temperature, &temp);
  lib_do_cmd(do_get_temperature, &temp_val);

  TEST_ASSERT_EQUAL_FLOAT(23.5, temp_val);
}

void test_lib_do_cmd_SalinitySetAndGet(void)
{
  lib_do_params_t params;
  lib_do_salinity_t temp = 23.5, temp_val; 
  lib_do_init(&params);

  lib_do_cmd(do_set_salinity, &temp);
  lib_do_cmd(do_get_salinity, &temp_val);

  TEST_ASSERT_EQUAL_FLOAT(23.5, temp_val);
}


void test_lib_do_cmd_PressureSetAndGet(void)
{
  lib_do_params_t params;
  lib_do_pressure_t temp = 23.5, temp_val; 
  lib_do_init(&params);

  lib_do_cmd(do_set_pressure, &temp);
  lib_do_cmd(do_get_pressure, &temp_val);

  TEST_ASSERT_EQUAL_FLOAT(23.5, temp_val);
}

void test_lib_do_cmd_CalAtm(void)
{
  lib_do_params_t params;

  sensor_mv_ExpectAndReturn(100);
  lib_do_init(&params);
  lib_do_cmd(do_cal_atm, NULL);
  
  TEST_ASSERT_EQUAL_FLOAT(100, params.slope);
}


void test_lib_do_cmd_CalZero(void)
{
  lib_do_params_t params;

  sensor_mv_ExpectAndReturn(100);
  lib_do_init(&params);
  lib_do_cmd(do_cal_zero, NULL);
  
  TEST_ASSERT_EQUAL_FLOAT(100, params.zero_shift);
}

void test_lib_do_cmd_CalGetNoneCaliberated(void)
{
  lib_do_params_t params;
  uint8_t get;
  lib_do_init(&params);
  lib_do_cmd(do_cal_get, &get);

  TEST_ASSERT_EQUAL(0, get);
}

void test_lib_do_cmd_CalGetSlopenCaliberated(void)
{
  lib_do_params_t params;
  uint8_t get;
  lib_do_init(&params);

  params.slope = 12; //random numbers
  lib_do_cmd(do_cal_get, &get);

  TEST_ASSERT_EQUAL(1, get);
}


void test_lib_do_cmd_CalGetZeroShiftCaliberated(void)
{
  lib_do_params_t params;
  uint8_t get;
  lib_do_init(&params);


  params.zero_shift = 12;
  lib_do_cmd(do_cal_get, &get);

  TEST_ASSERT_EQUAL(1, get);
}

void test_lib_do_cmd_CalGetAllCaliberated(void)
{
  lib_do_params_t params;
  uint8_t get;
  lib_do_init(&params);

  params.slope = 12; //random numbers
  params.zero_shift = 12;
  lib_do_cmd(do_cal_get, &get);

  TEST_ASSERT_EQUAL(2, get);
}


void test_lib_do_cmd_CalClear(void)
{
  lib_do_params_t params;


  lib_do_init(&params);
  params.slope = 13221;
  params.zero_shift = 13221;

  lib_do_cmd(do_cal_clear, NULL);
  
  TEST_ASSERT_EQUAL_FLOAT(40.26, params.slope);
  TEST_ASSERT_EQUAL_FLOAT(0, params.zero_shift);
}

void test_lib_do_cmd_Reset(void)
{
  lib_do_params_t params;


  lib_do_init(&params);
  params.slope = 13221;
  params.zero_shift = 13221;
  params.magic_number = 0x50;
  lib_do_cmd(do_reset, NULL);

  TEST_ASSERT_EQUAL(0x61, params.magic_number);
  TEST_ASSERT_EQUAL_FLOAT(40.26, params.slope);
  TEST_ASSERT_EQUAL_FLOAT(0, params.zero_shift);
}
