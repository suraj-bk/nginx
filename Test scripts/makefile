CC  =  gcc
CFLAGS += -g -Wall -Wextra -w

NGX_ROOT = /home/suraj/Desktop/suraj/src/nginx-1.7

TARGETS = ./memory_management_C_program/ngx_pool_t_test
TARGET_C_FILE = $(TARGETS).c
CLEANUP = rm -f $(TARGETS) *.o

all: $(TARGETS)

clean:
	$(CLEANUP)


CORE_INCS = -I. \
-I./nginx_src/src/core \
-I./nginx_src/src/event \
-I./nginx_src/src/event/modules \
-I./nginx_src/src/os/unix \
-I./nginx_src/objs \

0BJPATH =./nginx_src/objs/*.o \
./nginx_src/objs/src/os/unix/*.o \
./nginx_src/objs/src/core/*.o \
./nginx_src/objs/src/event/*.o \
./nginx_src/objs/src/event/modules /*.o \
./nginx_src/objs/src/http/*.o \
./nginx_src/objs/src/http/modules/*.o 

LFLAGS = -lstdc ++ -lpthread -ldl -rdynamic -lcrypt -lpthread -lpcre -lcrypto -lcrypto

NGX_PALLOC =./nginx_src/objs/src/core/ngx_palloc.o
NGX_STRING =./nginx_src/objs/src/core/ngx_string.o
NGX_ALLOC =./nginx_src/objs/src/os/unix/ngx_alloc.o

$(TARGETS): $(TARGET_C_FILE)  $(OBJPATH)
	$(CC) $(CFLAGS) $(CORE_INCS) $(NGX_PALLOC) $(NGX_STRING) $(NGX_ALLOC) $^ -o $@ 
