CC = gcc
CFLAGS = -Wall -std=c17 -g -I../../utils

SRCS = main.c ../../utils/data_parsing/file_read.c ../../utils/memory/custom_allocation.c
OBJS = $(SRCS:.c=.o)
TARGET = main

.PHONY: all run clean

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET) input.txt 0

all:
	make $(TARGET) && make run

clean:
	rm $(TARGET) $(OBJS)
