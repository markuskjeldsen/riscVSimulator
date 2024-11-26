# Compiler and flags
CC = gcc
CFLAGS = -g -Wall -Wextra -Iheader
LDFLAGS = 

# Directories
SRCDIR = .
INCDIR = header
TESTDIR = tests
OBJDIR = obj

# Files
SRCS = $(wildcard $(SRCDIR)/*.c) $(wildcard $(INCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
TARGET = convert_linux
DEBUG_TARGET = debug_$(TARGET)

# Default target
all: $(TARGET)

# Compile source files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(INCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files into the executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Debug build
debug: CFLAGS += -DDEBUG
debug: $(DEBUG_TARGET)

$(DEBUG_TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Clean up
clean:
	rm -rf $(OBJDIR) $(TARGET) $(DEBUG_TARGET)

# Debugging target
debug_run: $(DEBUG_TARGET)
	gdb $(DEBUG_TARGET)

# Run program with an optional test file
run: $(TARGET)
	./$(TARGET) $(TESTDIR)/$(TEST)

.PHONY: all clean debug debug_run run

