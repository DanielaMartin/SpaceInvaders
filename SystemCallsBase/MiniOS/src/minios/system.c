/**
 * @file	system.c
 * @author  
 * @version 
 *
 * @brief System module
 *
 * System-related definitions, and definitions that are common 
 * for different layers of the system.
 *
 */

#include "system.h"
#include "HAL/hal.h"
#include "console/console.h"
#include "syscalls.h"


void io_init(void);
void init_sequence(void);

/**
*	System Init
*
*	Initializes IO and CPU. Must be called before any other call
*
*/
void system_init(void){
	
	//Initializes the HAL
	hal_cpu_init();			
	hal_io_init();		
	hal_nvmem_init();
	hal_memreg_init();

	//Initializes IO devices
	io_init();
	
	//Inits console
	console_init();
	
	//Initializes the system calls interface
	syscalls_init();
}

void io_init(void){
	
	//Starts All IO devices
	hal_sensor_start( SensorLight );
	hal_sensor_start( SensorTemp );
	hal_clock_start();
	hal_display_start();
	hal_serial_start( SerialA, SYS_CONF_SERIAL_A_BAUDRATE );
	hal_serial_start( SerialB, SYS_CONF_SERIAL_A_BAUDRATE );
	hal_led_start();
	hal_nvmem_start( NVMemSDCardFAT );
	
	//Clock starts in 00:13:00 July 14, 1991
	tTime time = {
		
		0, 13, 0, 14, 7, 1991 //
	};
	hal_clock_write(&time);
	
	//All LEDS starts Off and Display starts empty in (0,0),
	//but first they blink momentarily
	init_sequence();

}

void init_sequence(void){
		
	//All LEDs On
	hal_led_write(Led0, LedOn);
	hal_led_write(Led1, LedOn);
	hal_led_write(Led2, LedOn);
	hal_led_write(Led3, LedOn);
	hal_led_write(Led4, LedOn);
		
	//Screen "on"
	for(uint32_t i=0; i<4; i++){	 //rows
		hal_display_gotoxy(0, i);
		for(uint32_t j=0; j<95; j++) //columns
		hal_display_putc('|');
	}

	//Wait...
	hal_delay(200);
	
	//All LEDs Off
	hal_led_write(Led0, LedOff);
	hal_led_write(Led1, LedOff);
	hal_led_write(Led2, LedOff);
	hal_led_write(Led3, LedOff);
	hal_led_write(Led4, LedOff);
		
	//clear screen
	hal_display_cls();
}
