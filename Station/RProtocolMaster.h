/*
        Remote Station Protocol support for Sprinklers system.

  This module is intended to be used with my SmartGarden system, as well as my modified version of the sprinklers_avr code.


This module handles remote communication protocol. Initial version operates over Xbee link in API mode, but protocol itself is
generic and can operate over multiple transports.


Creative Commons Attribution-ShareAlike 3.0 license
Copyright 2014 tony-osp (http://tony-osp.dreamwidth.org/)

*/

#ifndef _RPROTOCOLMASTER_h
#define _RPROTOCOLMASTER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Time.h>
#include "port.h"
#include <inttypes.h>


#include "SGRProtocol.h"        // wire protocol definitions

typedef bool (*PTransportCallback)(uint8_t nStation, void *msg, uint8_t mSize);
typedef bool (*PARPCallback)(uint8_t nStation, uint8_t *pNetAddress);

class RProtocolMaster {

public:
                RProtocolMaster();
				bool    begin(void);
				void	RegisterTransport(void *ptr);
				void	RegisterARP(void *ptr);

				bool	SendReadZonesStatus( uint8_t stationID, uint16_t transactionID );
				bool	SendReadSystemRegisters( uint8_t stationID, uint8_t startRegister, uint8_t numRegisters, uint16_t transactionID );
				bool	SendReadSensors( uint8_t stationID, uint16_t transactionID );
				bool	SendForceSingleZone( uint8_t stationID, uint8_t channel, uint16_t ttr, uint16_t transactionID );
				bool	SendTurnOffAllZones( uint8_t stationID, uint16_t transactionID );
				bool	SendSetName( uint8_t stationID, const char *str, uint16_t transactionID );
				bool	SendRegisterEvtMaster( uint8_t stationID, uint8_t eventsMask, uint16_t transactionID);

				void	ProcessNewFrame(uint8_t *ptr, int len, uint8_t *pNetAddress);

				void	SendTimeBroadcast(void);


private:
// transport callback, will be populated by the caller beforehand.
				PTransportCallback	_SendMessage;
// ARP address update
				PARPCallback		_ARPAddressUpdate;
};

// Modbus holding registers area size
//
// Currently we support up to 8 zones (can be changed if necessary)
#define         MODBUSMAP_HOLDING_MAX   (MREGISTER_ZONE_COUNTDOWN + 8)

extern RProtocolMaster rprotocol;


#endif  //_RPROTOCOLMASTER_h
