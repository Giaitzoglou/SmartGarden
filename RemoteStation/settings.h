/*
  Settings handling for Local UI on Remote station on SmartGarden


Copyright 2014 tony-osp (http://tony-osp.dreamwidth.org/)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

*/

#ifndef _SETTINGS_h
#define _SETTINGS_h

// This simple Remote station may have up to 8 zones
#define MAX_ZONES 8
// This simple Remote station has only one Station defined in the config
#define MAX_STATIONS 1
// This Remote station may have up to 8 sensors
#define MAX_SENSORS	 8

#include <inttypes.h>

#include "core.h"
#include "port.h"

#include "eepromMap.h"

#define EEPROM_SHEADER "R2.3"


#define NETWORK_XBEE_DEFAULT_ENABLED	true

#define NETWORK_XBEE_DEFAULT_PANID	5520	
#define NETWORK_XBEE_DEFAULT_CHAN	16
#define NETWORK_XBEE_DEFAULT_PORT	1
#define NETWORK_XBEE_DEFAULT_SPEED	57600

#define NETWORK_FLAGS_ENABLED		1	// 1 - indicates that the network is enabled (config)
#define NETWORK_FLAGS_ON			2	// 1 - indicates that the network is running (runtime state)

#define NETWORK_XBEE_DEFAULTADDRESS	2
#define DEFAULT_STATION_ID			1

#define DEFAULT_TTR					99
#define DEFAULT_MAX_OFFLINE_TDELTA  300000UL		// time (in milliseconds) since last time sync before indicator starts to show that the station is offline
													// 300,000ms is 5minutes.

////////////////////
//  EEPROM Getter/Setters


// Misc
bool IsFirstBoot();
void ResetEEPROM();

// XBee RF network
bool IsXBeeEnabled(void);
uint8_t GetXBeePort(void);
uint16_t GetXBeePortSpeed(void);
uint16_t GetXBeeAddr(void);
uint16_t GetXBeePANID(void);
uint8_t GetXBeeChan(void);
uint8_t GetXBeeFlags(void);
uint8_t GetMyStationID(void);
uint8_t GetMaxTtr(void);
uint8_t GetNumZones(void);
uint8_t GetPumpChannel(void);


void SetXBeeFlags(uint8_t flags);
void SetXBeeAddr(uint16_t addr);
void SetXBeePANID(uint16_t panID);
void SetXBeePortSpeed(uint16_t speed);
void SetXBeePort(uint8_t port);
void SetXBeeChan(uint8_t chan);
void SetXBeeFlags(uint8_t flags);
void SetMyStationID(uint8_t stationID);
void SetMaxTtr(uint8_t ttr);
void SetNumZones(uint8_t numZones);
void SetPumpChannel(uint8_t pumpChannel);


#endif

