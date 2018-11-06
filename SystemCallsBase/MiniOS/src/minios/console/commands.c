/**
 * @file	commands.c
 * @author  
 * @version 
 *
 * @brief The commands module part of the console. Contains definitions for commands available in the
 *		  console.
 *		  Note: only one param (command-line argument) is supported.
 *
 */
#include <stdio.h>
#include <string.h>
#include "minios/HAL/hal.h"
#include "minios/console/console.h"
#include "minios/console/commands.h"
#include "minios/system.h"

static void print( uint8_t* );
static void println( uint8_t* );

/*
*
*/
void commands_ls( uint8_t* param, uint32_t num_params ){
	
	#define NUM_OF_FILES_TO_READ	20	//arbitrary
	uint8_t file_list[NUM_OF_FILES_TO_READ][ MEM_FAT_MAX_FNAME_LENGTH + 1 ];
	uint8_t line_to_print[ MEM_FAT_MAX_FNAME_LENGTH + strlen("       ") + 9 + strlen( " Bytes" )  + 1 ];  //assuming a file cant have more than 9 digits of size in KB
	uint32_t num_files;
	double size_of_file;
	
	//print file list
	if( ( num_files = hal_nvmem_fat_file_list( file_list, NUM_OF_FILES_TO_READ ) ) > 0 ){
		
		for( uint32_t i=0; i<num_files; i++ ){
			//finds file size
			size_of_file = hal_nvmem_fat_file_size( file_list[i] );
			size_of_file /= 1024;
			
			//prepares line to be printed
			sprintf( line_to_print, "%s       %2.1f KB", file_list[i], size_of_file );
			
			//print
			println( line_to_print );
		}
	}
	else{
		println( "No files found" );
	}
}

/*
*
*/
void commands_cat( uint8_t* param, uint32_t num_params ){
	#define MAX_CHARS_IN_FILE	2048 //2Kb for now
	uint8_t buffer[MAX_CHARS_IN_FILE];
	
	//checks param
	if( num_params == 0){
		println( "Specify file" );
		return;	
	}
		
	//checks file (FOR SOME REASON IT DOES NOT WORK SOMETIMES.... SYSTEM HANGS. fix this)
/*	uint32_t size = hal_nvmem_fat_file_size(param);
	if( size == 0 ){ 
		println( "Cat: file does not exist" ); 
		return; 
	}
	else if( size > MAX_CHARS_IN_FILE ){
		 println( "Cat: Only files of size 2Kb or less are supported" );
	}*/
	
	//reads
	uint32_t bytes_read =  hal_nvmem_fat_file_read( param, buffer, MAX_CHARS_IN_FILE );
	
	//turns buffer into a string
	buffer[bytes_read-1] = '\0';
	
	//print
	println( buffer );
}

/*
*
*/
void commands_date( uint8_t* param, uint32_t num_params  ){
	#define MAX_DATE_LENGTH	26
	tTime t;
	uint8_t* months[] = {	"January", "February", "March", "April", "May",
							"June", "July", "August", "September", "October",
							"November", "December"  };
							
	hal_clock_read(&t);
	
	uint8_t line[MAX_DATE_LENGTH + 1];
	sprintf( line, "%s %d, %d %02d:%02d:%02d", months[t.month-1], t.day, t.year, t.hours, t.minutes, t.seconds );
	
	println( line );
}

/*
*
*/
void commands_sysinfo( uint8_t* param, uint32_t num_params  ){
	#define MAX_INFO_LENGTH 15
	uint8_t line[MAX_INFO_LENGTH + 1];
	sprintf( line, "%sv%s", SYS_NAME, SYS_VERSION );
	
	println( line );
}

static void print( uint8_t* string ){
	while( *string ) 
		hal_serial_putc( SerialA, *string++ );
}

static void println( uint8_t* string ){
	print( string );
	print( console_newline_in_use() );
}
