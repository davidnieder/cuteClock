#ifndef DISPLAY_C
#define DISPLAY_C

#include "display.h"

void display_init()
{
    display.minutes_0 = 0;
    display.minutes_1 = 0;
    display.hours_0 = 0;
    display.hours_1 = 0;

    display.temperature_0 = 0;
    display.temperature_1 = 0;

    display.colon_symbol = COLON;
    display.degree_symbol = DEGREE;
    display.celsius_symbol = CELSIUS;

    /* initialise interrupt */
//    TCCR2 |= (1<<WGM21) | (1<<CS22);    /* clean on compare, no prescaling */
//    OCR2 = 60;                          /* compare value */

//    TIMSK |= (1<<OCIE2);                /* enable interrupt */

    /* pin registers */
    COLUMN_REGISTER = (1<<COLUMN4) | (1<<COLUMN3) | (1<<COLUMN2) |
                      (1<<COLUMN1);
    DDRC = (1<<LA2) | (1<<LA3) | (1<<LA6) | (1<<LA7) | (1<<LA8);
    DDRD = (1<<LA12) | (1<<LA11) | (1<<LA10);

}

void display_switch_mode()
{
    if(display_mode == TIME)
        display_mode = TEMPERATURE;
    else
        display_mode = TIME;
}

void display_set_mode(uint8_t mode)
{
    if(mode == TIME || mode == TEMPERATURE) {
        display_mode = mode;
    }
}

void display_character(uint8_t character)
{
    switch(character)   {
        case 0:
            PORTC &= ~((1<<LA2) | (1<<LA3) | (1<<LA6) | (1<<LA7) | (1<<LA8));
            PORTD &= ~(1<<LA10);
        break;
        case 1:
            PORTC &= ~(1<<LA6);
            PORTD &= ~(1<<LA10);
        break;
        case 2:
            PORTC &= ~((1<<LA2) | (1<<LA6) | (1<<LA7) | (1<<LA8));
            PORTD &= ~(1<<LA11);
        break;
        case 3:
            PORTC &= ~((1<<LA2) | (1<<LA6) | (1<<LA8));
            PORTD &= ~((1<<LA11) | (1<<LA10));
        break;
        case 4:
            PORTC &= ~((1<<LA3) | (1<<LA6));
            PORTD &= ~((1<<LA11) | (1<<LA10));
        break;
        case 5:
            PORTC &= ~((1<<LA2) | (1<<LA3) | (1<<LA8));
            PORTD &= ~((1<<LA10) | (1<<LA11));
        break;
        case 6:
            PORTC &= ~((1<<LA2) | (1<<LA3) | (1<<LA7) | (1<<LA8));
            PORTD &= ~((1<<LA10) | (1<<LA11));
        break;
        case 7:
            PORTC &= ~((1<<LA2) | (1<<LA6));
            PORTD &= ~(1<<LA10);
        break;
        case 8:
            PORTC &= ~((1<<LA2) | (1<<LA3) | (1<<LA6) | (1<<LA7) | (1<<LA8));
            PORTD &= ~((1<<LA11) | (1<<LA10));
        break;
        case 9:
            PORTC &= ~((1<<LA2) | (1<<LA3) | (1<<LA6) | (1<<LA8));
            PORTD &= ~((1<<LA11) | (1<<LA10));
        break;
        case COLON:
            PORTD &= ~(1<<LA12);
        break;
        case DEGREE:
            PORTC &= ~((1<<LA2) | (1<<LA3) | (1<<LA6));
            PORTD &= ~(1<<LA11);
        break;
        case CELSIUS:
            PORTC &= ~((1<<LA2) | (1<<LA3) | (1<<LA7) | (1<<LA8));
        break;
        case MINUS:
            PORTD &= ~(1<<LA11);
        break;
    }
}

void display_update()
{
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
