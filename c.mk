# delete the default suffixes (disable implicit rules)
.SUFFIXES:
.PHONY: all clean clean-all com

# wine command
PREFIX		:= ~/tools
DEBUG		:= -all
WINE		:= WINEPREFIX=$(PREFIX) WINEDEBUG=$(DEBUG) wine

# installation dirs
SOFTUNE_DIR	:= $(PREFIX)/drive_c/Softune/bin
FLASHLY_DIR	:= $(PREFIX)/drive_c/FLASHly

# wine com port (e.g. use "make WIN_PORT=2" to use the second port)
WIN_PORT	:= 1
COM			:= $(PREFIX)/dosdevices/com$(WIN_PORT)

# linux serial port (either via USB or directly forwarded)
LIN_PORT	= $(shell echo $$(($(WIN_PORT)-1)))
USB			= /dev/ttyUSB$(LIN_PORT)
SERIAL		= /dev/ttyS$(LIN_PORT)

# aliases
FCC907S		:= $(WINE) $(SOFTUNE_DIR)/fcc907s.exe
FASM907S	:= $(WINE) $(SOFTUNE_DIR)/FASM907S.EXE
FLNK907S	:= $(WINE) $(SOFTUNE_DIR)/FLNK907S.EXE
F2MS		:= $(WINE) $(SOFTUNE_DIR)/F2MS.EXE
FLASHLY		:= $(WINE) $(FLASHLY_DIR)/FLASHly.exe

# sources
SOURCES		:= $(sort $(shell find . -name "*.c"))
ASM			:= $(patsubst %.c, %.asm, $(SOURCES))
OBJECT		:= $(patsubst %.asm, %.o, $(ASM))

# library sources
LIB_SOURCES	:= $(shell find $(LIBRARIES) -name "*.c")
LIB_ASM_PRE	:= $(shell find $(LIBRARIES) -name "*.asm")
LIB_ASM		:= $(patsubst %.c, %.asm, $(LIB_SOURCES))
LIB_OBJECTS	:= $(patsubst %.asm, %.o, $(LIB_ASM) $(LIB_ASM_PRE))

# flags
CPU			:= MB96F348HSB
AFLAGS		:= -cpu $(CPU) -w 2 -pl 60 -pw 132 -linf OFF -lsrc OFF -lsec OFF -lcros OFF -linc OFF
CFLAGS		:= -cpu $(CPU) -w 5 -INF srcin -T p,-B $(addprefix -I , $(LIBRARIES)) -O 4 -K SPEED -K NOUNROLL -K NOLIB -K NOEOPT -K NOADDSP -K NOALIAS -B -model MEDIUM -ramconst -S
LFLAGS		:= -cpu $(CPU) -w 2 $(addprefix -L , $(LIBRARIES)) -Xset_rora -pl 60 -pw 132 -a -AL 2 -ro _INROM01=0x00ff0000/0x00ffffff -ra _INRAM01=0x00002240/0x00007fff -rg 0 -Xm -NCI0302LIB
FFLAGS		:= -cpu $(CPU) -c:$(WIN_PORT) -m:RTS- -r:DTR+ -Q:4 -E:DF0000 -E:FF0000 -nolog -newlog -msgok

# default target
all: flash_main

# create a com port either using ttyUSBX or ttySX
com:
ifeq ($(wildcard $(USB)),)
	ln -sf $(SERIAL) $(COM)
else
	ln -sf $(USB) $(COM)
endif

# generate assembly file
%.asm: %.c
%.asm: %.c
	-$(FCC907S) $(CFLAGS) -o $@ $<

# generate object file
%.o: %.asm
	$(FASM907S) $(AFLAGS) -o $@ $<

# link object files
%.abs: $(OBJECT) $(LIB_OBJECTS)
	$(FLNK907S) $(LFLAGS) -o $@ $^

# create file to be flashed
%.mhx: %.abs
	$(F2MS) -S2 $< -o $@

# flash the program
flash_%: %.mhx com
	$(FLASHLY) $(FFLAGS) -P: $<

clean:
	rm -rf $(OBJECT)
	rm -rf $(ASM)
	rm -rf *.mhx
	rm -rf *.abs

clean-all: clean
	rm -rf $(LIB_OBJECTS)
	rm -rf $(LIB_ASM)

.PRECIOUS:%.mhx $(LIB_OBJECTS)
