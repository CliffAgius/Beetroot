/*
 *	Author - Clifford Agius
 *	Date - January 2019
 *
 *	This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License.
 *	To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/.
 *
 *	Website - http://www.openbionics.com/
 *	GitHub - https://github.com/Open-Bionics
 *	Email - CliffordAgius@CA_Software.co.uk
 *
 */

#include "BlueTooth.h"
#include <Arduino.h>
#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

 /*=========================================================================
	 APPLICATION SETTINGS

     FACTORYRESET_ENABLE       Perform a factory reset when running this sketch
    
                               Enabling this will put your Bluefruit LE module
							   in a 'known good' state and clear any config
							   data set in previous sketches or projects, so
                               running this at least once is a good idea.
    
                               When deploying your project, however, you will
							   want to disable factory reset by setting this
							   value to 0.  If you are making changes to your
                               Bluefruit LE device via AT commands, and those
							   changes aren't persisting across resets, this
							   is the reason why.  Factory reset will erase
							   the non-volatile memory where config data is
							   stored, setting it back to factory default
							   values.
        
                               Some sketches that require you to bond to a
							   central device (HID mouse, keyboard, etc.)
							   won't work at all with this feature enabled
							   since the factory reset will clear all of the
							   bonding data stored on the chip, meaning the
							   central device won't be able to reconnect.
	 MINIMUM_FIRMWARE_VERSION  Minimum firmware version to have some new features
	 MODE_LED_BEHAVIOUR        LED activity, valid options are
							   "DISABLE" or "MODE" or "BLEUART" or
							   "HWUART"  or "SPI"  or "MANUAL"
							   MODE - Default behaviour, indicates the current operating mode
							   BLEUART - Toggles the LED on any activity on the BLE UART Service (TX or RX characteristic)
	 -----------------------------------------------------------------------*/
#define FACTORYRESET_ENABLE         1
#define MINIMUM_FIRMWARE_VERSION    "0.6.6"
#define MODE_LED_BEHAVIOUR          "MODE"
#define BTDEVICENAME				"Handy"
	 /*=========================================================================*/

Adafruit_BluefruitLE_SPI blePrint(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);
char BTinputs[BUFSIZE + 1];
bool BTEnabled = false;

void setupBT()
{

	BTEnabled = false;
	//Start the connection...
	blePrint.begin();

	/* Perform a factory reset to make sure everything is in a known state */
	if (FACTORYRESET_ENABLE)
	{
		blePrint.factoryReset();
		//Rename the BLuetooth device...
		blePrint.sendCommandCheckOK("AT+GAPDEVNAME=" BTDEVICENAME);
	}

	/* Disable command echo from Bluefruit */
	blePrint.echo(false);

	/* Wait for connection */
	//Wait for the connection or waitTime length which ever comes first...
	unsigned long startedWaiting = millis();
	unsigned long waitTime = 10000;				//Wait time in ms...
	while (!blePrint.isConnected() && millis() - startedWaiting <= waitTime) {
		delay(500);
	}

	//Check if we connected or the connection timed out...
	if (!blePrint.isConnected())
	{
		return;
	}

	// LED Activity command is only supported from 0.6.6
	if (blePrint.isVersionAtLeast(MINIMUM_FIRMWARE_VERSION))
	{
		// Change Mode LED Activity
		blePrint.sendCommandCheckOK("AT+HWModeLED=" MODE_LED_BEHAVIOUR);
	}


	BTEnabled = true;

	// Set module to DATA mode
	blePrint.setMode(BLUEFRUIT_MODE_DATA);

	// Send test data...
	blePrint.println("BLE Connected...");
}

/**************************************************************************/
/*!
	@brief  Constantly poll for new command or response data
*/
/**************************************************************************/
void PollBT(void)
{
	if (BTEnabled)
	{
		if (blePrint.isConnected())
		{
			// Check for user input
			char n = 0;

			// Echo received data
			while (blePrint.available())
			{
				int data = blePrint.read();
				if (data != -1)
				{
					BTinputs[n++] = data;
				}
				/*Serial.print("BT Val - ");
				Serial.println(BTinputs[n - 1]);*/
			}
		}
	}
}

void ClearBTBuffer() {
	BTinputs[0] = NULL;
}

void BTPrint(const char str[])
{
	//blePrint.print("AT+BLEUARTTX=");
	//blePrint.print(str);

	//// check response stastus
	//if (!blePrint.waitForOK()) {
	//	Serial.println(F("Failed to send?"));
	//}

	//if (blePrint.isConnected())
	//{/*
		//blePrint.print(str);*/
		//blePrint.print("AT+BLEUARTTX=");
		blePrint.print(str);
	//}
}

void BTPrint(int val)
{
	//blePrint.print("AT+BLEUARTTX=");
	//blePrint.print(val);

	//// check response stastus
	//if (!blePrint.waitForOK()) {
	//	Serial.println(F("Failed to send?"));
	//}

	/*if (blePrint.isConnected())
	{*/
		//blePrint.print(val);
		//blePrint.print("AT+BLEUARTTX=");
		blePrint.print(val);
	//}
}

void BTPrint(int val, int format)
{
	//blePrint.print("AT+BLEUARTTX=");
	//blePrint.print(val, format);

	//// check response stastus
	//if (!blePrint.waitForOK()) {
	//	Serial.println(F("Failed to send?"));
	//}

	/*if (blePrint.isConnected())
	{*/
		//blePrint.print(val, format);
		//blePrint.print("AT+BLEUARTTX=");
		blePrint.print(val, format);
	//}
}


void BTPrintLn(const char str[])
{
	//blePrint.print("AT+BLEUARTTX=");
	//blePrint.println(str);

	//// check response stastus
	//if (!blePrint.waitForOK()) {
	//	Serial.println(F("Failed to send?"));
	//}

	//if (blePrint.isConnected())
	//{
		//blePrint.println(str);
		//blePrint.print("AT+BLEUARTTX=");
		blePrint.println(str);
	//}
}

void BTPrintLn(int str)
{
	//blePrint.print("AT+BLEUARTTX=");
	//blePrint.println(str);

	//// check response stastus
	//if (!blePrint.waitForOK()) {
	//	Serial.println(F("Failed to send?"));
	//}

	/*if (blePrint.isConnected())
	{*/
		//blePrint.println(str);
		//blePrint.print("AT+BLEUARTTX=");
		blePrint.println(str);
	//}
}

void BTPrintPGM(char ch)
{
	//blePrint.print("AT+BLEUARTTX=");
	//blePrint.print(ch);

	//// check response stastus
	//if (!blePrint.waitForOK()) {
	//	Serial.println(F("Failed to send?"));
	//}

	/*if (blePrint.isConnected())
	{*/
		//blePrint.print(ch);
		//blePrint.print("AT+BLEUARTTX=");
		blePrint.print(ch);
	//}
}