/********************************************************************************
* led.h: Innehåller funktionalitet för enkel implementering av lysdioder via
*        strukten led samt associerade funktioner. Denna strukt fungerar också
*        utmärkt för andra digitala utportar.
********************************************************************************/
#ifndef LED_H_
#define LED_H_

/* Inkluderingsdirektiv: */
#include "misc.h"

/********************************************************************************
* led: Strukt för implementering av lysdioder och andra digitala utportar.
********************************************************************************/
struct led
{
   uint8_t pin;          /* Lysdiodens pin-nummer på aktuell I/O-port. */
   enum io_port io_port; /* I/O-port som lysdioden är ansluten till. */
   bool enabled;         /* Indikerar ifall lysdioden är tänd. */
};

/********************************************************************************
* led_init: Initierar ny lysdiod på angiven pin.
*
*           - self: Pekare till lysdioden som ska initieras.
*           - pin : Lysdiodens pin-nummer på Arduino Uno, exempelvis 8. 
*                   Alternativt kan motsvarande port-nummer på ATmega328P 
*                   anges, exempelvis B0 för pin 8 eller D2 för pin 2.
********************************************************************************/
void led_init(struct led* self, 
              const uint8_t pin);

/********************************************************************************
* led_clear: Nollställer lysdiod samt motsvarande pin.
*
*            - self: Pekare till lysdioden som ska nollställas.
********************************************************************************/
void led_clear(struct led* self);

/********************************************************************************
* led_on: Tänder angiven lysdiod.
*
*         - self: Pekare till lysdioden som ska tändas.
********************************************************************************/
void led_on(struct led* self);

/********************************************************************************
* led_off: Släcker angiven lysdiod.
*
*          - self: Pekare till lysdioden som ska släckas.
********************************************************************************/
void led_off(struct led* self);

/********************************************************************************
* led_toggle: Togglar utsignalen på angiven lysdiod. Om lysdioden är släckt vid
*             anropet så tänds den. På samma sätt gäller att om lysdioden är 
*             tänd vid anropet så släcks den.
*
*             - self: Pekare till lysdioden vars utsignal ska togglas.
********************************************************************************/
void led_toggle(struct led* self);

/********************************************************************************
* led_blink: Blinkar lysdiod en gång med angiven blinkhastighet.
*
*            - self          : Pekare till lysdioden som ska blinkas.
*            - blink_speed_ms: Blinkhastigheten mätt i millisekunder.
********************************************************************************/
void led_blink(struct led* self,
               const uint16_t blink_speed_ms);

#endif /* LED_H_ */