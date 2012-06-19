#ifndef MAIN_H
#define MAIN_H

#define F_CPU 2000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "display.c"
#include "time.c"
#include "temperature.c"

#define BUTTON_PORT PORTD
#define BUTTON_PIN PIND
#define BUTTON1 PD0
#define BUTTON2 PD1

#endif
