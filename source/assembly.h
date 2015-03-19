#ifndef _ASSEMBLY_H_ 
#define _ASSEMBLY_H_

#ifdef __cplusplus 
extern "C" {
#endif

void* GetGpioAddress();
void SetGpioFunction(unsigned int gpioRegister, unsigned int function);
void SetGpio(unsigned int gpioRegister, unsigned int value);

void* GetSystemTimerBase();
unsigned long long GetTimeStamp();
void Wait(unsigned int delayInMicroSeconds);

#ifdef __cplusplus 
}
#endif

#endif
