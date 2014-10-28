#include <stdio.h>
 #include "ngx_config.h"
 #include "ngx_conf_file.h"
 #include "nginx.h"
 #include "ngx_core.h"
 #include "ngx_string.h"
 #include "ngx_palloc.h"
 #include "ngx_array.h"
#include "ngx_rbtree.h"
#include<time.h>


 volatile ngx_cycle_t * ngx_cycle;

 void
 ngx_log_error_core (ngx_uint_t level, ngx_log_t * log, ngx_err_t err,
             const char * fmt, ...)
 {
 }



void main(){
	int i,n;
    typedef struct rbtree{
        ngx_rbtree_node_t rb_node;
        int elem;
    }RB_NODE;

    ngx_rbtree_t tmp_rb;
	ngx_rbtree_node_t sentinel;
//sentinel.elem = 0;
    ngx_rbtree_init(&tmp_rb,&sentinel,&ngx_rbtree_insert_value);
    RB_NODE tmp_rb_node[30];

	printf("Enter the number of nodes : ");
	scanf("%d",&n);
	printf("\nEnter the elements : ");
	for(i=0;i<n;i++){
		scanf("%d",&tmp_rb_node[i].elem );
		tmp_rb_node[i].rb_node.key = tmp_rb_node[i].elem;
        ngx_rbtree_insert(&tmp_rb,&tmp_rb_node[i].rb_node);
	}

   /*for(i = 0;i<5;++i){
        tmp_rb_node[i].elem = i+1;
        tmp_rb_node[i].rb_node.key = tmp_rb_node[i].elem;
        ngx_rbtree_insert(&tmp_rb,&tmp_rb_node[i].rb_node);
    }*/
	
	void disp(){
	disp()
		printf("%d\t",);
	}
	printf("Value  |  Color  |  Left pointer address  |  Right poiner address  |  Parent address  |  Current node address \n");
	for(i=0;i<n;i++){
		printf("\n");

		printf(" %d          %d         0x%x                  0x%x             0x%x           0x%x ",tmp_rb_node[i].elem,tmp_rb_node[i].rb_node.color,tmp_rb_node[i].rb_node.left,tmp_rb_node[i].rb_node.right,tmp_rb_node[i].rb_node.parent,&tmp_rb_node[i].rb_node);
	}
printf("\n");
}

