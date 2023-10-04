# Compiler and flags
CC = gcc
CFLAGS = -Wall -Iinclude

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INCLUDE_DIR = include

# Files and targets
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TARGET = $(BIN_DIR)/main

# Libraries for bluez
LIBS = -lbluetooth

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJ)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

# Compilation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean
