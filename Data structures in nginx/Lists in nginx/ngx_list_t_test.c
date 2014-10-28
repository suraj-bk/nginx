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


void dump_list(ngx_list_t* list)
{
	if (list == NULL)
	{
		return;
	}

	printf("list = 0x%x\n", list);
	printf("	.last = 0x%x\n", list->last);
	printf("	.part = 0x%x\n", &(list->part));
	printf("	.size = %lu\n", list->size);
	printf("	.nalloc = %u\n", list->nalloc);
	printf("	.pool\n", list->pool);

	printf("element:\n");

	ngx_list_part_t* part = &(list->part);
	while(part)
	{
		dump_list_part(list, part);
		part = part->next;
	}
	printf("\n");
}

void dump_pool(ngx_pool_t* pool)
{
 	while(pool)
 	{
 		printf("pool = 0x%x\n", pool);
 		printf(" .d\n");
 		printf("    .last = 0x%x\n", pool->d.last);
		printf("    .end = 0x%x\n", pool->d.end);
		printf("    .next = 0x%x\n", pool->d.next);
		printf("    .failed = %d\n", pool->d.failed);
		printf(" .max = %lu\n", pool->max);
		printf(" .current = 0x%x\n", pool->current);
		printf(" .chain = 0x%x\n", pool->chain);
		printf(" .large = 0x%x\n", pool->large);
		printf(" .cleanup = 0x%x\n", pool->cleanup);
		printf(" .log = 0x%x\n", pool->log);
		printf("available pool memory = %d\n\n", pool->d.end - pool->d.last);
		pool = pool->d.next;
 	}
}

void dump_list_part(ngx_list_t* list, ngx_list_part_t* part)
{
	int* ptr = (int*)(part->elts);
	int loop = 0;

	printf(" .part = 0x%x\n", &(list->part));
	printf("	.elts = 0x%x", part->elts);

	printf("(");
	for (; loop < list->nalloc - 1; ++loop)
	{
		printf("%d, ", ptr[loop]);
	}
	printf("%d)\n", ptr[loop]);
	printf("	.nelts = %d\n", part->nelts);
	printf("	.next = 0x%x", part->next);
	if (part->next)
	{
		printf("-->\n");
	}
	printf("\n");
}

void ngx_list_t_test()
{
	ngx_pool_t* pool;
	int i = 0;

	printf("----------------------------------\n");
	printf("the size of ngx_list_part_t:\n");
	printf("----------------------------------\n");
	printf("%lu\n\n", sizeof(ngx_list_part_t));

	printf("----------------------------------\n");
	printf("the size of ngx_list_t:\n");
	printf("----------------------------------\n");
	printf("%lu\n\n", sizeof(ngx_list_t));

	printf("----------------------------------\n");
	printf("create a new pool:\n");
	printf("----------------------------------\n");
	pool = ngx_create_pool(1024, NULL);
	dump_pool(pool);

	printf("----------------------------------\n");
	printf("alloc an list from the pool:\n");
	printf("----------------------------------\n");
	ngx_list_t* list = ngx_list_create(pool, 5, sizeof(int));
	dump_pool(pool);

	for (i = 0; i < 300; ++i)
	{
		int* ptr = ngx_list_push(list);
		*ptr = i + 1;
	}

	printf("----------------------------------\n");
	printf("the list information:\n");
	printf("----------------------------------\n");
	dump_list(list);

	printf("----------------------------------\n");
	printf("the pool at the end:\n");
	printf("----------------------------------\n");
	dump_pool(pool);

    ngx_destroy_pool(pool);
}

int main()
{
	ngx_list_t_test();
	return 0;

}
