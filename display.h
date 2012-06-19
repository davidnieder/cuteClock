#ifndef DISPLAY_H
#define DISPLAY_H

#define COLUMN_REGISTER DDRB
#define COLUMN_PORT PORTB

#define COLUMN1 PB0
#define COLUMN2 PB1
#define COLUMN3 PB2
#define COLUMN4 PB3

/* led anodes */
#define LA2 PC0
#define LA3 PC1
#define LA6 PC2
#define LA7 PC3
#define LA8 PC4
#define LA10 PD6
#define LA11 PD5
#define LA12 PD7

/* spezial characters */
#define COLON 10
#define DEGREE 11
#define CELSIUS 12
#define MINUS 13
#define VOID 14

#define SWITCH_DISPLAY_MODE_TIME 5

#define TIME 0
#define TEMPERATURE 1

uint8_t actual_column = 0;
uint8_t display_mode = TIME;

struct  {
    uint8_t minutes_0;
    uint8_t minutes_1;
    uint8_t hours_0;
    uint8_t hours_1;

    uint8_t temperature_0;
    uint8_t temperature_1;

    uint8_t colon_symbol;
    uint8_t degree_symbol;
    uint8_t celsius_symbol;
} display;

/* prototypes */
void display_init();
void display_switch_mode();
void display_set_mode(uint8_t);
void display_character(uint8_t);
void display_update();

#endif
