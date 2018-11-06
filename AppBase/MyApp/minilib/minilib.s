.equ	SVCLedSet, 0

.thumb_func 
.global led_set
led_set:
	svc SVCLedSet
	bx lr

