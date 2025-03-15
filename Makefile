CC = gcc
CFLAGS = -Wall -Wextra -g 
LDFLAGS = -mconsole

SRC_DIR = src
TEST_DIR = tests
UNITY_DIR = tests\unity

SRC = $(SRC_DIR)\main.c $(SRC_DIR)\matrix.c $(SRC_DIR)\MyComplex.c 
OBJ = $(SRC:.c=.o)

TEST_SRC = $(TEST_DIR)\UnitTests.c $(UNITY_DIR)\unity.c
TEST_OBJ = $(TEST_SRC:.c=.o)
TEST_EXEC = $(TEST_DIR)\UnitTests.exe

TARGET = main.exe


$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)


$(TEST_EXEC): $(filter-out $(SRC_DIR)\main.o, $(OBJ)) $(TEST_OBJ)
	$(CC) $(filter-out $(SRC_DIR)\main.o, $(OBJ)) $(TEST_OBJ) -o $(TEST_EXEC) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@if exist $(SRC_DIR)\main.o del $(SRC_DIR)\main.o
	@if exist $(SRC_DIR)\matrix.o del  $(SRC_DIR)\matrix.o
	@if exist $(SRC_DIR)\MyComplex.o del $(SRC_DIR)\MyComplex.o
	@if exist $(TEST_DIR)\UnitTests.o del $(TEST_DIR)\UnitTests.o
	@if exist $(UNITY_DIR)\unity.o del $(UNITY_DIR)\unity.o
