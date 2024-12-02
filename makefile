# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -I./header
LDFLAGS = # Any additional linking flags if needed
DEBUG_FLAGS = -g # Debugging flags

# Directories
OBJ_DIR = obj
SRC_DIR = .
INC_DIR = header
BIN_DIR = .

# Source files
SRC = $(SRC_DIR)/main.c $(INC_DIR)/B-type.c $(INC_DIR)/decode.c $(INC_DIR)/file_read.c $(INC_DIR)/I-type.c \
      $(INC_DIR)/J-type.c $(INC_DIR)/registers.c $(INC_DIR)/R-type.c $(INC_DIR)/S-type.c $(INC_DIR)/U-type.c

# Object files
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Executable
EXEC = $(BIN_DIR)/main
DEBUG_EXEC = $(BIN_DIR)/main_debug

# Create the object directory if it doesn't exist
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link the object files to create the executable
$(EXEC): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $(EXEC)

# Link the object files to create the debug executable
$(DEBUG_EXEC): $(OBJ)
	$(CC) $(LDFLAGS) $(DEBUG_FLAGS) $(OBJ) -o $(DEBUG_EXEC)

# Create the binary directory if it doesn't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Create the object directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean up object and executable files
clean:
	@echo "cleaning up"
	@if [ "$(OBJ_DIR)" != "." ] && [ "$(OBJ_DIR)" != ".." ]; then rm -rf $(OBJ_DIR); else echo "Skipping invalid OBJ_DIR"; fi
	@if [ "$(BIN_DIR)" != "." ] && [ "$(BIN_DIR)" != ".." ]; then rm -rf $(BIN_DIR); else echo "Skipping invalid BIN_DIR"; fi

# Build for debugging
debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(DEBUG_EXEC)

.PHONY: clean debug
