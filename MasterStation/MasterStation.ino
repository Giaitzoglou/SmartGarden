/*

Core SmartGarden Master controller file.

This project was inspired by Ray's OpenSprinkler project, and by Sprinklers_pi program (Richard Zimmerman)

Some of the modules used in this project came from Sprinklers_pi code and are covered by Richard's (c),
other parts of the code are written by Tony-osp (http://tony-osp.dreamwidth.org/)

This particular file (MasterStation.ino) is written by Tony-osp.

*/

#include <SdVolume.h>
#include <SdStream.h>
#include <SdSpi.h>
#include <SdInfo.h>
#include <SdFile.h>
#include <SdFatUtil.h>
#include <SdFatmainpage.h>
#include <SdFatConfig.h>
#include <SdBaseFile.h>
#include <Sd2Card.h>
#include <ostream.h>
#include <istream.h>
#include <iostream.h>
#include <ios.h>
#include <bufstream.h>
#include <ArduinoStream.h>


#include "settings.h"
#include "core.h"
#include <Ethernet.h>
#include <SPI.h>
#include <EEPROM.h>
#include <Time.h>
#include <SDFat.h>
#include <LiquidCrystal.h>
#include "LocalUI.h"
#include "sdlog.h"
#include <SFE_BMP180.h>
#include <Wire.h>
#include "LocalBoard.h"
#include <IniFile.h>
#include <XBee.h>
#include "XBeeRF.h"
#include "port.h"
#include "Defines.h"

OSLocalUI localUI;
SdFat sd;

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xAD};

void	RegisterRemoteEvents(void);


void setup() {
    Serial.begin(115200); 
	trace_setup(Serial);
    
	trace(F("Start!\n"));

    localUI.begin();
    
	if (IsFirstBoot())
	{
// Note: To reset EEPROM we need to initialize SD card. But we must initialize Ethernet first, otherwise SD card will not work.
//		 To get around this dependency we initialize Ethernet with a dummy address and initialize SD card. 
//		 Anyway after EEPROM reset we will have to reboot the controller.

		Ethernet.begin(mac, IPAddress(1,1,1,2), INADDR_NONE, IPAddress(1,1,1,1), IPAddress(255,255,255,0));
		if (!sd.begin(4, SPI_HALF_SPEED)) 
		{
			trace(F("Could not Initialize SDCard"));
			localUI.lcd_print_line_clear_pgm(PSTR("EEPROM Corrupted"), 0);
			localUI.lcd_print_line_clear_pgm(PSTR("SD CARD FAILURE!"), 1);
			delay(10000);
			sysreset();
		}
		ResetEEPROM();	// note: ResetEEPROM will also reset the controller.
	}

    localUI.lcd_print_line_clear_pgm(PSTR("XBee RF init..."), 1);
	XBeeRF.begin();

    localUI.lcd_print_line_clear_pgm(PSTR("Ethernet init..."), 1);
	// start the Ethernet connection and the server:
    Ethernet.begin(mac, GetIP(), INADDR_NONE, GetGateway(), GetNetmask());

	if (!sd.begin(4, SPI_HALF_SPEED)) 
	{
		trace(F("Could not Initialize SDCard\n"));
	}
	else
	{
		trace(F("SDCard init success\n"));
	}

	RegisterRemoteEvents();

    // give the Ethernet shield time to set up:
    delay(1000);
    
}

void loop() {
    mainLoop();
    localUI.loop();
	XBeeRF.loop();
}


// Go through remote stations and register myself as EvtMaster. Called as a part of the initialization sequence.
//
// (p.s. Really should have a separate remote stations manager, but can put it here for now)
//
void	RegisterRemoteEvents(void)
{
		for( uint8_t i=1; i<MAX_STATIONS; i++ )		// iterate through stations starting from 1, since station 0 is always local
		{
			XBeeRF.SubscribeEvents( i );			// we are relying on the station enable and network type check inside SubscribeEvents()
		}
}
