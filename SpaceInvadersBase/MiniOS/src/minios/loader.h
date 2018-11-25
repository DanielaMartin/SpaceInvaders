/**
 * @file	iostream.c
 * @author  
 * @version 
 *
 * @brief MiniOS IO Streams
 *	
 */


#ifndef LOADER_H_
#define LOADER_H_


#define LOADER_NO_APP_FOUND			0
#define LOADER_APP_TOO_LARGE		1
#define LOADER_EXEC_SUCCESS			2 //app executed succesfully (regardless of core returned by app)

uint32_t loader_exec_app( uint8_t*, uint8_t*, uint32_t, uint32_t* );


#endif /* LOADER_H_ */