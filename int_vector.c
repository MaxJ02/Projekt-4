#include "int_vector.h"

void int_vector_init(struct int_vector* self)
{
	self->data = 0;
	self->size = 0;
	return;
}

void int_vector_clear(struct int_vector* self)
{
	free(self->data);
	self->data = 0;
	self->size = 0;
	return;
}

int int_vector_push(struct int_vector* self,
                    const int new_element)
{
	int* copy = (int*)realloc(self->data, sizeof(int) * (self->size + 1));
	if(!copy) return 1;
	copy[self->size++] = new_element;
	self->data = copy;
	return 0;
	
}

void int_vector_print(const struct int_vector*self,
                      FILE* ostream)
{
	if(!ostream) ostream = stdout;
	fprintf(ostream, "--------------------------------------------------------------------\n");
	for (size_t i = 0; i < self->size; ++i)
	{
		fprintf(ostream, "%d\n", self->data[i]);
	}
	fprintf(ostream, "--------------------------------------------------------------------\n\n");
}