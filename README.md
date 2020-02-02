# Handy Electronics

This repository is a fork of the OpenBionics Beetroot as you will see above, but I have taken it further by adapting the code to run on the [Adafruit Feather M0 Bluefruit](https://learn.adafruit.com/adafruit-feather-m0-bluefruit-le/overview) and using the [Adafruit DC Feather wing](https://learn.adafruit.com/adafruit-stepper-dc-motor-featherwing).

This means that as OpenBionics have now closed the Open Source project while they aim for NICE approval and to sell the Hero Arm around the world you will no longer be able to purchase the OpenBionics Chestnut board.  But thats Ok as I have within the Electronics folder a list of the parts required and the circuit diagrams to build the control for your Handy Project.

The parts are all widely available from either Adafruit direct (Links above!) your local electronics supplier or even Amazon online store.

I have left the Instructions below for setting up the Arduino IDE to connect to the board as most of the instructions for getting the correct files in place still apply.

However if you wish to stay in VisualStudio rather than the very poor Arduino IDE or even VSCode then I hightly recommend the VisualMicro extention which is free from https://www.visualmicro.com/

Take a look around and let me know via Issues or directly via twitter @CliffordAgius if you have any suggestions or questions.



# OLD INSTRUCTIONS

### Open Bionics - Beetroot 

Included in this repository;

- Beetroot V1.0 - The firmware release for Open Bionics Brunel hand & Chestnut PCB 

## Quick Start
### 1. Install [Arduino](https://www.arduino.cc)
* Navigate to the downloads page at [Arduino.cc](https://www.arduino.cc/en/Main/Software)
* Download the latest version of the IDE (1.8.1 at time of writing)
* Install Arduino
### 2. Download [Beetroot](https://github.com/Open-Bionics/Beetroot) 
* Navigate to the [Beetroot repository](https://github.com/Open-Bionics/Beetroot) 
* Download and extract the zip folder (Clone or download -> Download Zip)
* Open the arduino file at **Beetroot\OpenBionics_Beetroot\OpenBionics_Beetroot\OpenBionics_Beetroot.ino**
### 3. Install [FingerLib.h](https://github.com/Open-Bionics/FingerLib)
* Within Arduino, go to **Sketch -> Include Library -> Manage Libraries...**
* Search for **FingerLib**
* Install **FingerLib**
### 4. Install Chesnut board - WE ARE NOW USING THE ADAFRUIT FEATHER BOARD
* Within Arduino, go to **File -> Preferences**
* Copy the following URL https://open-bionics.github.io/package_openbionics_index.json
* Paste URL in **Additional Boards Manager URLs** box
* Open **Tools -> Board -> Boards Manager..**
* Search for **Open Bionics** - SEARCH FOR **Adafruit SAMD Boards**
* Install the latest verison of the **Open Bionics Boards**
* Select **Tools -> Board -> Chestnut** to select the Chestnut PCB 
### 5. Upload to the Brunel hand
* Plug the hand into the supplied 12V DC jack
* Plug the USB micro into the hand and the computer
* Within Arduino, select **Tools -> Port -> COM## (Chestnut)** (see [here](https://www.arduino.cc/en/guide/troubleshooting#toc16) for more details)
* Select **Sketch -> Upload**
### 6. Use Beetroot
* After a successful upload, the hand will be flashing Orange (near the USB port)
* Within Arduino, select **Tools -> Serial Monitor** (the hand should now be flashing Green)
* On the bottom right hand corner of the Serial Monitor window, make sure the dropdown box for the baud rate is set to **115200 baud** and set the other dropdown box to **Carriage Return**
* Enter **?** over the serial monitor to view the list of serial instructions

This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/

### 7. Extra
* Drivers - you may need to download the SAMD21 boards from Arduino using the Arduino Boards Manager, as this allows the drivers for the SAMD21G18 to be installed
* Brunel Version - this software is configured to run on Brunel V2, however by changing BRUNEL_VER in Globals.h to 1, the software will be reconfigured for the original Brunel (the only difference is the finger/pin mapping) 


## Beetroot Release Notes

	Version	|	Date		|	Notes
	V1.1.0	|	11/07/18	|	Updated for the Brunel V2 (motor stall detection, WDT
	V1.0.4	|	24/10/17	|	Added SerialPins & SerialJack. Updated LED.h 
	V1.0.3	|	10/08/17	|	Added HANDle (Nunchuck) control.
	V1.0.2	|	05/06/17	|	Updated grip positions. Changed 'commSwitchPin' to correct pin.
	V1.0.1	|	10/04/17	|	Removed useless grips. Added EEPROM 'first run' detection. Fixed LEFT hand finger inversion
	V1.0.0	|	22/03/17	|	Initial release for Brunel hand and Chestnut board using SAMD21G18A
		
	



### Beetroot Description

* Simple hand control software designed to run on the Open Bionics Chestnut hand controller
* Uses FingerLib.h for level finger control, which allows fingers to be used as servos
* Can be controlled via the following methods:
	* Serial control (baud 115200)
	* Muscle control (Analogue EMG, I2C EMG)
	* HANDle control (Wii Nunchuck)
* Enter '?' to view available serial commands

		
