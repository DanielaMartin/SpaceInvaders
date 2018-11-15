.equ	SVCLedSet, 0
.equ	SVCButtonStartEv, 1
.equ	SVCDisplayCls, 2
.equ	SVCDisplayPutc, 3

.thumb_func 
.global led_set
led_set:
	svc SVCLedSet
	bx lr

.thumb_func 
.global start_button
start_button:
	svc SVCButtonStartEv
	bx lr

.thumb_func 
.global display_clear
display_clear:
	svc SVCDisplayCls
	bx lr

.thumb_func 
.global display_set_c
display_set_c:
	svc SVCDisplayPutc
	bx lr

