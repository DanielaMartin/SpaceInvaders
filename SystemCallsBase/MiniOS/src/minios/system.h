/**
 * @file	system.h
 * @author  
 * @version 
 *
 * @brief System Module header file
 *	Note: system.h must be included before any other MiniOS header file as it
 *	has common includes required by other source code.
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

//
//   ---------   SYSTEM OPTIONS    ---------
// (Configure system by editing this values)
// (can implement config files instead...)
#define SYS_VERSION					"3"
#define SYS_NAME					"MiniOS"
#define SYS_USERNAME_MAX_LENGTH		10
#define SYS_CONF_SERIAL_A_BAUDRATE	115200
#define SYS_CONF_SERIAL_B_BAUDRATE	115200
#define SYS_APP_MAX_SIZE	20480			//20 KB max size (the buffer occupies space!)
											//It is not difficult to remove this limitation. The app loader can be written
											//to load "on-the-fly" i.e. read one byte, load it, and discard it.
											//The most difficult change is to extend HAL NVMem to enable this behavior

void system_init(void);

#endif /* SYSTEM_H_ */