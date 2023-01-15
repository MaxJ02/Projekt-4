/********************************************************************************
* interrupts: beräkning av genomsnittstiden och genomsnittstemperaturen samt avbrotts-
*             rutiner för knappen b1, timer 0 och timer 1.
********************************************************************************/
#include "header.h"

//Globala, alla känner dessa.
static volatile uint32_t timer1_counter = 0;
static volatile uint32_t timer1_max_count = (uint32_t)(60000 / 0.128 + 0.5);

static uint32_t executed_interrupts[5];
static volatile uint32_t num_executed_interrupts = 0;
static volatile uint32_t index = 0;

/********************************************************************************
* average: Tar de senaste 5 temperaturmätningarna och beräknar
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

double get_average(double *values, size_t count)
{
	double sum = 0;

	for (int i = 0; i < count; ++i)
	{
		sum += values[i];
	}

	return sum / count;
}

/********************************************************************************
* update_executed_interrupts: räknar ut genomsnittstiden från det fem senaste
*                             knapptryckningarna. 
********************************************************************************/
static void update_executed_interrupts(void)
{
	executed_interrupts[index++] = num_executed_interrupts;
	num_executed_interrupts = 0;
	
	if (index >= 5)
	{
		timer1_max_count = average(executed_interrupts, 5); //Beräknar medelvärdet av de fem senaste knapptryckningarna.
		index = 0;
	}
	return;
}

double temperatures[5];
int temperature_index = 0;

static void tmp36_average_temp(void)
{
	double temperature = tmp36_get_temperature(&temp1);
	
	temperatures[temperature_index++] = temperature;

	if (temperature_index == 5)
	{
		double avg_temp = get_average(temperatures, 5);
		printf("Average temperature: %lg\n", avg_temp);
		temperature_index = 0;
	}
}
/********************************************************************************
ISR :  Avbrottsrutin som sker vid nedtryckning av tryckknappen ansluten till pin 13
**    (b1) Temperaturen skrivs ut vid nedtryckning via ansluten USART, och counter
*     1 nollställs. Genomsnittstiden för knapptryck uppdateras också. Avbrott stängs
*    av i 300 ms efter nedtryckning av tryckknapp för att motverka kontaktstudsar.


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
		tmp36_average_temp();
	}		
	return;
}

/********************************************************************************
* ISR (TIMER0_OVF_vect):  Avbrottsrutin som sker vid overflow av timer 0 
*                         (uppräkning till 256, som sker varje 0.128ms vid aktiverad timer)
*						 
*						 När knappen trycks ned så räknas det upp till 300 ms,
                         och timer 0 samt counter 0 nollställs.
*						 Sedan börjar den räkna upp till 256 igen.             
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
* ISR (TIMER1_COMPA_vect):Avbrottsrutin som sker vid uppräkning till 256 med timer 1 inställd
*                         på CTC mode, vilket ska ske varje 0.128e ms vid aktiverad timer.
*        
*                         När timer 1 når värdet timer1_max_count skrivs temperaturen 
*                         ut via den anslutna seriella terminalen. Sedan nollställs timer 1.                      
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
