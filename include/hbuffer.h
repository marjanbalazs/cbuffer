#define create_buffer(TYPE) typedef struct {					\
    TYPE* buffer;												\
    size_t capacity;											\
    size_t read;												\
    size_t write;												\
    size_t full;						    					\
} cbuffer_##TYPE##_t;											\
										    					\
typedef cbuffer_##TYPE##_t* cbuffer_##TYPE##_handle_t;			\
																\
cbuffer_##TYPE##_handle_t 										\
construct_##TYPE##_cbuffer(size_t capacity)						\
{																\
    cbuffer_##TYPE##_t* cbuffer =								\
						malloc( sizeof (cbuffer_##TYPE##_t));	\
    cbuffer->buffer = malloc(sizeof(TYPE) * capacity );			\
    cbuffer->capacity = capacity;								\
    cbuffer->read = 0;											\
    cbuffer->write = 0;											\
    cbuffer->full = 0;											\
    return cbuffer;												\
}																\
																\
void															\
destroy_cbuffer(cbuffer_##TYPE##_t cbuffer)						\
{																\
    free(cbuffer->buffer);										\
    free(cbuffer);												\
}																\
																\
int																\
cbuffer_put(TYPE* source_element, cbuffer_##TYPE##_t cbuffer)	\
{																\
    int ret;													\
    if ( cbuffer_isfull(cbuffer) )								\
    {															\
        ret = 0;												\
    }															\
    else														\
    {															\
        void* ptr = cbuffer->buffer +							\
					cbuffer->write * cbuffer->sizeof_element;	\
        memcpy(ptr, source_element, cbuffer->sizeof_element);	\
        cbuffer->write++;										\
        if ( cbuffer->write % cbuffer->capacity ==				\
			 cbuffer->read % cbuffer->capacity )				\
        {														\
            cbuffer->full = 1;									\
        }														\
        ret = 1;												\
    }															\
    return ret;													\
}																\
																\
TYPE*															\
cbuffer_get(cbuffer_##TYPE##_tcbuffer cb)						\
{																\
    TYPE* ret;													\
    															\
	if( cbuffer_isempty(cbuffer) != 0)							\
	{															\
		retptr = NULL;											\
	}															\
	else														\
	{															\
		retptr = cbuffer->element_cbuffer +						\
				 cbuffer->read * cbuffer->sizeof_element;		\
		cbuffer->full = 0;										\
		cbuffer->read++;										\
	}															\
	return retptr;												\
}																\
																\
int																\
cbuffer_isfull(cbuffer_##TYPE##_t cbuffer)						\
{																\
	return cbuffer->full;										\
}																\
																\
int																\
cbuffer_isempty(cbuffer_##TYPE##_t cbuffer)						\
{																\
	return (cbuffer->read == cbuffer->write) &&				 	\
			(cbuffer->full == 0);								\
}
