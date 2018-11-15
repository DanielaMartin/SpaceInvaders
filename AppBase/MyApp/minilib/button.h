/*
 * button.h
 *
 * Created: 06.11.2018 16:51:35
 *  Author: fraud
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

enum tButtonNum	{ Button0 = 0, Button1, Button2, Button3, Button4 };	/**< enumeration for buttons in the board*/
//enum tButtonState {ButtonUnpressed=false, ButtonPressed };
	
typedef enum tButtonNum tButtonNum;
	
void start_button (void (*) (tButtonNum));

#endif /* BUTTON_H_ */