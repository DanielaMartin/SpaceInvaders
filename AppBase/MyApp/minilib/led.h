/*
 * led.h
 *
 * Created: 2017-12-02 7:07:09 PM
 *  Author: rroma
 */ 


#ifndef LED_H_
#define LED_H_


enum tLedState{ LedOff=false, LedOn };
enum tLedNum{ Led0 = 0, Led1, Led2, Led3 };

void led_set( tLedNum , tLedState );


#endif /* LED_H_ */