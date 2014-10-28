#include <stdio.h>
#include "ngx_config.h"
#include "ngx_conf_file.h"
#include "nginx.h"
#include "ngx_core.h"
#include "ngx_string.h"
#include "ngx_palloc.h"

volatile ngx_cycle_t *ngx_cycle;
void ngx_log_error_core(ngx_uint_t level, ngx_log_t *log, ngx_err_t err,const char *fmt, ...)
{
}

int main(){
    printf("\n");
	printf("A sample string created using macro definition.The macro defines both length and data\n");
    ngx_str_t str = ngx_string("A sample string");
    printf("\nstr.data = %s",str.data);
    printf("\nstr.len = %d",str.len);
    //ngx_toupper(str);
    ngx_str_set(str,'hello');
    printf("\nstr.data = %s",str.data);
    printf("\nstr.len = %d",str.len);
    //printf("\n str in uppercase : %s",str.data);
    ngx_str_t dst;
    ngx_str_null(&dst);
    ngx_encode_base64(&dst,&str);
    printf("\ndst.data = %s",dst.data);
    printf("\ndst.len = %d",dst.len);
    printf("\n");
}
