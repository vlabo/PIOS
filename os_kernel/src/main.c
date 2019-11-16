
#include "io/uart.h"
#include "io/gpio.h"
#include "io/delays.h"

void main()
{
    uart_init();

    //gpio_pullControl(26, GPIO_PULL_OFF);
    //gpio_pinmode(26, GPIO_INPUT);

    uart_printf("Test\n");
    int i = 0;
    while(1) {
        i++;
        uart_printf("GPIO 26 is %s %d\n", "testsss", i);
        wait_msec_st(1000000);
    }
}
