/********************************************************************************
* interrupts: ber�kning av genomsnittstiden och genomsnittstemperaturen samt avbrotts-
*             rutiner f�r knappen b1, timer 0 och timer 1.
********************************************************************************/
#include "header.h"

//Globala, alla k�nner dessa.
static volatile uint32_t timer1_counter = 0;
static volatile uint32_t timer1_max_count = (uint32_t)(60000 / 0.128 + 0.5);

static uint32_t executed_interrupts[5];
static volatile uint32_t num_executed_interrupts = 0;
static volatile uint32_t index = 0;

/********************************************************************************
* average: Tar de senaste 5 temperaturm�tningarna och ber�knar
*          genomsnittet med en statisk array
********************************************************************************/
static uint32_t average(uint32_t* data, const int size)
{
	uint32_t sum = 0; 
	
	for (int i = 0; i < size; ++i)
	{
		sum += data[i];
	}
	
	return (uint32_t)(sum / 5.0 + 0.5);
}
/********************************************************************************
* update_executed_interrupts: r�knar ut genomsnittstiden fr�n det fem senaste
*                             knapptryckningarna. 
********************************************************************************/
static void update_executed_interrupts(void)
{
	executed_interrupts[index++] = num_executed_interrupts;
	num_executed_interrupts = 0;
	
	if (index >= 5)
	{
		timer1_max_count = average(executed_interrupts, 5); //Ber�knar medelv�rdet av de fem senaste knapptryckningarna.
		index = 0;
	}
	return;
}
/********************************************************************************
ISR :  Avbrottsrutin som sker vid nedtryckning av tryckknappen ansluten till pin 13
**    (b1) Temperaturen skrivs ut vid nedtryckning via ansluten USART, och counter
*     1 nollst�lls. Genomsnittstiden f�r knapptryck uppdateras ocks�. Avbrott st�ngs
*    av i 300 ms efter nedtryckning av tryckknapp f�r att motverka kontaktstudsar.


********************************************************************************/
ISR (PCINT0_vect)
{
	PCICR &= ~(1 << PCIE0);
	TIMSK0 = (1 << TOIE0);

	if (button_is_pressed(&b1))
	{
		tmp36_print_temperature(&temp1);
		timer1_counter = 0;
		update_executed_interrupts();
	}		
	return;
}

/********************************************************************************
* ISR (TIMER0_OVF_vect):  Avbrottsrutin som sker vid overflow av timer 0 
*                         (uppr�kning till 256, som sker varje 0.128ms vid aktiverad timer)
*						 
*						 N�r knappen trycks ned s� r�knas det upp till 300 ms,
                         och timer 0 samt counter 0 nollst�lls.
*						 Sedan b�rjar den r�kna upp till 256 igen.             
********************************************************************************/
ISR (TIMER0_OVF_vect)
{
	static volatile uint16_t counter0 = 0;
	
	if (++counter0 >= TIMER0_MAX_COUNT)
	{
		PCICR = (1 << PCIE0);
		TIMSK0 = 0x00;
		counter0 = 0;
	}

	return;
}

/********************************************************************************
* ISR (TIMER1_COMPA_vect):Avbrottsrutin som sker vid uppr�kning till 256 med timer 1 inst�lld
*                         p� CTC mode, vilket ska ske varje 0.128e ms vid aktiverad timer.
*        
*                         N�r timer 1 n�r v�rdet timer1_max_count skrivs temperaturen 
*                         ut via den anslutna seriella terminalen. Sedan nollst�lls timer 1.                      
********************************************************************************/
ISR (TIMER1_COMPA_vect)
{
	num_executed_interrupts++;
	
	if (++timer1_counter >= timer1_max_count)
	{
		tmp36_print_temperature(&temp1);
		timer1_counter = 0;
	}

	return;
}
