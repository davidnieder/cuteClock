#ifndef TIME_H
#define TIME_H

#define TICKS_PER_MILLISECOND (F_CPU/1000)

volatile uint16_t milliseconds = 0;
volatile uint8_t seconds = 0;
volatile uint8_t minutes = 0;
volatile uint8_t hours = 0;

volatile uint8_t last_switch = 0;

/* prototypes */
void time_init(void);
void time_update(void);
void add_hour(void);
void add_minute(void);

#endif
