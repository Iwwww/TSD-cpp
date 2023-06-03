CC = g++
CFLAGS = -Wall -Wextra -std=c++11

# Directories
SRCDIR = hashTable
BUILDDIR = build

# Source files
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRCS))

# Main executable
EXECUTABLE = main

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS) main.cpp
	$(CC) $(CFLAGS) $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILDDIR) $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

