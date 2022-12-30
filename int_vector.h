#ifndef INT_VECTOR_H_
#define INT_VECTOR_H_

#include <stdio.h>
#include <stdlib.h>

struct int_vector
{
	int* data;
	size_t size;
};

void int_vector_init(struct int_vector* self);

void int_vector_clear(struct int_vector* self);

int int_vector_push(struct int_vector* self,
                    const int new_element);

void int_vector_print(const struct int_vector*self,
                      FILE* ostream);

#endif /* INT_VECTOR_H_ */