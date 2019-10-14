#ifndef CBUFFER_H
#define CBUFFER_H_

#include <stdlib.h>
#include <string.h>

/*------------------Types--------------------------------*/

typedef struct {
	size_t sizeof_element;
	size_t capacity;
	size_t read;
	size_t write;
	size_t full;
	void *element_cbuffer;
} cbuffer_t;

typedef cbuffer_t *cbuffer_handle_t;

/*------------------Function prototypes------------------*/

cbuffer_t* construct_cbuffer(size_t capacity, size_t elem_size);
void destroy_cbuffer(cbuffer_t* cbuffer);
int cbuffer_isfull(cbuffer_t* cbuffer);
int cbuffer_isempty(cbuffer_t* cbuffer);
int cbuffer_put(void *source_element, cbuffer_t* cbuffer);
void* cbuffer_get(cbuffer_t* cbuffer);

#endif
