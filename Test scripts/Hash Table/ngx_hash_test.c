/ **
* Ngx_hash_t test
* In this example, it will first save URLs into the memory pool, and IPs saved in static memory.
* Then, give some examples to find IP according to a URL.
* /   
  
# include <stdio.h>   
# include "ngx_config.h   
# include "ngx_conf_file.h"   
# include "nginx.h   
# include "ngx_core.h   
# include "ngx_string.h   
# include "ngx_palloc.h   
# include "ngx_array.h   
# include "ngx_hash.h   
  
# define Max_Num 7   
# define Max_Size 1024   
# define Bucket_Size 64 / / 256, 64   
  
The # define NGX_HASH_ELT_SIZE (name) \   
(Sizeof (void *) + ngx_align ((name) -> key.len + 2, sizeof (void *)))
  
/ * For hash test * /   
static ngx_str_t urls [Max_Num] = {
ngx_string ("www.baidu.com"), / / 220.181.111.147   
ngx_string ("www.sina.com.cn"), / / 58.63.236.35   
ngx_string ("www.google.com"), / / 74.125.71.105   
ngx_string ("www.qq.com"), / / 60.28.14.190   
ngx_string ("www.163.com"), / / 123.103.14.237   
ngx_string ("www.sohu.com"), / / 219.234.82.50   
ngx_string ("www.abo321.org") / / 117.40.196.26   
};
  
static   char * values ??[MAX_NUM] = {
"220.181.111.147"
"58.63.236.35"
"74.125.71.105"
"60.28.14.190"
"123.103.14.237"
"219.234.82.50"
"117.40.196.26"   
};
  
The # define Max_Url_Len 15   
The # define Max_Ip_Len 15   
  
# define Max_Num2 a 2   
  
/ * For finding test * /   
static ngx_str_t urls2 [Max_Num2] = {
ngx_string ("www.china.com"), / / 60.217.58.79   
ngx_string ("www.programdevelop.com.net") / / 117.79.157.242   
};
  
ngx_hash_t * init_hash (ngx_pool_t * pool, ngx_array_t * array);
void dump_pool (ngx_pool_t * pool);
void dump_hash_array (ngx_array_t * a);
void dump_hash (ngx_hash_t * hash, ngx_array_t * array);
ngx_array_t * add_urls_to_array (ngx_pool_t * pool);
void find_test (ngx_hash_t * hash, ngx_str_t addr [], int num);
  
/ * For passing compiling * /   
volatile ngx_cycle_t * ngx_cycle;
void ngx_log_error_core (ngx_uint_t level, ngx_log_t * log, ngx_err_t err, const   char * fmt, ...)
{
}
  
int main (/ * int argc, char ** argv * /)
{
ngx_pool_t * pool = NULL;
ngx_array_t * array = NULL;
ngx_hash_t * hash;
  
printf ("-------------------------------- \ n");
printf ("create a new pool: \ n");
printf ("-------------------------------- \ n");
to pool = ngx_create_pool (1024, NULL);
  
dump_pool (pool);
  
printf ("-------------------------------- \ n");
printf ("create and add urls to it: \ n");
printf ("-------------------------------- \ n");
array = add_urls_to_array (pool); / / in fact, here should validate array   
dump_hash_array (array);
  
printf ("-------------------------------- \ n");
printf ("The Pool: \ n");
printf ("-------------------------------- \ n");
dump_pool (pool);
  
the hash = init_hash (pool, array);
if (hash == NULL)
{
printf ("Failed to initialize hash! \ n");
return -1;
}
  
printf ("-------------------------------- \ n");
printf ("The hash: \ n");
printf ("-------------------------------- \ n");
dump_hash (hash, array);
printf ("\ n");
  
printf ("-------------------------------- \ n");
printf ("The Pool: \ n");
printf ("-------------------------------- \ n");
dump_pool (pool);
  
/ / Find test   
printf ("-------------------------------- \ n");
printf ("the find test: \ n");
printf ("-------------------------------- \ n");
find_test (hash, urls, Max_Num);
printf ("\ n");
  
find_test (hash, urls2, Max_Num2);
  
/ / Release   
ngx_array_destroy (array);
ngx_destroy_pool (pool);
  
return 0;
}
  
ngx_hash_t * init_hash (ngx_pool_t * pool, ngx_array_t * array)
{
ngx_int_t result;
ngx_hash_init_t hinit;
  
ngx_cacheline_size = 32; / / here this variable for nginx must be defined   
hinit.hash = NULL; / / if hinit.hash is NULL, it will alloc memory for it in ngx_hash_init   
hinit.key = & ngx_hash_key_lc; / / hash function   
hinit.max_size = Max_Size;
hinit.bucket_size = Bucket_Size;
hinit.name = "my_hash_sample";
hinit.pool = pool; / / the hash table exists in the memory pool   
hinit.temp_pool = NULL;
  
result = ngx_hash_init (& hinit, (ngx_hash_key_t *) array-> elts, array-> nelts);
if (result! = NGX_OK)
return NULL;
  
return hinit.hash;
}
  
void dump_pool (ngx_pool_t * pool)
{
while (pool)
{
printf ("pool = 0x% x \ n", pool);
printf ("d \ n");
printf (". last = 0x% x \ n", pool-> d.last);
printf (". end = 0x% x \ n", pool-> d.end);
printf (". next = 0x% x \ n", pool-> d.next);
printf (". failed =% d \ n", pool-> d.failed);
printf (". max =% d \ n", pool-> max);
printf (". current = 0x% x \ n", pool-> current);
printf (". chain = 0x% x \ n", pool-> chain);
printf (". large = 0x% x \ n", pool-> large);
printf (". cleanup = 0x% x \ n", pool-> cleanup);
printf (". log = 0x% x \ n", pool-> log);
printf ("available pool memory =% d \ n \ n", pool-> d.end - pool-> d.last);
pool = pool-> d.next;
}
}
  
void dump_hash_array (ngx_array_t * a)
{
char prefix [] = "";
  
if (a == NULL)
return;
  
printf ("array = 0x% x \ n", a);
printf (". elts = 0x% x \ n", a-> elts);
printf (". nelts =% d \ n", a-> nelts);
printf (". size =% d \ n", a-> size);
printf (". nalloc =% d \ n", a-> nalloc);
printf (". pool = 0x% x \ n", a-> pool);
  
printf ("Elements: \ n");
ngx_hash_key_t * ptr = (ngx_hash_key_t *) (a-> elts);
for (; ptr <(ngx_hash_key_t *) (a-> elts + a-> nalloc * a-> size); ptr + +)
{
printf ("0x% x: {key = (\"% s \ "%. * s,% d), key_hash =%-10ld, value = \"% s \ "%. * s} \ n",
ptr, ptr-> key.data, Max_Url_Len - ptr-> key.len, prefix, ptr-> key.len,
ptr-> key_hash, ptr-> value, Max_Ip_Len - strlen (ptr-> value), prefix);
}
printf ("\ n");
}
  
/ **
* Pass array pointer to read elts [i]. Key_hash, then for getting the position - key
* /   
void dump_hash (ngx_hash_t * hash, ngx_array_t * array)
{
int loop;
char prefix [] = "";
u_short test [Max_Num] = {0};
ngx_uint_t key;
ngx_hash_key_t * ELTs;
The int nelts;
  
if (hash == NULL)
return;
  
printf ("hash = 0x% x: ** buckets = 0x% x, size =% d \ n", hash, hash-> buckets, hash-> size);
  
for (loop = 0; loop <hash-> size; loop + +)
{
ngx_hash_elt_t * elt = hash-> buckets [loop];
printf ("0x% x: buckets [% d] = 0x% x \ n", & (hash-> buckets [loop]), loop, elt);
}
printf ("\ n");
  
elts = (ngx_hash_key_t *) array-> elts;
nelts = array-> nelts;
for (loop = 0; loop <nelts; loop + +)
{
char url [Max_Url_Len + 1] = {0};
  
key = elts [loop]. key_hash% hash-> size;
ngx_hash_elt_t * elt = (ngx_hash_elt_t *) ((u_char *) hash-> buckets [key] + test [key]);
  
ngx_strlow (url, elt-> name, elt-> len);
printf ("buckets% d: 0x% x: {value = \"% s \ "%. * s, len =% d, name = \"% s \ "%. * s} \ n",
key, elt, (char *) elt-> value, Max_Ip_Len - strlen ((char *) elt-> value), prefix,
elt-> len, url, Max_Url_Len - elt-> len, prefix); / / replace elt-> name with url   
  
test [key] = (u_short) (test [key] + NGX_HASH_ELT_SIZE (& elts [loop]));
}
}
  
ngx_array_t * add_urls_to_array (ngx_pool_t * pool)
{
int loop;
char prefix [] = "";
ngx_array_t * a = ngx_array_create (pool, Max_Num, sizeof (ngx_hash_key_t));
  
for (loop = 0; loop <Max_Num; loop + +)
{
ngx_hash_key_t * hashkey = (ngx_hash_key_t *) ngx_array_push (a);
hashkey-> key = urls [loop];
hashkey-> key_hash = ngx_hash_key_lc (urls [loop]. data, urls [loop]. len);
hashkey-> value = (void *) values ??[loop];
/ ** For debug
printf ("{key = (\"% s \ "%. * s,% d), key_hash =%-10ld, value = \"% s \ "%. * s}, added to array \ n",
hashkey-> key.data, Max_Url_Len - hashkey-> key.len, prefix, hashkey-> key.len,
hashkey-> key_hash, hashkey-> value, Max_Ip_Len - strlen (hashkey-> value), prefix);
* /   
}
  
return a;
}
  
void find_test (ngx_hash_t * hash, ngx_str_t addr [], int num)
{
ngx_uint_t key;
int loop;
char prefix [] = "";
  
for (loop = 0; loop <num; loop + +)
{
the key = ngx_hash_key_lc (addr [loop] data, addr [loop]. len);
void * value = ngx_hash_find (hash, key, addr [loop]. data, addr [loop]. len);
if (value)
{
printf ("(url = \"% s \ "%. * s, key =%-10ld) found, (ip = \"% s \ ") \ n",
addr [loop]. data, Max_Url_Len - addr [loop]. len, prefix, key, (char *) value);
}
else   
{
printf ("(url = \"% s \ "%. * s, key =%-10d) not found! \ n",
addr [loop]. data, Max_Url_Len - addr [loop]. len, prefix, key);
}
}
}