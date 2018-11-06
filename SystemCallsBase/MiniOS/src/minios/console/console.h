/**
 * @file	console.c
 * @author  
 * @version 
 *
 * @brief The console's header file
 *
 */


#ifndef CONSOLE_H_
#define CONSOLE_H_


void console_init( void );
void console_begin( uint8_t* );
uint8_t* console_newline_in_use( void );

#endif /* CONSOLE_H_ */