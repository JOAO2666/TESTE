# Makefile for UNIFIGHT Project

# Compiler and flags
CC = gcc
CFLAGS = -s -static -O2 -std=c99 -Wall -DPLATFORM_DESKTOP
# Include paths for Raylib
# IMPORTANT: User needs to verify this path is correct for their system
RAYLIB_PATH = C:/raylib/raylib
INCLUDE_PATHS = -I$(RAYLIB_PATH)/src -Iexternal
# Linker flags for Raylib
# IMPORTANT: User needs to verify this path is correct for their system
LDFLAGS = -L$(RAYLIB_PATH)/src -lraylib -lopengl32 -lgdi32 -lwinmm

# Name of the executable
EXEC = unifight.exe

# Source files
SRCS = unifight.c personagem.c ui.c efeitos.c config.c

# Object files: replace .c with .o
OBJS = $(SRCS:.c=.o)

# Resource file for Raylib (Windows specific)
# IMPORTANT: User needs to verify this path is correct for their system
RC_FILE = $(RAYLIB_PATH)/src/raylib.rc.data
RC_OBJ = raylib.rc.o

# Default target
all: $(EXEC)

# Rule to link the executable
$(EXEC): $(OBJS) $(RC_OBJ)
	$(CC) $(OBJS) $(RC_OBJ) -o $(EXEC) $(CFLAGS) $(LDFLAGS)

# Rule to compile .c files to .o files
%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE_PATHS)

# Rule to compile the resource file (Windows specific)
$(RC_OBJ): $(RC_FILE)
	windres -i $(RC_FILE) -o $(RC_OBJ)

# Clean rule
clean:
	del /Q $(OBJS) $(EXEC) $(RC_OBJ) # Windows
	# For Linux/macOS, use: rm -f $(OBJS) $(EXEC) $(RC_OBJ)

# Phony targets
.PHONY: all clean
