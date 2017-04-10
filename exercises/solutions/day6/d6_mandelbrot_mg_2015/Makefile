
ifndef EXERCISES_ROOT
$(error EXERCISES_ROOT not defined!)
endif

# define paths to libraries in use
LIBRARIES := $(EXERCISES_ROOT)/lib/uc_includes $(EXERCISES_ROOT)/lib/16FXlib

# Set multiple macros appending "-D MACRO_NAME" (only definition) or
# "-D MACRO_NAME=VALUE" to the MACROS variable below.
# E.g. "-D ENABLE_FRAMEBUFFER" may be used to activate the framebuffer
# when using the 16FXlib (requires recompilation of the library).
MACROS		:= -D BOARD

# include main makefile
include $(EXERCISES_ROOT)/c.mk

# compile using gcc (without the macros defined above: output via printf)
gcc:
	gcc main.c

# expand the clean rule to clear gcc's output
clean::
	rm -rf *.out
