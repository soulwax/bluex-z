# Makefile: 
# Folder structure:
# - src (source files)
# - obj (object files)
# - bin (binary files)
# - include (header files)
# - lib (library files)
# - doc (documentation files)

# Flags: gcc src/main.c -o obj/main.o -lbluetooth


# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c99 -g

# Linker flags
LDFLAGS = -lbluetooth

# Source files
SRC = $(wildcard src/*.c)

# Object files
OBJ = $(SRC:src/%.c=obj/%.o)

# Binary files
BIN = bin/bluex-zvx

# Default target
all: $(BIN)

# Linking
$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(BIN) $(LDFLAGS)

# Compiling
obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(OBJ) $(BIN)
