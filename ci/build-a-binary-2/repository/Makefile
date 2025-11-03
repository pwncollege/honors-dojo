# Target
TARGET=build/program

# Build Tools
CC=gcc
CFLAGS=-O2 -fdebug-prefix-map=$PWD=. -frandom-seed=42 -Wl,--build-id=none
# ^ Making compilation deterministic so we can hash it

# Sources
SOURCES=src/program.c

# Default target
all: $(TARGET)

$(TARGET): $(SOURCES)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $<
	strip --strip-all $@
	objcopy --adjust-section-vma .text=0 --adjust-section-vma .data=0 $@ $@.normalized
	mv $@.normalized $@
	sha256sum $@

# Clean build
clean:
	rm -rf build
