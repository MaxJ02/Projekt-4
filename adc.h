/********************************************************************************
* adc.h: Innehåller funktionalitet för enkel implementering av AD-omvandling
*        för analoga signaler via strukten adc. AD-omvandling sker via inläsning
*        av signaler från analoga pinnar A0 - A5 på  Arduino Uno, vilket
*        motsvarar PORTC0 - PORTC5 på ATmega328P.
*
*        Analoga insignaler mellan 0 - 5 V AD-omvandlas till digitala
*        motsvarigheter mellan 0 - 1023. Duty cycle kan användas för
*        PWM-generering och beräknas enligt nedan:
*
*                       duty cycle = ADC_result / ADC_MAX,
*
*       där ADC_result är resultat avläst från AD-omvandlaren OCH ADC_MAX
*       utgör högsta möjliga avlästa värde, vilket är 1023.0.
********************************************************************************/
#ifndef ADC_H_
#define ADC_H_

/* Inkluderingsdirektiv: */
#include "misc.h"

/* Makrodefinitioner: */
#define ADC_MAX 1023.0 /* Högsta digitala värde vid AD-omvandling (motsvarar 5 V). */

/********************************************************************************
* adc: Strukt för implementering av AD-omvandlare, som möjliggör avläsning
*      av insignaler från analoga pinnar samt beräkning av on- och off-tid för
*      PWM-generering (tiden som PWM-styrd utsignal ska vara hög respektive låg).
********************************************************************************/
struct adc
{
	uint8_t pin;         /* Analog pin som skall användas för avläsning. */
	uint16_t pwm_on_us;  /* On-tid för PWM-generering i mikrosekunder. */
	uint16_t pwm_off_us; /* Off-tid för PWM-generering i mikrosekunder. */
};

/********************************************************************************
* adc_init: Initierar analog pin för avläsning och AD-omvandling av insignaler,
*           som antingen kan anges som ett tal mellan 0 - 5 eller via konstanter
*           A0 - A5 (som motsvarar heltal 14 - 19).
*
*           - self: Pekare till analog pin som skall användas för AD-omvandling.
*           - pin : Analog pin som skall läsas för AD-omvandling.
********************************************************************************/
void adc_init(struct adc* self,
              const uint8_t pin);

/********************************************************************************
* adc_read: Läser av en analog insignal och returnerar motsvarande digitala
*           motsvarighet mellan 0 - 1023.
*
*           - self: Pekare till analog pin vars insignal ska AD-omvandlas.
********************************************************************************/
uint16_t adc_read(const struct adc* self);

/********************************************************************************
* adc_duty_cycle: Läser av en analog insignal och returnerar motsvarande
*                 duty cycle som ett flyttal mellan 0 - 1.
*
*                 - self: Pekare till analog pin vars insignal ska AD-omvandlas.
********************************************************************************/
double adc_duty_cycle(const struct adc* self);

/********************************************************************************
* adc_get_pwm_values: Läser av en analog insignal och beräknar on- och off-tid
*                     för PWM-generering, avrundat till närmaste heltal.
*
*                     - self         : Pekare till AD-omvandlaren som skall
*                                      läsas av.
*                     - pwm_period_us: PWM-perioden (on-tid + off-tid) mätt i
*                                      mikrosekunder (default = 10 000 us).
********************************************************************************/
void adc_get_pwm_values(struct adc* self,
                        uint16_t pwm_period_us);

#endif /* ADC_H_ */