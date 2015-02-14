/*
        EEPROM Map for the Remote Station of the SmartGarden system
		This file is not intended to be included directly, it should be used as a part of the settings.h


This module defines EEPROM addresses for various settings.

 Creative Commons Attribution-ShareAlike 3.0 license
 Copyright 2014 tony-osp (http://tony-osp.dreamwidth.org/)


*/

#ifndef _EEPROM_MAP_h
#define _EEPROM_MAP_h

#define ADDR_OP1                                4
#define ADDR_HW_VERSION							5
#define ADDR_SW_VERSION							6
#define ADDR_STATION_ID							7
#define ADDR_NUM_ZONES                          10
#define ADDR_PUMP_CHANNEL                       11

#define ADDR_MAX_TTR							12


#define ADDR_OTYPE                              20
#define ADDR_NUM_OT_DIRECT_IO					21
#define	ADDR_OT_DIRECT_IO						22		// Local direct IO map (positive or negative), maximum of 16 GPIO pins
#define ADDR_NUM_OT_OPEN_SPRINKLER				38
#define ADDR_OT_OPEN_SPRINKLER					39		// OpenSprinkler-style serial IO hookup

#define ADDR_EVTMASTER_FLAGS					43		// EventMaster flags - 2 bytes (zero if no master)
#define ADDR_EVTMASTER_STATIONID				45		// EventMaster StationID - 1 byte
#define ADDR_EVTMASTER_ADDRESS					46		// EventMaster XBee address - 2 bytes

#define END_OF_ZONE_BLOCK						832

// Networks config

// XBee RF network

#define	ADDR_NETWORK_XBEE_FLAGS		128		// XBee network status flags (enabled/on/etc)
#define ADDR_NETWORK_XBEE_PORT		129		// Serial port to use
#define ADDR_NETWORK_XBEE_SPEED		130		// Serial port speed to use, two bytes

#define ADDR_NETWORK_XBEE_PANID		132		// XBee PAN ID, two bytes
#define ADDR_NETWORK_XBEE_ADDR16	134		// XBee address, two bytes (we are using two-byte mode)
#define ADDR_NETWORK_XBEE_CHAN		136		// XBee channel, one byte

#define ZONE_OFFSET 576
#define ZONE_INDEX 32

#define STATION_INDEX			48
#define STATION_OFFSET			512
#define END_OF_STATION_BLOCK	575

#define ADDR_NUM_SENSORS		256

#define SENSOR_INDEX			24
#define SENSOR_OFFSET			257
#define END_OF_SENSORS_BLOCK	512

#if ZONE_OFFSET + (ZONE_INDEX * MAX_ZONES) > END_OF_ZONE_BLOCK
#error Number of Zones is too large
#endif

#if STATION_OFFSET + (STATION_INDEX * MAX_STATIONS) > END_OF_STATION_BLOCK
#error Number of Stations is too large
#endif

#if SENSORS_OFFSET + (SENSORS_INDEX * MAX_SENSORS) > END_OF_SENSORS_BLOCK
#error Number of Sensors is too large
#endif


#endif //_EEPROM_MAP_h