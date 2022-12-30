/********************************************************************************
* misc.c: Innehåller diverse funktionsdefinitioner.
********************************************************************************/
#include "misc.h"

/********************************************************************************
* delay_ms: Genererar fördröjning mätt i millisekunder.
*
*           - delay_time_ms: Angiven fördröjningstid i millisekunder.
********************************************************************************/
void delay_ms(const uint16_t delay_time_ms)
{
   for (uint16_t i = 0; i < delay_time_ms; ++i)
   {
      _delay_ms(1);
   }

   return;
}

/********************************************************************************
* delay_us: Genererar fördröjning mätt i mikrosekunder.
*
*           - delay_time_ms: Angiven fördröjningstid i mikrosekunder.
********************************************************************************/
void delay_us(const uint16_t delay_time_us)
{
	for (uint16_t i = 0; i < delay_time_us; ++i)
	{
		_delay_us(1);
	}

	return;
}