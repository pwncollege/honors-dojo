# Target
TARGET=program

# Build Tools
CC=gcc
CFLAGS=-Og -g

# Leaving debug information in to be nice :)

# Sources
SOURCES=src/program.c

# Default target
all: $(TARGET)

$(TARGET): $(SOURCES)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $<

# Clean build
clean:
	rm -rf build
