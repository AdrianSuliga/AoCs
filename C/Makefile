CC = gcc
CFLAGS = -Wall -std=c17 -g -I./utils

# All needed .c files
SRCS = ./2024/day_01/main.c ./2024/day_02/main.c \
       ./2024/day_03/main.c ./2024/day_04/main.c \
	   ./2024/day_05/main.c ./2024/day_06/main.c \
	   ./2024/day_07/main.c ./2024/day_08/main.c \
	   ./utils/data_parsing/file_read.c \
	   ./utils/memory/custom_allocation.c \
	   ./utils/presentation/custom_print.c \
	   ./utils/sorting/heap_sort.c

# All needed object files
UTIL_OBJS = \
	./utils/data_parsing/file_read.o \
	./utils/memory/custom_allocation.o \
	./utils/presentation/custom_print.o \
	./utils/sorting/heap_sort.o

# All needed binaries
RUNNABLES = day_01 day_02 day_03 day_04 day_05 \
			day_06 day_07 day_08

BINS = $(RUNNABLES:%=2024/%/main)
OBJS = $(SRCS:.c=.o)

.PHONY: test clean
.SECONDARY: 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

2024/%/main: 2024/%/main.o $(UTIL_OBJS)
	$(CC) $^ -o $@

test: $(BINS)
	@for bin in $(BINS); do \
		dir=$$(dirname $$bin); \
		./$$bin $$dir/input.txt 1; \
	done

clean:
	rm $(OBJS) $(BINS)
