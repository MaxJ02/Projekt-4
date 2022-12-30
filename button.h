#ifndef BUTTON_H_
#define BUTTON_H_

#include "misc.h"

struct button
{
   uint8_t pin;
   enum io_port io_port;
   bool interrupt_enabled;
};

void button_init(struct button* self,
                 const uint8_t pin);

void button_clear(struct button* self);

bool button_is_pressed(const struct button* self);

void button_enable_interrupt(struct button* self);

void button_disable_interrupt(struct button* self);

void button_toggle_interrupt(struct button* self);



#endif /* BUTTON_H_ */