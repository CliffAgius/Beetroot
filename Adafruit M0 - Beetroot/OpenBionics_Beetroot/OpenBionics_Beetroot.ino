/*	Open Bionics - Beetroot
 *	Author - Olly McBride
 *	Date - October 2016
 *
 *	This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License.
 *	To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/.
 *
 *	Website - http://www.openbionics.com/
 *	GitHub - https://github.com/Open-Bionics
 *	Email - ollymcbride@openbionics.com
 *
 *	OpenBionics_Beetroot.ino
 *
 */


#include <Adafruit_BluefruitLE_UART.h>
#include <Adafruit_BluefruitLE_SPI.h>
#include <Adafruit_BLEMIDI.h>
#include <Adafruit_BLEGatt.h>
#include <Adafruit_BLEEddystone.h>
#include <Adafruit_BLEBattery.h>
#include <Adafruit_BLE.h>
#include <Adafruit_SleepyDog.h>
#include <SPI.h>

#ifdef ADAFRUIT_FEATHER_M0
	#include <FlashAsEEPROM.h>					//Feather Board has no EEPROM so this uses Flash Instead
	#include <Adafruit_ATParser.h>				//Parse the AT commands for the BT module
	#include <MultiStepper.h>					
	#include <AccelStepper.h>
	#include <Adafruit_SleepyDog.h>				//Adafruit WatchDog Timer...
#else
	#include "Watchdog.h"						// Watchdog
#endif // ADAFRUIT_FEATHER_M0


#include <Wire.h>
#include "FingerLib.h"
#include "Globals.h"
#include "Demo.h"							// DEMO
#include "EMGControl.h"						// EMG
#include "Grips.h"							// Grip
#include "HANDle.h"							// HANDle
#include "Initialisation.h"					// settings, deviceSetup, systemMonitor 
#include "SerialControl.h"					// pollSerial

#if defined(ARDUINO_SAMD_ZERO) && defined(SERIAL_PORT_USBVIRTUAL)
 // Required for Serial on Zero based boards
#define Serial SERIAL_PORT_USBVIRTUAL
#endif

long CheckBTTime = 5000;	// time in ms between checks of BT...
long previousMillis = 0;    // will store last time BT was checked...

void setup()
{
	deviceSetup();							// initialise the board

	if (settings.printInstr)
	{
		delay(100);							// allow time for serial to connect
		serial_SerialInstructions();		// print serial instructions
	}
}


void loop()
{

#if defined(USE_ROS)
	ros_run();
#endif

#if !defined(ADAFRUIT_FEATHER_M0)	//Cant check the system temp on the Feather as there is no IMU fitted...
	// monitor system temp
	systemMonitor();
#endif

	// check to see if it's time to try and setup the BT connection again...
	/*unsigned long currentMillis = millis();
	if (!BTEnabled && (currentMillis - previousMillis > CheckBTTime))
	{
		previousMillis = currentMillis;
		setupBT();
	}*/

	// if demo mode is enabled, run demo mode
	if (DEMO.enabled())
	{
		DEMO.run();
	}

	// if EMG mode is enabled, run EMG mode
	if (EMG.enabled())
	{
		EMG.run();
	}

	// if HANDle mode is enabled, run HANDle mode
	if (HANDle.enabled())
	{
		HANDle.run();
	}


	// process any received serial characters
	pollSerial();

#if defined(ADAFRUIT_FEATHER_M0)
	Watchdog.reset();
#endif
}
