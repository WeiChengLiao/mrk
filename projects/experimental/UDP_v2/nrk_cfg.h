/***************************************************************
*                            NanoRK CONFIG                     *
***************************************************************/
#ifndef __nrk_cfg_h	
#define __nrk_cfg_h

// NRK_REPORT_ERRORS will cause the kernel to print out information about
// missed deadlines or reserve violations
#define NRK_REPORT_ERRORS 
// NRK_HALT_ON_ERRORS will cause the kernel to freeze on errors so that
// it is easier to see debugging messages.
//#define NRK_HALT_AND_LOOP_ON_ERROR
#define NRK_HALT_ON_ERROR

// If you want to disable the looping kernel error message when the system
// halts, then include the following define.  This will automatically
// halt the error as well.
//#define NRK_HALT_ON_ERROR 

// NRK_STACK_CHECK adds a little check to see if the bottom of the stack
// has been over written on all suspend calls
#define NRK_STACK_CHECK

//#define KERNEL_STK_ARRAY
// Leave NRK_NO_POWER_DOWN define in if the target can not wake up from sleep 
// because it has no asynchronously clocked
#define NRK_NO_POWER_DOWN 

//#define NRK_WATCHDOG
#define NRK_STATS_TRACKER

// Max number of tasks in your application
// Be sure to include the idle task
// Making this the correct size will save on BSS memory which
// is both RAM and ROM...
#define NRK_MAX_TASKS       			8    
                           

#define NRK_TASK_IDLE_STK_SIZE         256 // Idle task stack size min=32 
#define NRK_APP_STACKSIZE              256     
#define NRK_KERNEL_STACKSIZE           256
#define NRK_MAX_RESOURCE_CNT           9 
#define NRK_MAX_DRIVER_CNT 			   1

// This must be greater than or equal to the highest priority task that uses
// the serial port (i.e. print of nrk_kprintf)
#define SLIP_PCP_CEILING		20		// used by network layer tasks and serial task
// Enable buffered and signal controlled serial RX
#define NRK_UART_BUF   1
// Set buffer to MAX slip packet size
#define MAX_RX_UART_BUF 128 


#endif





