#include "button.h"

void button_init(struct button* self,
                 const uint8_t pin)
{
		if (pin >= 0 && pin <= 7)
		{
			self->io_port = IO_PORTD,
			self->pin = pin;
			PORTD |= (1 << self->pin);
		}
		else if (pin >= 8 && pin <= 13)
		{
			self->io_port = IO_PORTB;
			self->pin = pin - 8;
			PORTB |= (1 << self->pin);
		}
		else if (pin >= 14 && pin <= 19)
		{
			self->io_port = IO_PORTC;
			self->pin = pin - 14;
			PORTC |= (1 << self->pin);
		}
		else
		{
			self->io_port = IO_PORT_NONE;
			self->pin = 0;
		}

		self->interrupt_enabled = false;
		return;
}


void button_clear(struct button* self)
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

	self->io_port = IO_PORT_NONE;
	self->pin = 0;
	return;
}

bool button_is_pressed(const struct button* self)
{
	if (self->io_port == IO_PORTB)
	{
		return (PINB & (1 << self->pin));
	}
	else if (self->io_port == IO_PORTC)
	{
		return (PINC & (1 << self->pin));
	}
	else if (self->io_port == IO_PORTD)
	{
		return (PIND & (1 << self->pin));
	}
	else
	{
		return false;
	}
}

void button_enable_interrupt(struct button* self)
{
	asm("SEI");

	if (self->io_port == IO_PORTB)
	{
		PCICR |= (1 << PCIE0);
		PCMSK0 |= (1 << self->pin);
	}
	else if (self->io_port == IO_PORTC)
	{
		PCICR |= (1 << PCIE1);
		PCMSK1 |= (1 << self->pin);
	}
	else if (self->io_port == IO_PORTD)
	{
		PCICR |= (1 << PCIE2);
		PCMSK2 |= (1 << self->pin);
	}

	self->interrupt_enabled = true;
	return;
}

void button_disable_interrupt(struct button* self)
{
	if (self->io_port == IO_PORTB)
	{
		PCMSK0 &= ~(1 << self->pin);
	}
	else if (self->io_port == IO_PORTC)
	{
		PCMSK1 &= ~(1 << self->pin);
	}
	else if (self->io_port == IO_PORTD)
	{
		PCMSK2 &= ~(1 << self->pin);
	}

	self->interrupt_enabled = false;
	return;
}

void button_toggle_interrupt(struct button* self)
{
	if (self->interrupt_enabled)
	{
		button_disable_interrupt(self);
	}
	else
	{
		button_enable_interrupt(self);
	}

	return;
}