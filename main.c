#ifndef MAIN_C
#define MAIN_C

#include "main.h"


int main()
{
    cli();

    /* raise pull-ups on button pins */
    BUTTON_PORT |= (1<<BUTTON2) | (1<<BUTTON1);

    time_init();
    adc_init();
    display_init();

    sei();

    while(1)    {

        /* check button statuses */
        if( !(PIND & (1<<BUTTON1)) )   {
            add_hour();
            _delay_ms(250);
        }
        if( !(PIND & (1<<BUTTON2)) )   {
            add_minute();
            _delay_ms(250);
        }

        time_update();
        temperature_update();
        
        _delay_ms(250);
    }

    return 0;
}

#endif
