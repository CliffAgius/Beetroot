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
*	Grips_Default.cpp
*
*/

#include "Grips_Default.h"


#if (BRUNEL_VER == 1)

// grip names + empty string
const char* default_GripNames[NUM_GRIPS + 1] = {
	"Fist", \
	"Hook", \
	"Point", \
	"Pinch", \
	"Tripod", \
	"Finger Roll", \
	"Thumb Roll", \
	""		// EMPTY STR
};  


#define OPPOSE_PINCH	600 // 680
#define OPPOSE_TRIPOD	680 // 770



// array to hold the finger positions for each grip
uint16_t default_GripPos[NUM_GRIPS][NUM_GRIP_STEPS][NUM_FINGERS + 1] = {
	{	// FIST
		//COUNT		F0				F1				F2				F3 & F4
		{ 0,		OPPOSE_TRIPOD,	FULLY_OPEN,		FULLY_OPEN,		FULLY_OPEN },	//OPEN
		{ BLANK,	BLANK,			BLANK,			BLANK,			BLANK },		//MIDPOINTA
		{ BLANK,	BLANK,			BLANK,			BLANK,			BLANK },	//MIDPOINTB
		{ BLANK,	BLANK,			BLANK,			BLANK,			BLANK },		//MIDPOINTC
		{ BLANK,	BLANK,			BLANK,			BLANK,			BLANK },		//MIDPOINTD
		{ 100,		OPPOSE_TRIPOD,	FULLY_CLOSED,	FULLY_CLOSED,	850 },			//CLOSED
	},
	{	// HOOK
		//COUNT		F0				F1				F2				F3 & F4
		{ 0,		FULLY_OPEN,		FULLY_OPEN,		FULLY_OPEN,		FULLY_OPEN },	//OPEN
		{ BLANK,	BLANK,			BLANK,			BLANK,			BLANK },		//MIDPOINTA
		{ BLANK,	BLANK,			BLANK,			BLANK,			BLANK },		//MIDPOINTB
		{ BLANK,	BLANK,			BLANK,			BLANK,			BLANK },		//MIDPOINTC
		{ BLANK,	BLANK,			BLANK,			BLANK,			BLANK },		//MIDPOINTD
		{ 100,		FULLY_OPEN,		FULLY_CLOSED,	FULLY_CLOSED,	850 },			//CLOSED
	},
	{	// POINT
		//COUNT		F0				F1				F2				F3 & F4
		{ 0,		OPPOSE_PINCH,	FULLY_OPEN,		FULLY_CLOSED,	850 },			//OPEN
		{ BLANK,	BLANK,			BLANK,			BLANK,			BLANK },		//MIDPOINTA
		{ BLANK,	BLANK,			BLANK,			BLANK,			BLANK },		//MIDPOINTB
		{ BLANK,	BLANK,			BLANK,			BLANK,			BLANK },		//MIDPOINTC
		{ BLANK,	BLANK,			BLANK,			BLANK,			BLANK },		//MIDPOINTD
		{ 100,		OPPOSE_PINCH,	FULLY_CLOSED,	FULLY_CLOSED,	850 },			//CLOSED
	},
	{	// PINCH
		//COUNT		F0				F1				F2				F3 & F4
		{ 0,		OPPOSE_PINCH,	FULLY_OPEN,		FULLY_OPEN,		FULLY_OPEN },	//OPEN
		{ BLANK,	BLANK,			BLANK,			BLANK,			BLANK },		//MIDPOINTA
		{ BLANK,	BLANK,			BLANK,			BLANK,			BLANK },		//MIDPOINTB
		{ BLANK,	BLANK,			BLANK,			BLANK,			BLANK },		//MIDPOINTC
		{ BLANK,	BLANK,			BLANK,			BLANK,			BLANK },		//MIDPOINTD
		{ 100,		OPPOSE_PINCH,	FULLY_CLOSED,	FULLY_OPEN,		FULLY_OPEN },	//CLOSED
	},

	{	// TRIPOD
		//COUNT		F0				F1				F2				F3 & F4
		{ 0,		OPPOSE_TRIPOD,	FULLY_OPEN,		FULLY_OPEN,		FULLY_OPEN },	//OPEN
		{ BLANK,	BLANK,			BLANK,			BLANK,			BLANK },		//MIDPOINTA
		{ BLANK,	BLANK,			BLANK,			BLANK,			BLANK },		//MIDPOINTB
		{ BLANK,	BLANK,			BLANK,			BLANK,			BLANK },		//MIDPOINTC
		{ BLANK,	BLANK,			BLANK,			BLANK,			BLANK },		//MIDPOINTD
		{ 100,		OPPOSE_TRIPOD,	FULLY_CLOSED,	FULLY_CLOSED,	FULLY_OPEN },	//CLOSED
	},
	{	// FINGER ROLL
		//COUNT		F0				F1				F2				F3 & F4
		{ 0,		FULLY_OPEN,		FULLY_OPEN,		FULLY_OPEN,		FULLY_OPEN },	//OPEN
		{ 20,		FULLY_OPEN,		FULLY_OPEN,		FULLY_OPEN,		BLANK },		//MIDPOINTA
		{ 40,		FULLY_OPEN,		FULLY_OPEN,		BLANK,			850 },			//MIDPOINTB
		{ 60,		FULLY_OPEN,		BLANK,			FULLY_CLOSED,	850 },			//MIDPOINTC
		{ 80,		BLANK,			FULLY_CLOSED,	FULLY_CLOSED,	850 },			//MIDPOINTD
		{ 100,		800,			FULLY_CLOSED,	FULLY_CLOSED,	850 },			//CLOSED
	},
	{	// THUMB ROLL
		//COUNT		F0				F1				F2				F3 & F4
		{ 0,		FULLY_OPEN,		FULLY_OPEN,		FULLY_OPEN,		FULLY_OPEN },	//OPEN
		{ 20,		800,			FULLY_OPEN,		FULLY_OPEN,		FULLY_OPEN },	//MIDPOINTA
		{ 40,		800,			FULLY_CLOSED,	FULLY_OPEN,		FULLY_OPEN },	//MIDPOINTB
		{ 60,		800,			FULLY_CLOSED,	FULLY_CLOSED,	FULLY_OPEN },	//MIDPOINTC
		{ 80,		800,			FULLY_CLOSED,	FULLY_CLOSED,	850 },			//MIDPOINTD
		{ 100,		800,			FULLY_CLOSED,	FULLY_CLOSED,	850 },			//CLOSED
	},
};

#elif (BRUNEL_VER == 2)

// grip names + empty string
const char* default_GripNames[NUM_GRIPS + 1] = {
	"Fist", \
	"Hook", \
	"Point", \
	"Pinch", \
	"Tripod", \
	"Finger Roll", \
	"Thumb Roll"
	""		// EMPTY STR
};


#define OPPOSE_PINCH	 620 // 565 // 730	// 620 
#define OPPOSE_TRIPOD	 700 // 685 // 890	// 720 



// array to hold the finger positions for each grip
uint16_t default_GripPos[NUM_GRIPS][NUM_GRIP_STEPS][NUM_FINGERS + 1] = {
	{	// FIST
		//COUNT		F0				F1				F2				F3 & F4
		{ 0,		OPPOSE_TRIPOD,	FULLY_OPEN,		FULLY_OPEN,		FULLY_OPEN },	//OPEN
		{ BLANK,	BLANK,			BLANK,			BLANK,			BLANK },		//MIDPOINTA
		{ BLANK,	BLANK,			BLANK,			BLANK,			BLANK },		//MIDPOINTB
		{ BLANK,	BLANK,			BLANK,			BLANK,			BLANK },		//MIDPOINTC
		{ BLANK,	BLANK,			BLANK,			BLANK,			BLANK },		//MIDPOINTD
		{ 100,		OPPOSE_TRIPOD,	850,			850,			FULLY_CLOSED },	//CLOSED
	},
	{	// HOOK
		//COUNT		F0				F1				F2				F3 & F4
		{ 0,		FULLY_OPEN,		FULLY_OPEN,		FULLY_OPEN,		FULLY_OPEN },	//OPEN
		{ BLANK,	BLANK,			BLANK,			BLANK,			BLANK },		//MIDPOINTA
		{ BLANK,	BLANK,			BLANK,			BLANK,			BLANK },		//MIDPOINTB
		{ BLANK,	BLANK,			BLANK,			BLANK,			BLANK },		//MIDPOINTC
		{ BLANK,	BLANK,			BLANK,			BLANK,			BLANK },		//MIDPOINTD
		{ 100,		FULLY_OPEN,		FULLY_CLOSED,	FULLY_CLOSED,	FULLY_CLOSED },			//CLOSED
	},
	{	// POINT
		//COUNT		F0				F1				F2				F3 & F4
		{ 0,		OPPOSE_PINCH,	FULLY_OPEN,		FULLY_CLOSED,	FULLY_CLOSED },	//OPEN
		{ BLANK,	BLANK,			BLANK,			BLANK,			BLANK },		//MIDPOINTA
		{ BLANK,	BLANK,			BLANK,			BLANK,			BLANK },		//MIDPOINTB
		{ BLANK,	BLANK,			BLANK,			BLANK,			BLANK },		//MIDPOINTC
		{ BLANK,	BLANK,			BLANK,			BLANK,			BLANK },		//MIDPOINTD
		{ 100,		OPPOSE_PINCH,	850,			FULLY_CLOSED,	FULLY_CLOSED },	//CLOSED
	},
	{	// PINCH
		//COUNT		F0				F1				F2				F3 & F4
		{ 0,		OPPOSE_PINCH,	FULLY_OPEN,		FULLY_OPEN,		FULLY_OPEN },	//OPEN
		{ BLANK,	BLANK,			BLANK,			BLANK,			BLANK },		//MIDPOINTA
		{ BLANK,	BLANK,			BLANK,			BLANK,			BLANK },		//MIDPOINTB
		{ BLANK,	BLANK,			BLANK,			BLANK,			BLANK },		//MIDPOINTC
		{ BLANK,	BLANK,			BLANK,			BLANK,			BLANK },		//MIDPOINTD
		{ 100,		OPPOSE_PINCH,	850,			FULLY_OPEN,		FULLY_OPEN },	//CLOSED
	},

	{	// TRIPOD
		//COUNT		F0				F1				F2				F3 & F4
		{ 0,		OPPOSE_TRIPOD,	FULLY_OPEN,		FULLY_OPEN,		FULLY_OPEN },	//OPEN
		{ BLANK,	BLANK,			BLANK,			BLANK,			BLANK },		//MIDPOINTA
		{ BLANK,	BLANK,			BLANK,			BLANK,			BLANK },		//MIDPOINTB
		{ BLANK,	BLANK,			BLANK,			BLANK,			BLANK },		//MIDPOINTC
		{ BLANK,	BLANK,			BLANK,			BLANK,			BLANK },		//MIDPOINTD
		{ 100,		OPPOSE_TRIPOD,	850,			850,			FULLY_OPEN },	//CLOSED
	},
	{	// FINGER ROLL
		//COUNT		F0				F1				F2				F3 & F4
		{ 0,		FULLY_OPEN,		FULLY_OPEN,		FULLY_OPEN,		FULLY_OPEN },	//OPEN
		{ 20,		FULLY_OPEN,		FULLY_OPEN,		FULLY_OPEN,		BLANK },		//MIDPOINTA
		{ 40,		FULLY_OPEN,		FULLY_OPEN,		BLANK,			FULLY_CLOSED },	//MIDPOINTB
		{ 60,		FULLY_OPEN,		BLANK,			850,			FULLY_CLOSED },	//MIDPOINTC
		{ 80,		BLANK,			850,			850,			FULLY_CLOSED },	//MIDPOINTD
		{ 100,		FULLY_CLOSED,	850,			850,			FULLY_CLOSED },	//CLOSED
	},
	{	// THUMB ROLL
		//COUNT		F0				F1				F2				F3 & F4
		{ 0,		FULLY_OPEN,		FULLY_OPEN,		FULLY_OPEN,		FULLY_OPEN },	//OPEN
		{ 20,		FULLY_CLOSED,	FULLY_OPEN,		FULLY_OPEN,		FULLY_OPEN },	//MIDPOINTA
		{ 40,		FULLY_CLOSED,	850,			FULLY_OPEN,		FULLY_OPEN },	//MIDPOINTB
		{ 60,		FULLY_CLOSED,	850,			850,			FULLY_OPEN },	//MIDPOINTC
		{ 80,		FULLY_CLOSED,	850,			850,			FULLY_CLOSED },	//MIDPOINTD
		{ 100,		FULLY_CLOSED,	850,			850,			FULLY_CLOSED },	//CLOSED
	},
};


#else
#error No BRUNEL_VER version defined in Globals.h
#endif
