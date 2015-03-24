/*
  Settings handling for Local UI on Remote station on SmartGarden


 Creative Commons Attribution-ShareAlike 3.0 license
 (c) 2014 Tony-osp (tony-osp.dreamwidth.org)

*/

#include "settings.h"
#include "port.h"
#include <string.h>
#include <stdlib.h>
#include "localUI.h"
#include "XBeeRF.h"

void ResetEEPROM()
{
		const char * const sHeader = EEPROM_SHEADER;

        trace(F("Reseting EEPROM\n"));

        for (int i = 0; i <= 3; i++)			// write current signature
                EEPROM.write(i, sHeader[i]);

		SetXBeeFlags(NETWORK_FLAGS_ENABLED);
		SetXBeeAddr(NETWORK_XBEE_DEFAULTADDRESS);
		SetXBeePANID(NETWORK_XBEE_DEFAULT_PANID);
		SetXBeePortSpeed(NETWORK_XBEE_DEFAULT_SPEED);
		SetXBeePort(NETWORK_XBEE_DEFAULT_PORT);
		SetXBeeChan(NETWORK_XBEE_DEFAULT_CHAN);
		SetMyStationID(DEFAULT_STATION_ID);
		SetMaxTtr(DEFAULT_TTR);
		SetNumZones(MAX_ZONES);

#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)

		uint8_t		zoneToIOMap[LOCAL_NUM_DIRECT_CHANNELS] = {41, 40, 42, 43 };

#else  // Mega or Moteino Mega (1284p)
#if defined(__AVR_ATmega1284P__) || defined(__AVR_ATmega1284p__)

		uint8_t		zoneToIOMap[LOCAL_NUM_DIRECT_CHANNELS] = {41, 40, 42, 43 };

#else // Uno or equivalent

		uint8_t		zoneToIOMap[LOCAL_NUM_DIRECT_CHANNELS] = {4, 5, 6, 7 };

#endif // Moteino Mega (1284p)
#endif // Mega or Moteino Mega


		SaveZoneIOMap( zoneToIOMap );

		SetEvtMasterFlags(0);
		SetEvtMasterStationID(0);
		SetEvtMasterStationAddress(0);


		localUI.lcd_print_line_clear_pgm(PSTR("EEPROM reloaded"), 0);
		localUI.lcd_print_line_clear_pgm(PSTR("Rebooting..."), 1);
		delay(2000);

		sysreset();
}


bool IsFirstBoot()
{
		const char * const sHeader = EEPROM_SHEADER;

		if ((EEPROM.read(0) == sHeader[0]) && (EEPROM.read(1) == sHeader[1]) && (EEPROM.read(2) == sHeader[2]) && (EEPROM.read(3) == sHeader[3])){

			return false;
		}

        return true;
}

bool IsXBeeEnabled(void)
{
	return (EEPROM.read(ADDR_NETWORK_XBEE_FLAGS) & NETWORK_FLAGS_ENABLED) ? true:false;
}

uint8_t GetXBeeChan(void)
{
	return EEPROM.read(ADDR_NETWORK_XBEE_CHAN);
}

uint8_t GetXBeePort(void)
{
	return EEPROM.read(ADDR_NETWORK_XBEE_PORT);
}
uint16_t GetXBeePortSpeed(void)
{
	uint16_t speed;

	speed = EEPROM.read(ADDR_NETWORK_XBEE_SPEED+1) << 8;
	speed += EEPROM.read(ADDR_NETWORK_XBEE_SPEED);

	return speed;
}

uint8_t GetXBeePANID(void)
{
//	uint16_t panID;

//	panID = EEPROM.read(ADDR_NETWORK_XBEE_PANID+1) << 8;
//	panID += EEPROM.read(ADDR_NETWORK_XBEE_PANID);

	return EEPROM.read(ADDR_NETWORK_XBEE_PANID);
}

uint16_t GetXBeeAddr(void)
{
	uint16_t addr;

	addr = EEPROM.read(ADDR_NETWORK_XBEE_ADDR16+1) << 8;
	addr += EEPROM.read(ADDR_NETWORK_XBEE_ADDR16);

	return addr;
}

void SetXBeeFlags(uint8_t flags)
{
	EEPROM.write(ADDR_NETWORK_XBEE_FLAGS, flags);
}


void SetXBeeChan(uint8_t chan)
{
	EEPROM.write(ADDR_NETWORK_XBEE_CHAN, chan);
}

void SetXBeePort(uint8_t port)
{
	EEPROM.write(ADDR_NETWORK_XBEE_PORT, port);
}

void SetXBeePortSpeed(uint16_t speed)
{
	uint8_t speedh = (speed & 0x0FF00) >> 8;
	uint8_t speedl = speed & 0x0FF;

	EEPROM.write(ADDR_NETWORK_XBEE_SPEED, speedl);
	EEPROM.write(ADDR_NETWORK_XBEE_SPEED+1, speedh);
}

void SetXBeePANID(uint8_t panIDl)
{
	uint8_t panIDh = NETWORK_XBEE_PANID_HIGH;

	EEPROM.write(ADDR_NETWORK_XBEE_PANID, panIDl);
	EEPROM.write(ADDR_NETWORK_XBEE_PANID+1, panIDh);
}

void SetXBeeAddr(uint16_t addr)
{
	uint8_t addrh = (addr & 0x0FF00) >> 8;
	uint8_t addrl = addr & 0x0FF;

	EEPROM.write(ADDR_NETWORK_XBEE_ADDR16, addrl);
	EEPROM.write(ADDR_NETWORK_XBEE_ADDR16+1, addrh);
}




uint8_t GetMyStationID(void)
{
	return EEPROM.read(ADDR_STATION_ID);
}

void SetMyStationID(uint8_t stationID)
{
	EEPROM.write(ADDR_STATION_ID, stationID);
	XBeeRF.begin();		// restart XBee, since our stationID might've been changed.
}


uint8_t GetMaxTtr(void)
{
	return EEPROM.read(ADDR_MAX_TTR);
}

void SetMaxTtr(uint8_t ttr)
{
	EEPROM.write(ADDR_MAX_TTR, ttr);
}

uint8_t GetNumZones(void)
{
	uint8_t  nZones = EEPROM.read(ADDR_NUM_ZONES);
	
	if( nZones <= MAX_ZONES ) return nZones;			// basic protection in case of EEPROM corruption
	else					  return 0;			// in case of EEPROM corruption it is safer to assume 0 enabled zones.
}


uint8_t GetPumpChannel(void)
{
	return EEPROM.read(ADDR_PUMP_CHANNEL);
}


void SetNumZones(uint8_t numZones)
{
	EEPROM.write(ADDR_NUM_ZONES, numZones);
}


void SetPumpChannel(uint8_t pumpChannel)
{
	EEPROM.write(ADDR_PUMP_CHANNEL, pumpChannel);
}

uint8_t GetXBeeFlags(void)
{
	return EEPROM.read(ADDR_NETWORK_XBEE_FLAGS);
}

void SaveZoneIOMap(uint8_t *ptr)
{
        for( int i = 0; i < LOCAL_NUM_DIRECT_CHANNELS; i++)
                EEPROM.write(ADDR_OT_DIRECT_IO + i, *(ptr+i));
}

uint8_t GetDirectIOPin(uint8_t n)
{
	if( n >= LOCAL_NUM_DIRECT_CHANNELS ) return 0;

	return EEPROM.read(ADDR_OT_DIRECT_IO + n);
}

uint16_t GetEvtMasterFlags(void)
{
	uint16_t flags;

	flags = EEPROM.read(ADDR_EVTMASTER_FLAGS+1) << 8;
	flags += EEPROM.read(ADDR_EVTMASTER_FLAGS);

	return flags;
}

uint8_t  GetEvtMasterStationID(void)
{
	return EEPROM.read(ADDR_EVTMASTER_STATIONID);
}

uint16_t GetEvtMasterStationAddress(void)
{
	uint16_t addr;

	addr = EEPROM.read(ADDR_EVTMASTER_ADDRESS+1) << 8;
	addr += EEPROM.read(ADDR_EVTMASTER_ADDRESS);

	return addr;
}

void SetEvtMasterStationAddress(uint16_t addr)
{
	uint8_t addrH = addr >> 8;
	uint8_t addrL = addr & 0x0FF;

	EEPROM.write(ADDR_EVTMASTER_ADDRESS+1, addrH);
	EEPROM.write(ADDR_EVTMASTER_ADDRESS, addrL);
}

void SetEvtMasterFlags(uint16_t flags)
{
	uint8_t flagsH = flags >> 8;
	uint8_t flagsL = flags & 0x0FF;

	EEPROM.write(ADDR_EVTMASTER_FLAGS+1, flagsH);
	EEPROM.write(ADDR_EVTMASTER_FLAGS, flagsL);
}

void SetEvtMasterStationID(uint8_t stationID)
{
	EEPROM.write(ADDR_EVTMASTER_STATIONID, stationID);
}

