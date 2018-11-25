/**
 * @file	console.c
 * @author  
 * @version 
 *
 * @brief A console for MiniOS. To add a new supported command follow these steps:
 *			1. Add its name to cmd_names
 *			2. Create a function with the same name in commands.c
 *			3. Add a ptr to that function to cmd_ptrs
 *		  Note: only one param (command-line argument) is supported. 
 *			    e.g. $cat file.txt works fine, but can't pass more arguments.
 *			To add support change: extract_param function, loader module, and commands module. 
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "minios/HAL/hal.h"
#include "minios/console/console.h"
#include "minios/console/commands.h"
#include "minios/system.h"
#include "minios/loader.h"

static void print( uint8_t* );
static void println( uint8_t* );
static void readln( uint8_t* );
static void extract_command( uint8_t*, uint8_t* );
static uint32_t extract_param( uint8_t*, uint8_t* );
static int32_t command_index( uint8_t* );
static bool is_alpha( uint8_t );
static bool is_number( uint8_t );

#define MAX_COMMAND_LEN			20		//command length (arbitrary)
#define MAX_PARAM_LEN			20		//param length (arbitrary)
#define MAX_LINE_LEN			MAX_COMMAND_LEN + MAX_PARAM_LEN*2 + 1	
#define MAX_NUM_OF_PARAMS		1		//Only 1 param is supported, for now. 

#define DUMMY_USER		"no-user"	//No support for users yet
#define DEFAULT_PATH	"~"			//Initially the system is in the root directory. No support for dirs yet.
#define CONSOLE_SYMBOL	"$"			//The symbol that shows before the prompt
#define INVALID_CMD		-1
#define SENTINEL_CMD	"[[]]"		//some string that won't match any command
									//Don't know what a sentinel is? See https://en.wikipedia.org/wiki/Sentinel_value

//List of command names (Add new commands here)
//(NOTE: indexes between cmd_names and cmds_ptrs must match)
static uint8_t* cmd_names[] = { "ls",		//CAREFUL WITH MISSING COMMAS	
								"cat",		//gcc will concatenate the string before and after them and compile the project! 
								"date",		//Then it'll jut crash at runtime!...Idk if its legal C, but
								"sysinfo",	//it's a hard-to-find bug.
								SENTINEL_CMD	
								};
							
//The actual commands (Add ptrs to commands here)		
//(NOTE: indexes between cmd_names and cmds_ptrs must match)
static uint32_t* cmd_ptrs[] = { commands_ls,	
								commands_cat,
								commands_date,
								commands_sysinfo,
								};

static uint8_t* newline; 

/*
*
*/
void console_init( ){
	//Nothing to init
}

/*
*
*/
uint8_t* console_newline_in_use( void ){
	return newline;
}

/*
*
*
*
*/
void console_begin( uint8_t* nl ){

	newline = nl;

	uint8_t line[MAX_LINE_LEN];
	uint32_t prompt_msg_len =	SYS_USERNAME_MAX_LENGTH	  //user
								+ 1						  //@
								+ strlen(SYS_NAME)		  //sysname
								+ 1						  //:
								+ strlen(DEFAULT_PATH)	  //path
								+ strlen(CONSOLE_SYMBOL)  //symbol
								+ 1						  //' '
								+ 1;					  //null char
	uint8_t prompt_message[ prompt_msg_len ];

	//create prompt message
	sprintf( prompt_message, "%s@%s:%s%s ", DUMMY_USER, SYS_NAME, DEFAULT_PATH, CONSOLE_SYMBOL );

	//wait for any character
	hal_serial_getc(SerialA); //accounts for spurious 0x00 character received
	
	uint8_t cmd[MAX_COMMAND_LEN + 1];
	uint8_t param[MAX_PARAM_LEN + 1]; //only 1 param is supported for now
	
	while( true ){
		//Shows prompt
		print( prompt_message );

		//reads user input onto buffer
		readln( line );
			
		//extract command and params from input
		extract_command( line, cmd ); 
		uint32_t num_params =  extract_param( line, param );
		
		//try and process as command
		int32_t cmd_index = command_index( cmd );
		
		if( cmd_index != INVALID_CMD ){
			//execute command
			((void(*)(uint8_t*, uint32_t))(cmd_ptrs[cmd_index]))( param, num_params ); 
		}
		else{
			//Not a command. Try and process as an App
			
			uint32_t retval;
			uint32_t retcode;
			
			retval = loader_exec_app( cmd, param, num_params, &retcode ); 
			
			if( retval == LOADER_NO_APP_FOUND) 			println( "Command not recognized" );
			else if( retval == LOADER_APP_TOO_LARGE )	println( "Application is too large" );
			else if( retcode != 0 ){
				uint8_t* base_msg = "Application exited with code ";
				#define MAX_DIGITS_IN_UINT	10
				uint8_t buf[ strlen(base_msg) + MAX_DIGITS_IN_UINT ];
				sprintf( buf, "%s %d", base_msg, retcode );
				
				println( buf );
			}
			else{	/*execution went fine, print nothing */		}
		}
		
	}
}


static void extract_command( uint8_t* line, uint8_t* cmd ){
	uint8_t c;
	
	//copy everything until a space or null char
	do{
		c = *cmd++ = *line++;
	}while( c != ' ' && c != '\0' );
	
	//turn cmd into a string
	cmd[-1] = '\0';
}

static uint32_t extract_param( uint8_t* line, uint8_t* param ){
	uint8_t c;
	
	//advance line up to end of command
	do{
		c = *line++;
	}while( c != ' ' && c != '\0' );		
	
	if(line[-1] == '\0')
		return 0; //no parameters found
	
	//copy the rest to param (only 1 param is supported for now)
	while( *param++ = *line++ );
	
	//(only 1 param is supported)
	return 1; 
}

static int32_t command_index( uint8_t* cmd ){
	#define EQUAL 0
	uint8_t** all_cmds = cmd_names;
	int32_t index = 0;
	 
	//search for command in the command list
	//and returns its index
	while( strcmp( *all_cmds, SENTINEL_CMD ) != EQUAL ){
		if( strcmp( *all_cmds, cmd ) == EQUAL ){
			//we have a match
			return index; 
		}
		all_cmds++;	
		index++;
	}
	
	return INVALID_CMD; //no match found
}

static void readln( uint8_t* buffer ){

	//read everything until a new line is received
	uint8_t c;
	do{
		c = hal_serial_getc(SerialA); 
		
		if( c != '\n' && c!= '\r')
			hal_serial_putc( SerialA, c ); //transmits most chars for visual feedback
		
		//filters non-alphanumeric(UNION)newline(UNION)' '(UNION)'.' characters
		if( is_alpha(c) || is_number(c) || c == '\n' || c == ' ' || c == '.'  ){
			 *buffer++ = c;
		}
	}while( c != '\n' );

	//turn buffer into a string by replacing the newline character for a null character
	buffer[-1] = '\0';
	
	//go to newline
	println("");
}

static bool is_alpha(uint8_t c){
	return ( c >= 'A' && c<='Z' ) || ( c>= 'a' && c<= 'z' );
}

static bool is_number(uint8_t c){
	return c >= '0' && c<='9';
}

static void print( uint8_t* string ){
	while( *string )
		hal_serial_putc( SerialA, *string++ );
}

static void println( uint8_t* string ){
	print( string );
	print( newline );
}
