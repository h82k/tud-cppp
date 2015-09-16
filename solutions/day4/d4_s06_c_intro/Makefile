# $<	the first dependency
# $@	name of the target
# $+	list of all dependencies
# $^	list of all dependencies (unique elements)

# delete the default suffixes (disable implicit rules)
.SUFFIXES:
# PHONY targets (targets that do not represent a file)
.PHONY: clean all

# compiler options
CC		= gcc
# -g			add debugging symbols to the binary
# -O0			deactivate optimizations
# -Wall			show reasonable warnings
# -Wextra		show more warnings
# -MMD -MP		generate dependencies to header files so that make recognizes changes to header files,
#				which otherwise do not appear explicitly in any rule
CFLAGS	= -g -O0 -Wall -Wextra -MMD -MP
BUILD	= build

# source code
BINARY	= main.exe
SOURCES	= $(wildcard *.c)
OBJECTS	= $(patsubst %.c, $(BUILD)/%.o, $(SOURCES))
DEPEND	= $(patsubst %.c, $(BUILD)/%.d, $(SOURCES))

# default target (create the binary)
all: $(BINARY)

# include dependencies to detect header file changes (this creates new targets!)
-include $(DEPEND)

# create the binary
$(BINARY): $(OBJECTS)
	$(CC) -o $(BINARY) $^

# create an object file from a source file
$(BUILD)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD) $(BINARY)
