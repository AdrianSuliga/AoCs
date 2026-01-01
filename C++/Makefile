CC = g++
CFLAGS = -Wall -std=c++17 -g -I./utils

# All needed .c files
SRCS = ./2024/day_01/main.cpp ./2024/day_02/main.cpp \
       ./2024/day_03/main.cpp ./2024/day_04/main.cpp \
	   ./2024/day_05/main.cpp ./2024/day_06/main.cpp \
	   ./2024/day_07/main.cpp \
	   ./utils/data_parsing/file_read.cpp \
	   ./utils/presentation/custom_print.cpp

# All needed object files
UTIL_OBJS = \
	./utils/data_parsing/file_read.o \
	./utils/presentation/custom_print.o

# All needed binaries
RUNNABLES = day_01 day_02 day_03 day_04 day_05 \
			day_06 day_07

BINS = $(RUNNABLES:%=2024/%/main)
OBJS = $(SRCS:.cpp=.o)

.PHONY: test clean
.SECONDARY:

%.o: %.cpp
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
