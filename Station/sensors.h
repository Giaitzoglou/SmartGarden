/*
  Sensors handling module for the SmartGarden system.


This module handles various sensors connected to the microcontroller - Temperature, Pressure, Humidity, Waterflow etc.
Multiple sensor types are supported - BMP180 (pressure), DS18B20 (soil temperature), DHT21 (humidity and temperature) etc. 
Each sensor type is handled by its own piece of code, all sensors are wrapped into the common Sensors class.

Operation is waitless (to a possible extent). The common Sensors class is expected to be called for initialization (from setup()), and from the polling loop.

The Sensors class will handle sensors configuration and sensors reading at configured frequency. Readings are logged using external Logging class (sd-log) 
using time-series pattern. Errors are reported using common Trace infrastructure.



Creative Commons Attribution-ShareAlike 3.0 license
Copyright 2014 tony-osp (http://tony-osp.dreamwidth.org/)

*/

#ifndef _OSSensors_h
#define _OSSensors_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Time.h>
#include <wire.h>
#include "sdlog.h"
#include "settings.h"
#include "Defines.h"

#ifdef SENSOR_ENABLE_BMP180
#include <SFE_BMP180.h>
#include <Wire.h>
#endif

#ifdef SENSOR_ENABLE_DHT
#include <DHT.h>
#endif

#define SENSOR_CHANNEL_TEMPERATURE1 0	// when temp sensor is connected directly to the Master controller, assign it to channel 0
#define SENSOR_CHANNEL_PRESSURE1	1	// when air pressure sensor is connected directly to the Master controller, assign it to channel 1
#define SENSOR_CHANNEL_TEMPERATURE2 2	// second temp sensor connected to the master controller (if any)
#define SENSOR_CHANNEL_HUMIDITY1	3	// humidity sensor

struct SensorStruct 
{
	ShortSensor		config;
	int				lastReading;
	time_t			lastReadingTimestamp;
};

class Sensors {
public:

  // ====== Member Functions ======

  
  // -- Setup --
  byte begin(void);                              // initialization. Intended to be called from setup()

    // -- Operation --
  byte loop(void);                               // Main loop. Intended to be called regularly and frequently to handle sensors reading and logging. Usually  this will be called from Arduino loop()
  
  void ReportSensorReading( uint8_t stationID, uint8_t sensorChannel, int sensorReading );
  bool TableLastSensorsData(FILE* stream_file);

// Data

	int				Temperature;		// latest known readings
	int				Humidity;

private:

	SensorStruct	SensorsList[MAX_SENSORS];
	int				pollMinutesCounter;    
	byte			fPollRemote;
	uint8_t			numStationsToPoll;
	uint8_t			stationsToPollList[MAX_STATIONS];
	uint8_t			nPoll;
    
	void			poll_MinTimer(void);
};

extern Sensors sensorsModule;


#endif // _OSSensors_h
