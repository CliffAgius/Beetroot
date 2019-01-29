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
*	Initialisation.cpp
*
*/


#include <FingerLib.h>
#include <Wire.h>

#include "Globals.h"
#include "Initialisation.h"

#include "I2C_IMU_LSM9DS1.h"				// IMU
#include "Demo.h"							// DEMO
#include "EMGControl.h"						// EMG
#include "ErrorHandling.h"					// ERROR
#include "Grips.h"							// Grip
#include "HANDle.h"							// HANDle
#include "LED.h"							// NeoPixel
#include "SerialControl.h"					// init char codes
#include "Watchdog.h"						// Watchdog

//If the Adafruit board is used then need to use the FlashAsEEPROM as it has no EEPROM so it needs to be faked...
#ifdef ADAFRUIT_FEATHER_M0
	#include "BlueTooth.h"						//Bluetooth.
	#include <FlashAsEEPROM.h>
#else
	#include "I2C_EEPROM.h"
#endif // ADAFRUIT_FEATHER_M0

static CIRCLE_BUFFER <float> tempBuff;		// temperature circular buffer

Settings settings;		// board settings

// board initialisation sequence
void deviceSetup(void)
{
#if defined(ARDUINO_ARCH_SAMD)
	//Watchdog.begin(WATCHDOG_RESET_PER);	// enable the Watchdog timer 
#endif

#if defined (SERIAL_JACK_CONTROL)
	setHeadphoneJack(JACK_SERIAL);	// configure headphone jack to Serial
#else
	//setHeadphoneJack(JACK_ADC);		// configure headphone jack to ADC so as to not affect I2C lines
#endif

#ifdef ADAFRUIT_FEATHER_M0
	setupBT();					//Setup the Bluetooth connection with the OnBoard BlueFruit LE Module...
	MYSERIAL.println("Bluetooth Started...");
#endif

	MYSERIAL.begin(SERIAL_BAUD_RATE);		// initialise Serial

	Wire.begin();				// initialise I2C

	//LED.begin();				// initialise NeoPixel

	//timerSetup();				// initialise customMillis() and LED pulsing

	ERROR.begin();				// initialise the error handler
	ERROR.checkPrevError();		// check for previous errors (using EEPROM)
	ERROR.set(ERROR_INIT);		// set error state during initialisation, and set LED to orange	

	readEEPROM();				// load settings from EEPROM, if no settings, use defaults
	
	setupMtrs();				//Setup the motors...
	initFingerPins();			// attach finger pins and start ms timer

	initSerialCharCodes();		// assign the char codes and functions to char codes

	Grip.begin();				// initialise the grips
	Grip.setGrip(G4);
	Grip.setDir(OPEN);
	Grip.run();

	//EMG.begin();				// initialise EMG control

#if !defined(ADAFRUIT_FEATHER_M0)	//The Adafruit design has no IMU so no point using it...
	IMU.begin();				// initialise IMU	
#endif
	setModes();					// start EMG or Demo mode
	MYSERIAL_PRINTLN("Mode Set...");
	//detectSerialConnection();	// wait for serial connection if flag is set
	MYSERIAL_PRINTLN("Serial Detected...");
	ERROR.clear(ERROR_INIT);	// clear error state and set LED to green

#if defined(ARDUINO_ARCH_SAMD)
	//Watchdog.reset();
#endif
	MYSERIAL_PRINTLN("End of Device Setup...");
}

void setupMtrs() 
{
	for (int i = 1; i <= 4; i++)
	{
		mtrs[i] = AFMS.getMotor(i);
		MYSERIAL_PRINT("Motor connected - ");
		MYSERIAL_PRINTLN(i);
	}

	//Need to configure the AdaFruit Motor Shield as this will be done inside the
	//FingerLib files...
	MYSERIAL_PRINTLN("Starting the AFMS...");
	AFMS.begin();
	MYSERIAL_PRINTLN("AFMS started...");
}

// wait for serial connection if flag is set
void detectSerialConnection(void)
{
	if (settings.waitForSerial)			// if flag is set
	{
		MYSERIAL_PRINTLN("Waiting for serial...")
		while (!MYSERIAL)				// wait for serial connection
		{
//#if defined(ARDUINO_ARCH_SAMD)
//			Watchdog.reset();
//#endif
		}
		MYSERIAL_PRINTLN_PGM("Started");
	}
}

// read the settings from EEPROM
void loadSettings(void)
{

#ifdef ADAFRUIT_FEATHER_M0
	//As the Feather board is being used the EEPROM chip dosn't exist so use FlashAsEERPOM instead...
	if (EEPROM.isValid())
	{
		settings.handType = (HandType)EEPROM.read(0);
		settings.mode = (OperatingMode)EEPROM.read(1);
		settings.emg.peakThresh = EEPROM.read(2);
		settings.emg.holdTime = EEPROM.read(3);
		settings.waitForSerial = EEPROM.read(4);
		settings.motorEn = EEPROM.read(5);
		settings.printInstr = EEPROM.read(6);
		settings.init = EEPROM.read(7);
		MYSERIAL_PRINTLN("Adafruit EEPROM settings loaded...");
	}
#else
	static bool firstLoad = true;

	// if this is the first time the settings are being loaded from EEPROM
	if (firstLoad)
	{
		firstLoad = false;

		// if size of settings will overflow EEPROM, set error and halt program
		if ((EEPROM_LOC_BOARD_SETTINGS + sizeof(settings)) > EEPROM_TOTAL_SIZE - 1)
		{
			ERROR.set(ERROR_EEPROM_SETTINGS);
		}
	}

	//MYSERIAL.print("loadSettings() settings size: ");
	//MYSERIAL.println(sizeof(settings));

	//MYSERIAL.print("From: ");
	//MYSERIAL.print(EEPROM_LOC_BOARD_SETTINGS);
	//MYSERIAL.print(" to: ");
	//MYSERIAL.println(EEPROM_LOC_BOARD_SETTINGS+sizeof(settings));

	EEPROM_readStruct(EEPROM_LOC_BOARD_SETTINGS, settings);
#endif // ADAFRUIT_FEATHER_M0

}

// store the settings in EEPROM
void storeSettings(void)
{
	//MYSERIAL.print("storeSettings() settings size: ");
	//MYSERIAL.println(sizeof(settings));

//As the Feather board is being used the EEPROM chip dosn't exist so use FlashAsEERPOM instead...
#ifdef ADAFRUIT_FEATHER_M0
	/*EEPROM.write(0, settings.handType);
	EEPROM.write(1, settings.mode);
	EEPROM.write(2, settings.emg.peakThresh);
	EEPROM.write(3, settings.emg.holdTime);
	EEPROM.write(4, settings.waitForSerial);
	EEPROM.write(5, settings.motorEn);
	EEPROM.write(6, settings.printInstr);
	EEPROM.write(7, settings.init);*/
	//EEPROM.commit();
#else
	//Use the normal I2C_EEPROM system...
	EEPROM_writeStruct(EEPROM_LOC_BOARD_SETTINGS, settings);
#endif // ADAFRUIT_FEATHER_M0

}


// set default settings
void resetToDefaults(void)
{
	ERROR.storeError(NO_ERROR);			// reset stored error state

	settings.handType = HAND_TYPE_LEFT;	// right hand
	settings.mode = MODE_DEMO;				// normal mode (not demo or EMG)

	settings.emg.holdTime = 300;			// 300ms
	settings.emg.peakThresh = 600;			// 600/1023

	settings.waitForSerial = true;			// wait for serial connection to start
	settings.motorEn = true;				// enable all motors
	settings.printInstr = true;				// print serial instructions

	settings.init = EEPROM_INIT_CODE;		// store the unique initialisation code to indicate that EEPROM has been initialised with values

	//storeSettings();						// store the settings in EEPROM
}

// start hand in a particular mode depending on EEPROM settings
void setModes(void)
{
	MYSERIAL_PRINT("Mode being set to - ");
	MYSERIAL_PRINTLN(settings.mode);
	// initialise hand in specific mode, read from EEPROM
	switch (settings.mode)
	{
	case MODE_DEMO:
		DEMO.toggleConstant();
		break;
	case MODE_EMG_SIMPLE:
		EMG.simple();
		break;
	case MODE_EMG_PROP:
		EMG.proportional();
		break;
	case MODE_HANDLE:
		HANDle.enable();
		break;
	default:
		break;
	}
}

// load settings from EEPROM, if no previous EEPROM settings are stored, store defaults
void readEEPROM(void)
{
	loadSettings();				// load settings from EEPROM

	// if the EEPROM is not currently loaded with the correct values
	if (settings.init != EEPROM_INIT_CODE)
	{
		MYSERIAL_PRINTLN("Resetting defaults as EEPROM not valid...");
		resetToDefaults();		// set the default values
		storeSettings();		// store settings in EEPROM

		//deviceSetup();			// restart device setup
	}
	MYSERIAL_PRINTLN("EEPROM Set-up complete...");
}

// attach the finger pins for a left/right hand
void initFingerPins(void)
{
	// if no hand type is detected
	if ((settings.handType != HAND_TYPE_RIGHT) && (settings.handType != HAND_TYPE_LEFT))
	{
		settings.handType = HAND_TYPE_LEFT;			// default to a right hand
		storeSettings();								// store the settings in EEPROM
	}

#if defined(ARDUINO_SAMD_CHESTNUT)
	// Allow motor order to be reversed for the new Brunel design.
	static const int fingerOrderSets[][4] = { { 1,2,0,3 }, { 3,0,2,1 } };			// order of finger connectors for Brunel V1 & V2 (M1, M2, M3, M4)
	const int* fingerOrder = fingerOrderSets[(BRUNEL_VER == 1) ? 0 : 1];			// point to one of the finger orders

	static const int fingerInvSets[][4] = { {true, true, false, true }, {true, false, true, true} };	// set fingers to be inverted for Brunel V1 & V2
	const int* fingerInv = fingerInvSets[(BRUNEL_VER == 1) ? 0 : 1];				// point to one of the finger orders

	// attach the finger pins
	if (settings.handType == HAND_TYPE_RIGHT)
	{
		finger[fingerOrder[0]].attach(1, 2, A0, A6, fingerInv[0]);		// M1     
		finger[fingerOrder[1]].attach(7, 5, A1, A9, fingerInv[1]);		// M2
		finger[fingerOrder[2]].attach(4, 8, A2, A8, fingerInv[2]);		// M3
		finger[fingerOrder[3]].attach(0, 9, A3, A7, fingerInv[3]);		// M4

	}
	else if (settings.handType == HAND_TYPE_LEFT)
	{
		finger[fingerOrder[3]].attach(1, 2, A0, A6, fingerInv[3]);		// M1     
		finger[fingerOrder[2]].attach(7, 5, A1, A9, fingerInv[2]);		// M2
		finger[fingerOrder[1]].attach(4, 8, A2, A8, fingerInv[1]);		// M3
		finger[fingerOrder[0]].attach(0, 9, A3, A7, fingerInv[0]);		// M4
	}
#elif defined(ADAFRUIT_FEATHER_M0)
	MYSERIAL_PRINTLN("Attaching Fingers...");
	// attach the finger pins
	if (settings.handType == HAND_TYPE_RIGHT)
	{
		finger[0].attach(-1, -1, A0, true);		// Thumb
		finger[1].attach(-1, -1, A1, false);	// Index
		finger[2].attach(-1, -1, A2, false);	// Middle
		finger[3].attach(-1, -1, A3, false);	// Ring/Pinky

	}
	else if (settings.handType == HAND_TYPE_LEFT)
	{
		finger[0].attach(-1, -1, A0, true);		// M3 Thumb     
		finger[1].attach(-1, -1, A1, false);	// M1 Index
		finger[2].attach(-1, -1, A2, false);	// M2 Middle
		finger[3].attach(-1, -1, A3, true);	// M4 Ring/Pinky
	}
	
#else
#error "You will need to enter the correct pins for the finger motor and position feedback"
#endif


	// enable all fingers
	for (int i = 0; i < NUM_FINGERS; i++)
	{
		if (!finger[i].attached())				// if finger failed to attach
		{
			ERROR.set(ERROR_FINGER_INIT);		// set error
			break;
		}

		finger[i].motorEnable(settings.motorEn);	// set motor to be enabled/disabled depending on EEPROM setting
#ifdef FORCE_SENSE
		finger[i].forceSenseEnable(true);				// enable force sense on the finger
#endif

		finger[i].open();
	}
	MYSERIAL_PRINTLN("Fingers Attached...");
}

// configure headphone jack to I2C, ADC, Digital or SerialJack
void setHeadphoneJack(HeadphoneJackMode mode)
{
	const int commSwitchPin = 10;

	pinMode(commSwitchPin, OUTPUT);

	digitalWrite(commSwitchPin, mode);			// JACK_I2C, JACK_ADC, JACK_DIGITAL, JACK_SERIAL
	delay(100);									// allow time for switch to settle
}

// print board & firmware version, hand type and motor enabled/disabled
void printDeviceInfo(void)
{
	const char* handTypeNames[3] = { "NONE", "Right", "Left" };

	// print Brunel version
	MYSERIAL_PRINT("Brunel V");
	MYSERIAL_PRINTLN(BRUNEL_VER);
	
	// print firmware version
	MYSERIAL_PRINT("FW:\tBeetroot V");
	MYSERIAL_PRINT(FW_VER_MAJ);
	MYSERIAL_PRINT(".");
	MYSERIAL_PRINT(FW_VER_MIN);
	MYSERIAL_PRINT(".");
	MYSERIAL_PRINTLN(FW_VER_PAT);

	// print board name
	MYSERIAL_PRINTLN_PGM("Board:\tChestnut");

	// print hand type
	MYSERIAL_PRINT_PGM("Hand:\t");
	MYSERIAL_PRINTLN(handTypeNames[settings.handType]);
}

// monitor system status
void systemMonitor(void)
{
	static MS_NB_DELAY timer_1s;

	if (timer_1s.timeElapsed(1000))
	{
		// monitor board temperature
		//monitorTemperature();	// duration 12.5ms (21/02/18)

	}
}

// read the device temperature, in 'C
float readTemperature(void)
{
	const uint8_t buffSize = 16;			// temperature buffer size
	static bool init = false;				// initialisation flag

	// on the first run, load the buffer with battery values
	if (!init)
	{
		//Comms.println("Init temperature buff");

		tempBuff.begin(buffSize);			// init the buffer

		for (int i = 0; i < buffSize; i++)
		{
			IMU.poll();
			tempBuff.write(IMU.getTemp());	// fill the buffer with temperature values
		}
		init = true;
	}

	IMU.poll();
	tempBuff.write(IMU.getTemp());	// fill the buffer with temperature values

	return tempBuff.read();
}

// read the minimum temperature reached since power-on
float readMinTemp(void)
{
	return tempBuff.readMin();
}

// read the maximum temperature reached since power-on
float readMaxTemp(void)
{
	return tempBuff.readMax();
}

// check the temperature, throw warnings/errors or shutdown if too high
void monitorTemperature(void)
{
	float temp = readTemperature();

	// monitor CPU temperature
	if (temp >= CPU_TEMP_MAX)				// if device is too hot to continue	
	{
		if (!ERROR.isSet(ERROR_TEMP_MAX))
		{
			for (uint8_t i = 0; i < NUM_FINGERS; i++)
			{
				finger[i].motorEnable(false);
			}
			
			ERROR.set(ERROR_TEMP_MAX);		// set error
		}

	}
	else if (temp >= CPU_TEMP_WARNING)		// if device is starting to get warm
	{
		if (!ERROR.isSet(ERROR_TEMP_WARNING))
		{
			ERROR.set(ERROR_TEMP_WARNING);	// set warning
		}
	}
	else									// else if battery level is nominal
	{
		ERROR.clear(ERROR_TEMP_MAX);		// if error set, clear it
		ERROR.clear(ERROR_TEMP_WARNING);	// if warning set, clear it
	}
}
