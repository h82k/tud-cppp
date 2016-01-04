# delete the default suffixes (disable implicit rules)
.SUFFIXES:
.PHONY: all framebuffer clean

# wine/softune related
PREFIX		:= ~/tools
FCC907S		:= WINEPREFIX=$(PREFIX) wine $(PREFIX)/drive_c/Softune/bin/fcc907s.exe
FASM907S	:= WINEPREFIX=$(PREFIX) wine $(PREFIX)/drive_c/Softune/bin/FASM907S.EXE

# sources
INCLUDE		:= uc_includes
SOURCES		:= $(shell find . -name "*.c")
ASM_PRE		:= $(shell find . -name "*.asm")
ASM			:= $(patsubst %.c, %.asm, $(SOURCES))
OBJECTS		:= $(patsubst %.asm, %.o, $(ASM) $(ASM_PRE))

# compiler flags
AFLAGS		:= -cpu MB96F348HSB -w 2 -pl 60 -pw 132 -linf OFF -lsrc OFF -lsec OFF -lcros OFF -linc OFF
CFLAGS		:= -cpu MB96F348HSB -w 5 -INF srcin -T p,-B -I $(INCLUDE) -O 4 -K SPEED -K NOUNROLL -K NOLIB -K NOEOPT -K NOADDSP -K NOALIAS -B -model MEDIUM -ramconst -S

# default target
all: $(OBJECTS)
	# The following rule catches cases where the submodules have not been checked out properly
	[ -z "$(OBJECTS)" ] && echo "OBJECTS is empty!"; exit -1

# build with framebuffer enabled
framebuffer: CFLAGS+=-D ENABLE_FRAMEBUFFER
framebuffer: all

# generate assembly file
%.asm: %.c
	-$(FCC907S) $(CFLAGS) -o $@ $<

# generate object file
%.o: %.asm
	$(FASM907S) $(AFLAGS) -o $@ $<

clean:
	rm -rf $(OBJECTS)
	rm -rf $(ASM)
