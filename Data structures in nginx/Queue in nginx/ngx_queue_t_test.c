/** 
 * ngx_queue_t test 
 */  
   
#include <stdio.h>  
#include "ngx_config.h"  
#include "ngx_conf_file.h"  
#include "nginx.h"  
#include "ngx_core.h"  
#include "ngx_palloc.h"  
#include "ngx_queue.h"  
   
//2-dimensional point (x, y) queue structure  
typedef struct  
{  
    int x;  
    int y;  
} my_point_t;  
   
typedef struct  
{  
    my_point_t point;  
    ngx_queue_t queue;  
} my_point_queue_t;  
   
volatile ngx_cycle_t  *ngx_cycle;  
   
void ngx_log_error_core(ngx_uint_t level, ngx_log_t *log, ngx_err_t err,  
            const char *fmt, ...)  
{  
}  
   
void dump_pool(ngx_pool_t* pool)  
{  
    while (pool)  
    {  
        printf("pool = 0x%x\n", pool);  
        printf("  .d\n");  
        printf("    .last = 0x%x\n", pool->d.last);  
        printf("    .end = 0x%x\n", pool->d.end);  
        printf("    .next = 0x%x\n", pool->d.next);  
        printf("    .failed = %d\n", pool->d.failed);  
        printf("  .max = %d\n", pool->max);  
        printf("  .current = 0x%x\n", pool->current);  
        printf("  .chain = 0x%x\n", pool->chain);  
        printf("  .large = 0x%x\n", pool->large);  
        printf("  .cleanup = 0x%x\n", pool->cleanup);  
        printf("  .log = 0x%x\n", pool->log);  
        printf("available pool memory = %d\n\n", pool->d.end - pool->d.last);  
        pool = pool->d.next;  
    }  
}  
   
void dump_queue_from_head(ngx_queue_t *que)  
{  
    ngx_queue_t *q = ngx_queue_head(que);  
   
    printf("(0x%x: (0x%x, 0x%x)) <==> \n", que, que->prev, que->next);  
   
    for (; q != ngx_queue_sentinel(que); q = ngx_queue_next(q))  
    {  
        my_point_queue_t *point = ngx_queue_data(q, my_point_queue_t, queue);  
        printf("(0x%x: (%-2d, %-2d), 0x%x: (0x%x, 0x%x)) <==> \n", point, point->point.x,  
            point->point.y, &point->queue, point->queue.prev, point->queue.next);  
    }  
}  
   
void dump_queue_from_tail(ngx_queue_t *que)  
{  
    ngx_queue_t *q = ngx_queue_last(que);  
   
    printf("(0x%x: (0x%x, 0x%x)) <==> \n", que, que->prev, que->next);  
   
    for (; q != ngx_queue_sentinel(que); q = ngx_queue_prev(q))  
    {  
        my_point_queue_t *point = ngx_queue_data(q, my_point_queue_t, queue);  
        printf("(0x%x: (%-2d, %-2d), 0x%x: (0x%x, 0x%x)) <==> \n", point, point->point.x,  
            point->point.y, &point->queue, point->queue.prev, point->queue.next);  
    }  
}  
   
//sort from small to big  
ngx_int_t my_point_cmp(const ngx_queue_t* lhs, const ngx_queue_t* rhs)  
{  
    my_point_queue_t *pt1 = ngx_queue_data(lhs, my_point_queue_t, queue);  
    my_point_queue_t *pt2 = ngx_queue_data(rhs, my_point_queue_t, queue);  
   
    if (pt1->point.x < pt2->point.x)  
        return 0;  
    else if (pt1->point.x > pt2->point.x)  
        return 1;  
    else if (pt1->point.y < pt2->point.y)  
        return 0;  
    else if (pt1->point.y > pt2->point.y)  
        return 1;  
    return 1;  
}  
   
#define Max_Num 6  
   
int main()  
{  
    ngx_pool_t *pool;  
    ngx_queue_t *myque;  
    my_point_queue_t *point;  
    my_point_t points[Max_Num] = {  
            {10, 1}, {20, 9}, {9, 9}, {90, 80}, {5, 3}, {50, 20}  
    };  
    int i;  
   
    printf("--------------------------------\n");  
    printf("create a new pool:\n");  
    printf("--------------------------------\n");  
    pool = ngx_create_pool(1024, NULL);  
    dump_pool(pool);  
   
    printf("--------------------------------\n");  
    printf("alloc a queue head and nodes :\n");  
    printf("--------------------------------\n");  
    myque = ngx_palloc(pool, sizeof(ngx_queue_t));  //alloc a queue head  
    ngx_queue_init(myque);  //init the queue  
   
    //insert  some points into the queue  
    for (i = 0; i < Max_Num; i++)  
    {  
        point = (my_point_queue_t*)ngx_palloc(pool, sizeof(my_point_queue_t));  
        point->point.x = points[i].x;  
        point->point.y = points[i].y;  
        ngx_queue_init(&point->queue);  
   
        //insert this point into the points queue  
        ngx_queue_insert_head(myque, &point->queue);  
    }  
   
    dump_queue_from_tail(myque);  
    printf("\n");  
   
    printf("--------------------------------\n");  
    printf("sort the queue:\n");  
    printf("--------------------------------\n");  
    ngx_queue_sort(myque, my_point_cmp);  
    dump_queue_from_head(myque);  
    printf("\n");  
   
    printf("--------------------------------\n");  
    printf("the pool at the end:\n");  
    printf("--------------------------------\n");  
    dump_pool(pool);  
   
    ngx_destroy_pool(pool);  
    return 0;  
}  
