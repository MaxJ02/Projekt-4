/********************************************************************************
* led.h: Innehåller funktionsdefinitioner för implementering av lysdioder och
*        andra digitala utportar via strukten led.
********************************************************************************/
#include "led.h"

/********************************************************************************
* led_init: Initierar ny lysdiod på angiven pin.
*
*           - self: Pekare till lysdioden som ska initieras.
*           - pin : Lysdiodens pin-nummer på Arduino Uno, exempelvis 8.
*                   Alternativt kan motsvarande port-nummer på ATmega328P
*                   anges, exempelvis B0 för pin 8 eller D2 för pin 2.
********************************************************************************/
void led_init(struct led* self,
              const uint8_t pin)
{
   if (pin >= 0 && pin <= 7)
   {
      self->io_port = IO_PORTD,
      self->pin = pin;
      DDRD |= (1 << self->pin);
   }
   else if (pin >= 8 && pin <= 13)
   {
      self->io_port = IO_PORTB;
      self->pin = pin - 8;
      DDRB |= (1 << self->pin);
   }
   else if (pin >= 14 && pin <= 19)
   {
      self->io_port = IO_PORTC;
      self->pin = pin - 14;
      DDRC |= (1 << self->pin);
   }
   else
   {
      self->io_port = IO_PORT_NONE;
      self->pin = 0;
   }

   self->enabled = false;
   return;
}

/********************************************************************************
* led_clear: Nollställer lysdiod samt motsvarande pin.
*
*            - self: Pekare till lysdioden som ska nollställas.
********************************************************************************/
void led_clear(struct led* self)
{
   if (self->io_port == IO_PORTB)
   {
      DDRB &= ~(1 << self->pin);
      PORTB &= ~(1 << self->pin);
   }
   else if (self->io_port == IO_PORTC)
   {
      DDRC &= ~(1 << self->pin);
      PORTC &= ~(1 << self->pin);
   }
   else if (self->io_port == IO_PORTD)
   {
      DDRD &= ~(1 << self->pin);
      PORTD &= ~(1 << self->pin);
   }

   self->io_port = IO_PORT_NONE;
   self->pin = 0;
   self->enabled = false;
   return;
}

/********************************************************************************
* led_on: Tänder angiven lysdiod.
*
*         - self: Pekare till lysdioden som ska tändas.
********************************************************************************/
void led_on(struct led* self)
{
   if (self->io_port == IO_PORTB)
   {
      PORTB |= (1 << self->pin);
   }
   else if (self->io_port == IO_PORTC)
   {
      PORTC |= (1 << self->pin);
   }
   else if (self->io_port == IO_PORTD)
   {
      PORTD |= (1 << self->pin);
   }

   self->enabled = true;
   return;
}

/********************************************************************************
* led_off: Släcker angiven lysdiod.
*
*          - self: Pekare till lysdioden som ska släckas.
********************************************************************************/
void led_off(struct led* self)
{
   if (self->io_port == IO_PORTB)
   {
      PORTB &= ~(1 << self->pin);
   }
   else if (self->io_port == IO_PORTC)
   {
      PORTC &= ~(1 << self->pin);
   }
   else if (self->io_port == IO_PORTD)
   {
      PORTD &= ~(1 << self->pin);
   }

   self->enabled = false;
   return;
}

/********************************************************************************
* led_toggle: Togglar utsignalen på angiven lysdiod. Om lysdioden är släckt vid
*             anropet så tänds den. På samma sätt gäller att om lysdioden är
*             tänd vid anropet så släcks den.
*
*             - self: Pekare till lysdioden vars utsignal ska togglas.
********************************************************************************/
void led_toggle(struct led* self)
{
   if (self->enabled)
   {
      led_off(self);
   }
   else
   {
      led_on(self);
   }

   return;
}

/********************************************************************************
* led_blink: Blinkar lysdiod en gång med angiven blinkhastighet.
*
*            - self          : Pekare till lysdioden som ska blinkas.
*            - blink_speed_ms: Blinkhastigheten mätt i millisekunder.
********************************************************************************/
void led_blink(struct led* self,
               const uint16_t blink_speed_ms)
{
   led_toggle(self);
   delay_ms(blink_speed_ms);
   return;
}
