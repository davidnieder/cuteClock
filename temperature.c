#ifndef TEMPERATURE_C
#define TEMPERATURE_C

#include "temperature.h"

void adc_init()
{
    ADMUX |= (1<<REFS0);                /* avcc as reference voltage*/
    ADCSRA = (1<<ADPS2);                /* prescale factor 16 */
    ADCSRA |= (1<<ADEN);                /* enable ad converter */

    /* adc dummy conversion */
    ADCSRA |= (1<<ADSC);
    while( ADCSRA & (1<<ADSC) );
    adc_result = ADCW;
    adc_result = 0;

    /* set channel */
    ADMUX |= ADC_CHANNEL;
}

uint32_t adc_read()
{
    uint32_t result = 0;
    uint8_t i;

    for(i=0; i<8; i++)  {
        ADCSRA |= (1<<ADSC);
        while(ADCSRA & (1<<ADSC));
        result += ADCW;
    }
    return result;
}

void calc_temperature()
{
    adc_result = adc_read();
    temperature = (adc_result*adc_slope)/1000-adc_offset;
    temperature = temperature/100;
}

void temperature_update()
{
    calc_temperature();

    if(temperature > 99)    {
        display.temperature_0 = 9;
        display.temperature_1 = 9;
    }
    else if(temperature > 9)    {
        display.temperature_0 = temperature%10;
        display.temperature_1 = temperature/10;
    }
    else if(temperature >= 0)   {
        display.temperature_0 = temperature;
        display.temperature_1 = VOID;
    }
    else if(temperature <= -9)  {
        display.temperature_0 = 9;
        display.temperature_1 = MINUS;
    }
    else if(temperature < 0)    {
        display.temperature_0 = temperature;
        display.temperature_1 = MINUS;
    }
}

#endif
