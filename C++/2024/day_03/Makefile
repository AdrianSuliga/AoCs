CC = g++
CFLAGS = -Wall -std=c++17 -g -I../../utils

SRCS = main.cpp ../../utils/data_parsing/file_read.cpp ../../utils/presentation/custom_print.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = main

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

.PHONY: all run clean

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET) input.txt 0

all:
	make $(TARGET) && make run

clean:
	rm $(TARGET) $(OBJS)
