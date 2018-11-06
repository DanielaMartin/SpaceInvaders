/**
 * @file	syscalls.c
 * @author  
 * @version 
 *
 * @brief System Calls Interface 
 *
 */

#include "system.h"
#include "HAL/hal.h"
#include "syscalls.h"

void syscalls_entry_point(void);


/**
*	Syscalls Init
*
*	Initializes the system calls interface
*
*/
void syscalls_init(void){
	//Starts SVCs (registers SVC callback)
	hal_svc_start( syscalls_entry_point );
}

/**
*	Syscalls Entry Point
*
*	This is the execution entry point of a system call. That is, where execution
*	goes on SVC call.
*
*   Important: We assume the processor is always in user mode when executing SVC.
*	If the processor is not this fails! Should one want to extend it to support 
*	system calls made while in handler mode, the following is necessary:
*	   1. Figure out the state of the CPU before exception entry (thread or handler)
*         by inspecting EXEC_RETURN
*	   2. Based on that extract the right SP (PSP or MSP)
*	   3. The rest is the same...
*
*	There' no reason to make a syscall from the kernel though, so it's all good.
*/
void syscalls_entry_point(void){
	
	uint32_t sp = hal_cpu_get_psp();
	
	//Get syscall number from SVC instruction in program memory
	//- - - - - - -- - - - - - - - - - - - - - - - - - - - - - -
	//To find its address we look at the return address stacked on
	//exception entry (offset 6 from SP).
	//That stacked return address is the address of the instruction to
	//be executed on exception return (typically bx lr).
	//We know bx lr is a 16-bit instruction. So to get the SVC intruction
	//we just read 2 bytes before the specified address.
	uint32_t svc_number = ((uint16_t*) ((uint32_t*)sp)[6])[-1];
	
	//extract the number from the read instruction
	svc_number &= 0x00FF;
	
	//get arguments
	void* arg0 = ((uint32_t*)sp)[0];
	void* arg1 = ((uint32_t*)sp)[1];
	void* arg2 = ((uint32_t*)sp)[2];
	void* arg3 = ((uint32_t*)sp)[3];
	
	//attend syscall
	switch(svc_number){
		case SVCLedWrite:
			hal_led_write( (tLedNum)arg0, (tLedState)arg1 );
			break;
		default:	/* Error */
			break;
	}
}