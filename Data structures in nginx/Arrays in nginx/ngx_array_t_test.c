#include <stdio.h>
#include "ngx_config.h"
#include "ngx_conf_file.h"
#include "nginx.h"
#include "ngx_core.h"
#include "ngx_string.h"
#include "ngx_palloc.h"
#include "ngx_array.h"


volatile ngx_cycle_t *ngx_cycle;
void ngx_log_error_core(ngx_uint_t level, ngx_log_t *log, ngx_err_t err,const char *fmt, ...)
{
}

void dump_pool(ngx_pool_t* pool)
{
   while (pool)
   {
	printf("POOL ADDRESS :   0x%x\n", pool);
	printf(" FEILD        ADDRESS\n");
	printf("-----------------------\n");
	printf(" .last        0x%x\n", pool->d.last);
	printf(" .end         0x%x\n", pool->d.end);
	printf(" .next        0x%x\n", pool->d.next);
	printf(" .failed      %d\n", pool->d.failed);
	printf(" .max         %d\n", pool->max);
	printf(" .current     0x%x\n", pool->current);
	printf(" .chain       0x%x\n", pool->chain);
	printf(" .large       0x%x\n", pool->large);
	printf(" .cleanup     0x%x\n", pool->cleanup);
	printf(" .log         0x%x\n", pool->log);
	printf("available pool memory = %d\n\n", pool->d.end - pool->d.last);
	pool = pool->d.next;
   }
}

void dump_array(ngx_array_t* array)
{
	if(array)
	{
		printf("array = 0x%x\n", array);
		printf("	.pool = 0x%x\n", array->pool);
		printf("	.elts = 0x%x\n", array->elts);
		printf("	.nelts = 0x%x\n", array->nelts);
		printf("	.size = %lu\n", array->size);
		printf("	.nalloc = %u\n", array->nalloc);

		printf("elements: ");

		int* ptr = (int*)(array->elts);
		for (;	ptr < (int*)(array->elts + array->nalloc * array->size); )
		{
			printf("0x%x ", *(ptr++));
		}

		printf("\n");
	}
}

void ngx_array_t_test()
{
	ngx_pool_t* pool;
	int i = 0;

printf("SIZE OF INT : %d",sizeof(int));
	printf("--------------------------------\n");
   	printf("the size of ngx_array_t: \n");
	printf("--------------------------------\n");
	printf("%lu\n\n", sizeof(ngx_array_t));

	printf("--------------------------------\n");
	printf("create a new pool: \n");
	printf("--------------------------------\n");
	pool = ngx_create_pool(1024, NULL);
	dump_pool(pool);

	printf("--------------------------------\n");
	printf("alloc an array from the pool: \n");
	printf("--------------------------------\n");
	ngx_array_t* array = ngx_array_create(pool, 10, 3* sizeof(int));
	dump_pool(pool);
dump_array(array);
	dump_pool(pool);
	for(i = 0; i < 100; ++i)
	{
		int* ptr = ngx_array_push(array);
		*ptr = i + 1;
//printf("\nElement %d added at position %d ",*ptr,i);
	}

	dump_array(array);
	dump_pool(pool);
	ngx_array_destroy(array);
	ngx_destroy_pool(pool);
}

int main()
{
	ngx_array_t_test();
	return 0;
}
