# define paths to libraries in use
LIBRARIES	:= ../../../lib/uc_includes ../../../lib/16FXlib

# Set multiple macros appending "-D MACRO_NAME" (only definition) or
# "-D MACRO_NAME=VALUE" to the MACROS variable below.
# E.g. "-D ENABLE_FRAMEBUFFER" may be used to activate the framebuffer
# when using the 16FXlib (requires recompilation of the library).
MACROS		:= -D BOARD

# include main makefile
include ../../../c.mk

# compile using gcc (without the macros defined above: output via printf)
gcc:
	gcc main.c

# expand the clean rule to clear gcc's output
clean::
	rm *.out
