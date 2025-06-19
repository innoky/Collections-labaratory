CC = gcc
CFLAGS = -Wall -Wextra -g

SRC_DIR = src
TEST_DIR = tests
UNITY_DIR = $(TEST_DIR)/unity

SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/matrix.c $(SRC_DIR)/MyComplex.c $(SRC_DIR)/DataType.c
HEADERS = $(SRC_DIR)/matrix.h $(SRC_DIR)/MyComplex.h $(SRC_DIR)/DataType.h

TARGET = main
TEST_BIN = test

all: $(TARGET)

$(TARGET): $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

test: $(TEST_DIR)/UnitTests.c $(SRC_DIR)/matrix.c $(SRC_DIR)/MyComplex.c $(SRC_DIR)/DataType.c $(UNITY_DIR)/unity.c
	$(CC) $(CFLAGS) -o $(TEST_BIN) $^
	./$(TEST_BIN)

clean:
	rm -f $(TARGET) $(TEST_BIN) *.o

.PHONY: all clean test
