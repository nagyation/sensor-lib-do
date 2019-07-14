# DO Sensor library
This library is made to manage the usage of a Dissolved Oxygen Probe.

# How it works!
The do value is measured by reading the voltage across the do sensor in millivolts. temperature, pressure and salinity are compensated.

The `lib_do_cmd` is used to recieve cmds from the *parser or any caller library* and return the required output, To read sensor data, use `do_read` command, you can use calibrate cmds `do_cal_atm, do_cal_zero` to calibrate the sensor at runtime and use `do_cal_clear` to restore the default calibration, also you can get the calibration status using `do_cal_get` it should return `3` if all calibration points are set, lastly `do_reset` resets all the device params back to default.

Notice: `MAGIC_NUMBER_DEFAULT` is used for data integrity check.

# How to use!
Copy lib_do_config.template.h to lib_do_config.h and implement the sensor_mv function.
sensor_mv should return the voltage accross the probe in millitvolts.

License
----

GNU General Public License v3.0

***Copyright (C) 2019 Conative Labs***
