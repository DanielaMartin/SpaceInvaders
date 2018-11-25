/**
 * @file	syscalls.h
 * @author  
 * @version 
 *
 * @brief System Calls Interface header file
 *
 */

#ifndef SYSCALLS_H_
#define SYSCALLS_H_

void syscalls_init(void);

/**
*	System call numbers
*/
enum{
	//LED
	SVCLedWrite			= 0,
	SVCLedRead			= 1,

	//Button
	SVCButtonStartEv	= 2,

	//Clock
	SVCClockRead		= 3,
	SVCClockWrite		= 4,
	
	//Serial
	SVCSerialPutc		= 5,
	SVCSerialGetc		= 6,
	
	//Sensors
	SVCSensorStartEv	= 7,
	SVCSensorRead		= 8,
	
	//Display
	SVCDisplayCls		= 9,
	SVCDisplayPutc		= 10,
	SVCDisplayGotoxy	= 11,
	SVCDisplayNumLines	= 12,
	
	//Millisecond timer
	SVCMtimerStartEv	= 13,
	SVCMtimerStartPoll	= 14,
	SVCMtimerStop		= 15,
	SVCMtimerRead		= 16,

};



#endif /* SYSCALLS_H_ */