CC = gcc
CFLAGS = -Wall -Wextra -g

SRCS = main.c matrix.c complex.c
HEADERS = matrix.h complex.h DataType.h

TARGET = main
all: $(TARGET)

$(TARGET): $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET) *.o

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean