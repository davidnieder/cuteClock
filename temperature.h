#ifndef TEMPERATURE_H
#define TEMPERATURE_H


#define ADC_CHANNEL 5

uint32_t adc_result;
uint32_t temperature;

const uint16_t adc_offset = 6111;
const uint16_t adc_slope = 2715;


/* prototypes */
void adc_init(void);
uint32_t adc_read(void);
void calc_temperature(void);
void temperature_update(void);

#endif
