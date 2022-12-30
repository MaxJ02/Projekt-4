#include "led_vector.h"

void led_vector_init(struct led_vector* self)
{
	self->data = 0;
	self->size = 0;
	return;
}

void led_vector_clear(struct led_vector* self)
{
	free(self->data);
	self->data = 0;
	self->size = 0;
	return;
}

int led_vector_push(struct led_vector* self,
                    struct led* new_led)
{	
	struct led* copy = (struct led*)realloc(self->data, sizeof(struct led) * (self->size + 1));
	if(!copy) return 1;
	copy[self->size++] = *new_led;
	self->data = copy;
	return 0;
}

void led_vector_on(struct led_vector* self)
{
	for (size_t i = 0; i < self->size; ++i)
	{
		led_on(&self->data[i]);
	}
}

void led_vector_off(struct led_vector* self)
{
	for (size_t i = 0; i < self->size; ++i)
	{
		led_off(&self->data[i]);
	}
	return;
}

void led_vector_blink_collectively(struct led_vector* self,
                                   const uint16_t blink_speed_ms)
{
	led_vector_on(self); // Tänder alla.
	delay_ms(blink_speed_ms);
	led_vector_off(self);
	delay_ms(blink_speed_ms);
	return;
}

void led_vector_blink_sequentially(struct led_vector* self,
                                   const uint16_t blink_speed_ms)
{
	for (size_t i = 0; i < self->size; ++i)
	{
		led_on(&self->data[i]);
		delay_ms(blink_speed_ms);
		led_off(&self->data[i]);
	}
	return;
}