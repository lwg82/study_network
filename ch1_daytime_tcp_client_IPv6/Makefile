# $^ 全部依赖
# $@ 目标文件
# $< 第一个依赖
# $? 第一个变化的依赖

PROJ := daytime_tcp_client

CC := gcc
CFLAGS := -g -Wall -O0

SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)


$(PROJ): $(OBJS)
	$(CC) $^ -o $@ $(INCLUDES) $(LIBS) 

%.o: %.c
	$(CC) $(CFLAGS) -c $< 

clean:
	rm -rf *.o $(PROJ)

.PHONY:clean



