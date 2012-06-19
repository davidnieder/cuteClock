#ifndef TIME_C
#define TIME_C

#include "time.h"

void time_init(void)
{
    TCCR1B |= (1<<WGM12) | (1<<CS10);   /* clean on compare, no prescaling */
    OCR1A = TICKS_PER_MILLISECOND/2;    /* compare value */

    TIMSK |= (1<<OCIE1A);               /* enable interrupt */
}

void time_update(void)
{
    display.minutes_0 = minutes%10;
    display.minutes_1 = minutes/10;

    display.hours_0 = hours%10;
    display.hours_1 = hours/10;
}

void add_hour(void)
{
    hours++;

    display_set_mode(TIME);
    last_switch = seconds;
}

void add_minute(void)
{
    minutes++;
    seconds = 0;
    milliseconds = 0;

    display_set_mode(TIME);
    last_switch = seconds;
}

ISR(TIMER1_COMPA_vect)
{
    milliseconds++;

    if( milliseconds >= 2000 )  {
        milliseconds = 0;
        seconds++;
    }   
    if( seconds >= 60 ) { 
        seconds = 0;
        minutes++;

        last_switch = seconds;
    }
    if( minutes >= 60 ) {
        minutes = 0;
        hours++;
    }
    if( hours >= 24 )   {
        hours = 0;
    }

    if( milliseconds )  {           // wie oft spalte wechseln?
        actual_column++;
        if( actual_column > 4 )
            actual_column = 0;
    }

    /* switch display mode? */
    if( last_switch+SWITCH_DISPLAY_MODE_TIME < seconds )    {
        last_switch = seconds;
        display_switch_mode();
    }


    COLUMN_PORT &= ~(0b00001111);
    PORTC |= (0b00011111);
    PORTD |= (0b11100000);

    if( display_mode == TIME ) { 
        if( actual_column == 0 ) { 
            COLUMN_PORT |= (1<<COLUMN1);
            display_character(display.hours_1);
        }   
        else if( actual_column == 1 )    {   
            COLUMN_PORT |= (1<<COLUMN2);
            display_character(display.hours_0);
        }   
        else if( actual_column == 2 )    {   
            COLUMN_PORT |= (1<<COLUMN3);
            display_character(display.minutes_1);
        }   
        else if( actual_column == 3 )    {   
            COLUMN_PORT |= (1<<COLUMN4);
            display_character(display.minutes_0);
        }   
        else if( actual_column == 4 )    {   
            COLUMN_PORT |= (1<<COLUMN2);
            display_character(display.colon_symbol);
        }   
    }   
    else    {   
        if( actual_column == 0 ) { 
            COLUMN_PORT |= (1<<COLUMN1);
            display_character(display.temperature_1);
        }   
        else if( actual_column == 1 )    {   
            COLUMN_PORT |= (1<<COLUMN2);
            display_character(display.temperature_0);
        }   
        else if( actual_column == 2 )    {   
            COLUMN_PORT |= (1<<COLUMN3);
            display_character(display.degree_symbol);
        }   
        else if( actual_column == 3 )    {   
            COLUMN_PORT |= (1<<COLUMN4);
            display_character(display.celsius_symbol);
        }   
    }   
}

#endif
