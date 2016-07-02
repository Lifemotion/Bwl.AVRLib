#pragma once

volatile unsigned char gps_status;
volatile unsigned char gps_hour;
volatile unsigned char gps_min;
volatile unsigned char gps_sec;
volatile unsigned char gps_msec;

volatile signed char gps_timezone;

char gps_decode_gprmc(char* buffer);

