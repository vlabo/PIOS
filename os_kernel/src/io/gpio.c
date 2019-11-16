#include "gpio.h"
#include "delays.h"

volatile gpio_t* const gpio = (volatile gpio_t* const) (IO_BASE + GPIO_BASE);

void gpio_pullMulti( uint32_t p[2], uint32_t pull )
{
    if ( pull == GPIO_PULL_UP || 
         pull == GPIO_PULL_DOWN || 
         pull == GPIO_PULL_OFF)
    {
        gpio->pullControlEnable = pull;
        wait_cycles( 150 );
        
        gpio->pullControlClock[0] = p[0];
        gpio->pullControlClock[1] = p[1];
        wait_cycles( 150 );
        
        gpio->pullControlClock[0] = 0;
        gpio->pullControlClock[1] = 0;
    }
    else
    {
        gpio->pullControlEnable = GPIO_PULL_OFF;
    }
}

void gpio_pullControl ( uint32_t pin, uint32_t pull )
{
    if ( pin > 53 ) 
        return;

    uint32_t p[2]={0};
    uint32_t i = 0;
    if ( pin > 31 )
    {
        i++;
        pin-=32;
    }
    
    p[i] = (1 << pin);
    
    gpio_pullMulti( p, pull );    
}

/**
 * \brief reads the value of the GPIO-pin (set as input)
 * \param pin the GPIO pin you want the state of (in [0, 53])
 * \return the state of the GPIO-Pin (i.e. HIGH or LOW-signal level), 
 * always returns LOW if the input is invalid
 **/
uint32_t gpio_read ( uint32_t pin )
{
    if ( pin > 53 ) 
        return GPIO_LOW;

    volatile uint32_t* base = &gpio->level[0];
    if ( pin > 31 )
    {
        base++;
        pin -= 32;
    }
    
    uint32_t val = *base;
    return ( ((val & (1<<pin)) == 0) ? GPIO_LOW : GPIO_HIGH );
}

/**
 * \brief writes a value to the GPIO-Pin (i.e. writes 1 to set or 1 to clear-registers)
 * \param pin GPIO-Pin (preferably between 0 and 53)
 * \param val output-value (1 for on, 0 for off)
 **/
void gpio_write ( uint32_t pin, uint32_t val )
{
    if ( pin > 53 ) 
        return;

    volatile uint32_t* base = &gpio->outputset[0];
    if ( val == GPIO_LOW )
    {
        base = &gpio->outputclear[0];
    }
    
    if ( pin > 31 )
    {
        base++;
        pin -= 32;
    }
    (*base) = 1 << pin;
}

/**
 * \brief sets the PIN into the mode we want
 * \param pin GPIO-Pin
 * \param val GPIO-Mode
 * \return NONE
 **/
void gpio_pinmode ( uint32_t pin, uint32_t val )
{
    if ( val > 7 )
        return;

    if ( pin > 53 ) 
        return;
    
    volatile uint32_t *base = &gpio->fn_select[0];
    while ( pin >= 10 )
    {
        base++;
        pin-=10;
    }
    
    uint32_t v = *base;
    v &= ~(7 << ((pin<<1) + pin));    /// move the 7 pin*3 times, so it masks the correct bits
    v |= (val << ((pin<<1) + pin));
    *base = v;
}

int gpio_getPinmode ( uint32_t pin )
{
    if ( pin > 53 ) 
        return 0;
    
    volatile uint32_t *base = &gpio->fn_select[0];
    while ( pin >= 10 )
    {
        base++;
        pin-=10;
    }
    
    uint32_t v = *base;
    v = v >> ((pin<<1)+pin) ;
    v &= 7;    /// move the 7 pin*3 times, so it masks the correct bits
    return v;
}