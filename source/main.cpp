#include "assembly.h"
#include "basic.h"

void init() {
	SetGpioFunction(47, 1);
    int i = 10;
    i++;
	while(true) {
		SetGpio(47, 1);
		Wait(1000000);
		SetGpio(47, 0);
		Wait(1000000);
	}
}

extern "C" void Main() {
    init();
}
