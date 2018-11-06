/**
 * @file	hal_asm.s
 * @author  
 * @version 
 *
 * @brief Assembly for the CPU Part of the Hardware Abstraction Layer 
 *
 */

 .syntax unified
.section .text

//SVC Handler
//(no prologue and no epilogue to avoid
// changing the offsets of the stacked frame on SVC interrupt)
.thumb_func 
.global SVC_Handler
SVC_Handler:
	ldr	r3, =svc_callback
	ldr r3, [r3]
	bx	r3


/**
*	uint32_t hal_cpu_get_psp(void) 
*
*	Gets the PSP
*
*	Returns the process stack pointer
*/
.thumb_func 
.global hal_cpu_get_psp
hal_cpu_get_psp:
	mrs	r0, psp  //return psp
	bx lr 

/**
*	void hal_cpu_set_unprivileged(void) 
*
*	CPU Set unprivileged
*
*	Set the CPU as unprivileged (when in thread mode)s
*/
.thumb_func 
.global hal_cpu_set_unprivileged
hal_cpu_set_unprivileged:
	mrs r3, control
	orr	r3, r3, #1
	msr control, r3 /* control |= 1 */
	isb

	bx lr

/**
*	void hal_cpu_psp_active(void) 
*
*	CPU Set PSP active
*
*	Sets the Process Stack Pointer as active (when in thread mode)
*/
.thumb_func 
.global hal_cpu_set_psp_active
hal_cpu_set_psp_active:
	mrs r3, control
	orr	r3, r3, #2
	msr control, r3 /* control |= 2 */
	isb

	bx lr
/**
*	void hal_cpu_set_psp(uint32_t) 
*
*	Sets the PSP
*
*	Sets the Process Stack Pointer value
*/
.thumb_func 
.global hal_cpu_set_psp
hal_cpu_set_psp:
     msr psp, r0

     bx lr

