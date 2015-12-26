# delete the default suffixes (disable implicit rules)
.SUFFIXES:
.PHONY: all clean

# wine/softune related
PREFIX		= ~/tools
FCC907S		= WINEPREFIX=$(PREFIX) wine $(PREFIX)/drive_c/Softune/bin/fcc907s.exe
FASM907S	= WINEPREFIX=$(PREFIX) wine $(PREFIX)/drive_c/Softune/bin/FASM907S.EXE

# sources
INCLUDE		= uc_includes
SOURCES		= $(shell find . -name "*.c")
ASM			= $(shell find . -name "*.asm") $(patsubst %.c, %.asm, $(SOURCES))
OBJECT		= $(patsubst %.asm, %.o, $(ASM))

# compiler flags
AFLAGS		= -cpu MB96F348HSB -w 2 -pl 60 -pw 132 -linf OFF -lsrc OFF -lsec OFF -lcros OFF -linc OFF
CFLAGS		= -cpu MB96F348HSB -w 5 -INF srcin -T p,-B -I $(INCLUDE) -O 4 -K SPEED -K NOUNROLL -K NOLIB -K NOEOPT -K NOADDSP -K NOALIAS -B -model MEDIUM -ramconst -S

# default target
all: $(OBJECT)

# generate assembly file
%.asm: %.c
	-$(FCC907S) $(CFLAGS) -o $@ $<

# generate object file
%.o: %.asm
	$(FASM907S) $(AFLAGS) -o $@ $<

clean:
	rm -rf $(OBJECT)
