/********************************************************************************
* setup.c: Innehåller funktionalitet för initiering av det inbyggda systemet.
********************************************************************************/
#include "header.h"

//Initerar timerskretsar.
static inline void init_timers(void);

//Definition av globala objekt
struct button b1;  //Tryckknapp ansluten till pin 13.
struct tmp36 temp1; //Temperatursensor tmp36 ansluten till

/********************************************************************************
* setup: Initierar tryckknapp, interrupts på tryckknappen, tmp36 och timers.
********************************************************************************/
void setup(void)
{

	button_init(&b1, 13);
	
	button_enable_interrupt(&b1);

    tmp36_init(&temp1, A2);
	tmp36_print_temperature(&temp1);
	
	init_timers();
	
	return;
}
/********************************************************************************
* Init_timers: aktiverar avbrott globalt och initierar timerkretsarna Timer 0 och Timer 1.
*              Timer 1 initieras i CTC Mode med uppräkning till 256. Vid aktiverat avbrott
*              på en initierad timer sker ett timergenererat avbrott varje 0.128:e ms.
********************************************************************************/
static inline void init_timers(void)
{ 
	asm("SEI");
	TCCR0B = (1 << CS01);
	TCCR1B = (1 << WGM12) | (1 << CS11);
	OCR1A = 256; //Båda timerkretsarna ska räkna upp till 256
	TIMSK1 = (1 << OCIE1A);
	return;
}
