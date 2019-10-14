#include <stdint.h>
#include <stdio.h>
#include <cbuffer.h>
#include <string.h>

cbuffer_t* construct_cbuffer(size_t capacity, size_t elem_size)
{
	cbuffer_t* cbuffer = malloc(sizeof(cbuffer_t));
	if( cbuffer == NULL )
	{
		fprintf(stderr, "Fatal: failed to allocate %zu bytes for cbuffer.\n",
				sizeof(cbuffer_t));
	}
	cbuffer->element_cbuffer = malloc(elem_size * capacity);
	if( cbuffer->element_cbuffer == NULL ){
		fprintf(stderr, "Fatal: failed to allocate %zu bytes element buffer.\n",
				elem_size *capacity);
	} else {
		memset(cbuffer->element_cbuffer, 0 , elem_size *capacity );
	}
    cbuffer->sizeof_element = elem_size;
    cbuffer->capacity = capacity;
    cbuffer->read = 0;
    cbuffer->write = 0;
    cbuffer->full = 0;
    return (cbuffer);	/* Potential memory leak! */
}

void destroy_cbuffer(cbuffer_handle_t cbuffer)
{
    free(cbuffer->element_cbuffer);
    free(cbuffer);
}

int cbuffer_put(void* source_element, cbuffer_handle_t cbuffer)
{
    int ret;
    if ( cbuffer_isfull(cbuffer) )
    {
        ret = 0;
    }
    else
    {
        uintptr_t* ptr = (uintptr_t*) cbuffer->element_cbuffer +
        		cbuffer->write * cbuffer->sizeof_element;
        memcpy(ptr, source_element, cbuffer->sizeof_element);
        cbuffer->write++;
        if ( cbuffer->write % cbuffer->capacity == cbuffer->read % cbuffer->capacity )
        {
            cbuffer->full = 1;
        }
        ret = 1;
    }
    return (ret);
}

void* cbuffer_get( cbuffer_handle_t cbuffer)
{
    uintptr_t* retptr;
    
    if( cbuffer_isempty(cbuffer) != 0)
    {
        retptr = NULL;
    }
    else
    {
        retptr = (uintptr_t*) cbuffer->element_cbuffer +
        					cbuffer->read * cbuffer->sizeof_element;
        cbuffer->full = 0;
        cbuffer->read++;
    }

    return (retptr);
}

int cbuffer_isfull(cbuffer_handle_t cbuffer)
{
    return (cbuffer->full);
}

int cbuffer_isempty(cbuffer_handle_t cbuffer)
{
    return ((cbuffer->read == cbuffer->write ) && (cbuffer->full == 0));
}
