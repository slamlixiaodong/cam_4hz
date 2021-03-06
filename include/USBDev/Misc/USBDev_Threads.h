#ifndef __USBDEV_THREADS
#define __USBDEV_THREADS

#include "../DEVDEF.h"
#include "../USBDev.h"

/* Sleep 
* Sleep for millisec.
*/
void ThreadSleep(int millisec);

/* Get Current MilliSecond TimeStamp
* Return an integer contains the total millisecond.
*/
UINT64 DEV_GetCurrentMilliSecond();

/* Get Current System Time
* Return USBDev_Time struct.
*/
USBDev_Time DEV_GetCurrentTime();

/* Create Thread.
* Create a thread. func: pointer to thread start. param: input parameter for this thread.
* Return NULL if failed.
*/
void* CreateThread(void* func, void* param);

/* Close Thread.
*/
void CloseThread(void* pthread);

/* Wait For Thread
* Wait for a thread and return if timeout or happened.
* Return 0 if succeed; non-zero if timeout.
*/
UINT32 WaitForThread(void* pthread, int timeout);

#endif