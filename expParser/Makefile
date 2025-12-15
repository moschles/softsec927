# Makefile for building mathp
# Sources and headers live in depsource/
# Object files go to obj/
# Final executable is clean/mathp
# Supports: make (release), make debug, make clean

# Toolchain
CC ?= gcc
AR ?= ar
RM ?= rm -f
MKDIR_P ?= mkdir -p

# Directories
SRCDIR := depsource
OBJDIR := obj
BINDIR := clean

# Source files (explicit to match user's list)
SRCS := $(SRCDIR)/expressionParser.c \
        $(SRCDIR)/main.c \
        $(SRCDIR)/StringBuilder.c \
        $(SRCDIR)/Stringc.c

# Headers are in SRCDIR; add include path
INCLUDES := -I$(SRCDIR)

# Build settings (release by default)
CSTD ?= -std=c11
WARNINGS ?= -Wall -Wextra -Wpedantic
RELEASE_CFLAGS ?= $(CSTD) $(WARNINGS) -O2 -pipe -fstack-protector-strong -D_FORTIFY_SOURCE=2  -ftrapping-math -fno-fast-math -fsanitize=integer-divide-by-zero,signed-integer-overflow -fno-sanitize-recover=integer-divide-by-zero,signed-integer-overflow
DEBUG_CFLAGS ?= $(CSTD) $(WARNINGS) -g -O0 -DDEBUG -D_FORTIFY_SOURCE=2 -ftrapping-math -fno-fast-math -fsanitize=integer-divide-by-zero,signed-integer-overflow  -fno-sanitize-recover=integer-divide-by-zero,signed-integer-overflow

# Use dependency generation flags so header changes rebuild objects
DEPFLAGS := -MMD -MP

# Final target
TARGET := $(BINDIR)/mathp

# Compute object files in OBJDIR
OBJS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

# Default: release build
.PHONY: all
all: CFLAGS := $(RELEASE_CFLAGS)
all: LDFLAGS :=
all: dirs $(TARGET)

# Debug build (suitable for gdb)
.PHONY: debug
debug: CFLAGS := $(DEBUG_CFLAGS)
debug: LDFLAGS := -lm
debug: dirs $(TARGET)

# Create directories
.PHONY: dirs
dirs:
	@$(MKDIR_P) $(OBJDIR)
	@$(MKDIR_P) $(BINDIR)

# Link final executable
$(TARGET): $(OBJS)
	@echo "Linking $@"
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS)

# Compile source -> object
# Pattern rule places .o and .d into OBJDIR
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@echo "Compiling $<"
	$(CC) $(CFLAGS) $(INCLUDES) $(DEPFLAGS) -c -o $@ $<

# Clean intermediate and binary
.PHONY: clean
clean:
	@echo "Cleaning objects and binary"
	-$(RM) $(OBJS) $(DEPS) $(TARGET)

# Phony target to show variables (helpful for debugging Makefile)
.PHONY: show
show:
	@printf "CC=%s\nCFLAGS=%s\nSRCDIR=%s\nOBJDIR=%s\nBINDIR=%s\nSRCS=%s\nOBJS=%s\nTARGET=%s\n" \
		"$(CC)" "$(CFLAGS)" "$(SRCDIR)" "$(OBJDIR)" "$(BINDIR)" "$(SRCS)" "$(OBJS)" "$(TARGET)"

# Include dependency files if present
-include $(DEPS)
