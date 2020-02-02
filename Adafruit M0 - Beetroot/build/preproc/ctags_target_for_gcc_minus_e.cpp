# 1 "c:\\CA-Software\\Open Source Projects\\OpenBionics Hand\\Beetroot\\OpenBionics_Beetroot\\OpenBionics_Beetroot\\OpenBionics_Beetroot.ino"
# 1 "c:\\CA-Software\\Open Source Projects\\OpenBionics Hand\\Beetroot\\OpenBionics_Beetroot\\OpenBionics_Beetroot\\OpenBionics_Beetroot.ino"
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
# 16 "c:\\CA-Software\\Open Source Projects\\OpenBionics Hand\\Beetroot\\OpenBionics_Beetroot\\OpenBionics_Beetroot\\OpenBionics_Beetroot.ino"
# 17 "c:\\CA-Software\\Open Source Projects\\OpenBionics Hand\\Beetroot\\OpenBionics_Beetroot\\OpenBionics_Beetroot\\OpenBionics_Beetroot.ino" 2
# 18 "c:\\CA-Software\\Open Source Projects\\OpenBionics Hand\\Beetroot\\OpenBionics_Beetroot\\OpenBionics_Beetroot\\OpenBionics_Beetroot.ino" 2
# 19 "c:\\CA-Software\\Open Source Projects\\OpenBionics Hand\\Beetroot\\OpenBionics_Beetroot\\OpenBionics_Beetroot\\OpenBionics_Beetroot.ino" 2
# 20 "c:\\CA-Software\\Open Source Projects\\OpenBionics Hand\\Beetroot\\OpenBionics_Beetroot\\OpenBionics_Beetroot\\OpenBionics_Beetroot.ino" 2

# 22 "c:\\CA-Software\\Open Source Projects\\OpenBionics Hand\\Beetroot\\OpenBionics_Beetroot\\OpenBionics_Beetroot\\OpenBionics_Beetroot.ino" 2

# 24 "c:\\CA-Software\\Open Source Projects\\OpenBionics Hand\\Beetroot\\OpenBionics_Beetroot\\OpenBionics_Beetroot\\OpenBionics_Beetroot.ino" 2
# 25 "c:\\CA-Software\\Open Source Projects\\OpenBionics Hand\\Beetroot\\OpenBionics_Beetroot\\OpenBionics_Beetroot\\OpenBionics_Beetroot.ino" 2
# 26 "c:\\CA-Software\\Open Source Projects\\OpenBionics Hand\\Beetroot\\OpenBionics_Beetroot\\OpenBionics_Beetroot\\OpenBionics_Beetroot.ino" 2
# 27 "c:\\CA-Software\\Open Source Projects\\OpenBionics Hand\\Beetroot\\OpenBionics_Beetroot\\OpenBionics_Beetroot\\OpenBionics_Beetroot.ino" 2
# 28 "c:\\CA-Software\\Open Source Projects\\OpenBionics Hand\\Beetroot\\OpenBionics_Beetroot\\OpenBionics_Beetroot\\OpenBionics_Beetroot.ino" 2
# 29 "c:\\CA-Software\\Open Source Projects\\OpenBionics Hand\\Beetroot\\OpenBionics_Beetroot\\OpenBionics_Beetroot\\OpenBionics_Beetroot.ino" 2
# 30 "c:\\CA-Software\\Open Source Projects\\OpenBionics Hand\\Beetroot\\OpenBionics_Beetroot\\OpenBionics_Beetroot\\OpenBionics_Beetroot.ino" 2


void setup()
{
 deviceSetup(); // initialise the board

 if (settings.printInstr)
 {
  delay(100); // allow time for serial to connect
  serial_SerialInstructions(); // print serial instructions
 }
}


void loop()
{




 // monitor system temp
 systemMonitor();

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


 Watchdog.reset();

}
