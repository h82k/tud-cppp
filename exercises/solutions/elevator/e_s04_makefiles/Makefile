# $<	the first dependency
# $@	name of the target
# $+	list of all dependencies
# $^	list of all dependencies (unique elements)

# delete the default suffixes (disable implicit rules)
.SUFFIXES:
# PHONY targets (targets that do not represent a file)
.PHONY: clean all

# compiler options
CC		= g++
# -Wall 		show all warnings
# -MMD -MP		generate dependencies to header files so that make recognizes changes to header files,
#				which otherwise do not appear explicitly in any rule
# -std=c++11	enable C++11
CFLAGS	= -Wall -std=c++11 -MMD -MP

# source code
BINARY	= main.exe
SOURCES	= $(wildcard ./*.cpp)
OBJECTS	= $(patsubst %.cpp, %.o, $(SOURCES))
DEPEND	= $(patsubst %.cpp, %.d, $(SOURCES))

# default target (create the binary)
all: $(BINARY)

# include dependencies to detect header file changes (this creates new targets!)
-include $(DEPEND)

# create the binary
$(BINARY): $(OBJECTS)
	$(CC) -o $(BINARY) $^

# create an object file from a source file
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECTS) $(DEPEND) $(BINARY)
