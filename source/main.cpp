#include "assembly.h"
#include "basic.h"

void init() {
	SetGpioFunction(47, 1);
	while(true) {
		SetGpio(47, 1);
        Wait(500000);
		SetGpio(47, 0);
        Wait(500000);
	}
}

extern "C" void Main() {
    init();
}
