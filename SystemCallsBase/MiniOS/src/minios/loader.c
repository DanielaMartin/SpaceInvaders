/**
 * @file	loader.c
 * @author  
 * @version 
 *
 * @brief App loader. Note: only one param (command-line argument) 
 * is supported.
 *	
 */

#include <stdio.h>
#include <string.h>
#include "minios/HAL/hal.h"
#include "minios/system.h"
#include "minios/loader.h"

static void load_app( uint8_t*, uint8_t*, uint32_t );

tMemRegion app_memreg;
uint8_t binary[SYS_APP_MAX_SIZE];		//where the app is loaded

/*
*
*/
uint32_t loader_exec_app( uint8_t* app_name, uint8_t* param, uint32_t num_params, uint32_t* ret_code  ){
	
	//Get App region details
	hal_memreg_read( MemRegApp, &app_memreg );
	
	//validates app file
	uint32_t app_size = hal_nvmem_fat_file_size( app_name );
	
	if( app_size == 0 )						 return LOADER_NO_APP_FOUND;
	else if ( app_size > SYS_APP_MAX_SIZE  ) return LOADER_APP_TOO_LARGE;
	
	//reads app
	uint32_t bytes_read = hal_nvmem_fat_file_read( app_name, binary, SYS_APP_MAX_SIZE );

	//Extract app's initial SP and application from binary
	uint32_t app_sp = *((uint32_t*)binary);
	uint32_t* app_buffer = (uint32_t*)binary + 1;

	//load app in App memory region
	load_app( app_memreg.base, app_buffer, bytes_read );
	
	// Set CPU in user mode
	//(can't refer any automatic variables past this point)
	hal_cpu_set_psp( app_sp );
	hal_cpu_set_psp_active();
	hal_cpu_set_unprivileged();

	//run!
	*ret_code = ((uint32_t(*)(uint32_t*, uint32_t))app_memreg.base + 1)(param, num_params);

	return LOADER_EXEC_SUCCESS;
}

static void load_app( uint8_t* mem, uint8_t* binary, uint32_t size ){
	
	for(uint32_t i = 0; i<size; i++)
		mem[i] = binary[i];

}
