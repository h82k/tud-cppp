# delete the default suffixes (disable implicit rules)
.SUFFIXES:
.PRECIOUS:%.mhx
.PHONY: all clean

# wine command
PREFIX		= ~/tools
DEBUG		= -all
WINE		= WINEPREFIX=$(PREFIX) WINEDEBUG=$(DEBUG) wine

# installation dirs
SOFTUNE_DIR	= $(PREFIX)/drive_c/Softune/bin
FLASHLY_DIR	= $(PREFIX)/drive_c/FLASHly

# aliases
FCC907S		= $(WINE) $(SOFTUNE_DIR)/fcc907s.exe
FASM907S	= $(WINE) $(SOFTUNE_DIR)/FASM907S.EXE
FLNK907S	= $(WINE) $(SOFTUNE_DIR)/FLNK907S.EXE
F2MS		= $(WINE) $(SOFTUNE_DIR)/F2MS.EXE
FLASHLY		= $(WINE) $(FLASHLY_DIR)/FLASHly.exe

# sources
#INCLUDE	= uc_includes library
#SOURCES	= main.c $(wildcard $(addsuffix /*.c, $(INCLUDE)))
#ASM		= $(wildcard $(addsuffix /*.asm, $(INCLUDE))) $(patsubst %.c, %.asm, $(SOURCES))
INCLUDE		= $(shell find . -type d)
SOURCES		= $(shell find . -name "*.c")
ASM			= $(shell find . -name "*.asm") $(patsubst %.c, %.asm, $(SOURCES))
OBJECT		= $(patsubst %.asm, %.o, $(ASM))
INCLUDE		:= $(addprefix -I , $(INCLUDE))

# flags
CPU			= MB96F348HSB
COM			= 1
AFLAGS		= -cpu $(CPU) -w 2 -pl 60 -pw 132 -linf OFF -lsrc OFF -lsec OFF -lcros OFF -linc OFF
CFLAGS		= -cpu $(CPU) -w 5 -INF srcin -T p,-B $(INCLUDE) -O 4 -K SPEED -K NOUNROLL -K NOLIB -K NOEOPT -K NOADDSP -K NOALIAS -B -model MEDIUM -ramconst -S
LFLAGS		= -cpu $(CPU) -w 2 -Xset_rora -pl 60 -pw 132 -a -AL 2 -ro _INROM01=0x00ff0000/0x00ffffff -ra _INRAM01=0x00002240/0x00007fff -rg 0 -Xm -NCI0302LIB
FFLAGS		= -cpu $(CPU) -c:$(COM) -m:RTS- -r:DTR+ -Q:4 -E:DF0000 -E:FF0000 -nolog -newlog -msgok -P:

# default target
all: flash_main

# generate assembly file
%.asm: %.c
%.asm: %.c
	-$(FCC907S) $(CFLAGS) -o $@ $<

# generate object file
%.o: %.asm
	$(FASM907S) $(AFLAGS) -o $@ $<

# link object files
%.abs: $(OBJECT)
	$(FLNK907S) $(LFLAGS) -o $@ $^

# create file to be flashed
%.mhx: %.abs
	$(F2MS) -S2 $< -o $@

# flash the program
flash_%: %.mhx
	$(FLASHLY) $(FFLAGS) $<

clean:
	rm -rf *.asm
	rm -rf $(OBJECT)
	rm -rf *.mhx
	rm -rf *.abs
