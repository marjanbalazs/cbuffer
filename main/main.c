#include <cbuffer.h>
#include <stdio.h>

int main(void)
{
	printf("Hello from main!\n");
	cbuffer_t *cb = construct_cbuffer(10, sizeof(int));
	int x = 5;
	int y = 6;
	int z = 7;
	cbuffer_put(&x, cb);
	cbuffer_put(&y, cb);
	cbuffer_put(&z, cb);

	if (cbuffer_isempty(cb)) {
		printf("The buffer is not supposed to be empty!\n");
	} else {
		printf("All is good!\n");
	}
	int *p = cbuffer_get(cb);
	printf("%d\n", *p);
	p = cbuffer_get(cb);
	printf("%d\n", *p);
	p = cbuffer_get(cb);
	printf("%d\n", *p);

	destroy_cbuffer(cb);
}
