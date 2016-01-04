# define paths to libraries in use
LIBRARIES	:= ../../../lib/uc_includes ../../../lib/16FXlib
# macros used during compilation targeting the board
MACROS		:= -D BOARD
# include main makefile
include ../../../c.mk
# compile with gcc without the macro targeting a standard pc (output via printf)
gcc:
	gcc main.c
clean::
	rm *.out
