#include <stdint-gcc.h>
#include <stdbool.h>
#include "minilib/led.h"

#define MINIOSAPP __attribute__ ((section(".entry_point"))) uint32_t
#define STACKINFO __attribute__ ((section(".stack_info"))) uint32_t

extern uint32_t _estack;
STACKINFO sp  = &_estack;

MINIOSAPP main(void){
	
	led_set( Led1, LedOn );
	
	return 0;
}