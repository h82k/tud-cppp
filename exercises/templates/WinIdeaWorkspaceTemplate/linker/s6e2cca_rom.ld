INPUT (& &)
OUTPUT_FORMAT ("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
ENTRY(__FM_reset_cortex_m)
SEARCH_DIR(.)
GROUP(-lgcc -lc)
MEMORY
{
   ROM   (rx)   : ORIGIN = 0x00000000, LENGTH = 2048K
   IROM2 (rx)   : ORIGIN = 0x00406000, LENGTH = 40K
   RAM   (rwx)  : ORIGIN = 0x1FFD0000, LENGTH = 192K
   IRAM2 (rwx)  : ORIGIN = 0x20038000, LENGTH = 64K
}

/* These force the linker to search for particular symbols from
 * the start of the link process and thus ensure the user's
 * overrides are picked up
 */
EXTERN(__FM_reset_cortex_m)
EXTERN(__FM_interrupt_vector_cortex_m)
EXTERN(__FM_start_c main __FM_stack __FM_stack_size __FM_heap_size)

PROVIDE(__FM_stack = __FM_region_start_ram + __FM_region_size_ram);
PROVIDE(__FM_stack_start = __FM_stack - __FM_stack_size);
PROVIDE(__FM_heap_start = __FM_stack - __FM_stack_size - __FM_heap_size);

/* default values if not defined externally
 */
PROVIDE(__FM_stack_size = 0x00000400);
PROVIDE(__FM_heap_size  = 0x00000400);

SECTIONS
{
  .text :
  {
    CREATE_OBJECT_SYMBOLS
    __FM_region_start_rom = .;
    *(.FM.region-head.ROM)
    __FM_interrupt_vector = __FM_interrupt_vector_cortex_m;
    *(.FM.interrupt_vector)
    /* Make sure we pulled in an interrupt vector.  */
    ASSERT (. != __FM_interrupt_vector_cortex_m, "No interrupt vector");
    *(.ROM)
    *(.ROM.b)

    __FM_reset = __FM_reset_cortex_m;
    *(.FM.reset)
    /* Make sure we pulled in some reset code.  */
    ASSERT (. != __FM_reset, "No reset code");

    *(.text .text.* .gnu.linkonce.t.*)
    *(.plt)
    *(.gnu.warning)
    *(.glue_7t) *(.glue_7) *(.vfp11_veneer)

    *(.rodata .rodata.* .gnu.linkonce.r.*)

    *(.ARM.extab* .gnu.linkonce.armextab.*)
    *(.gcc_except_table)
    *(.eh_frame_hdr)
    *(.eh_frame)

    . = ALIGN(4);
    __FM_regions = .;
    LONG (0)
    LONG (__FM_region_init_ram)
    LONG (__FM_region_start_ram)
    LONG (__FM_region_init_size_ram)
    LONG (__FM_region_zero_size_ram)
  } > ROM

  /* .ARM.exidx is sorted, so has to go in its own output section.  */
  __exidx_start = .;
  .ARM.exidx :
  {
    *(.ARM.exidx* .gnu.linkonce.armexidx.*)
  } >ROM
  __exidx_end = .;
  .text.align :
  {
    . = ALIGN(4);
    _etext = .;
  } >ROM
  __FM_region_size_rom = LENGTH(ROM);
  __FM_region_num = 1;

  .data :
  {
    _sdata = .;
    __FM_region_start_ram = .;
    *(.FM.region-head.RAM)
    KEEP(*(.jcr))
    *(.got.plt) *(.got)
    *(.shdata)
    *(.data .data.* .gnu.linkonce.d.*)
    *(.RAM)
    . = ALIGN(4);
    _edata = .;
  } >RAM AT>ROM
  data_size = _edata - _sdata;
  .bss :
  {
    _sbss = .;
    *(.shbss)
    *(.bss .bss.* .gnu.linkonce.b.*)
    *(COMMON)
    *(.RAM.b)
    . = ALIGN(4);
    _ebss = .;
    _end = .;
    __end = .;
  } >RAM AT>ROM
  bss_size = _ebss - _sbss;
  
  PROVIDE ( end = _ebss );
  PROVIDE ( _end = _ebss );
  
  .heap :
  {
    . = ALIGN(4);
    . = . + __FM_heap_size;
  } >RAM
  .stack :
  {
    . = ALIGN(4);
    . = . + __FM_stack_size;
  } >RAM
  __FM_region_init_ram = LOADADDR (.data);
  __FM_region_init_size_ram = _edata - __FM_region_start_ram;
  __FM_region_zero_size_ram = _end - _edata;
  __FM_region_size_ram = LENGTH(RAM);
  __FM_region_num = 1;

  .stab 0 (NOLOAD) : { *(.stab) }
  .stabstr 0 (NOLOAD) : { *(.stabstr) }
  /* DWARF debug sections.
   * Symbols in the DWARF debugging sections are relative to the beginning
   * of the section so we begin them at 0.  */
  /* DWARF 1 */
  .debug          0 : { *(.debug) }
  .line           0 : { *(.line) }
  /* GNU DWARF 1 extensions */
  .debug_srcinfo  0 : { *(.debug_srcinfo) }
  .debug_sfnames  0 : { *(.debug_sfnames) }
  /* DWARF 1.1 and DWARF 2 */
  .debug_aranges  0 : { *(.debug_aranges) }
  .debug_pubnames 0 : { *(.debug_pubnames) }
  /* DWARF 2 */
  .debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
  .debug_abbrev   0 : { *(.debug_abbrev) }
  .debug_line     0 : { *(.debug_line) }
  .debug_frame    0 : { *(.debug_frame) }
  .debug_str      0 : { *(.debug_str) }
  .debug_loc      0 : { *(.debug_loc) }
  .debug_macinfo  0 : { *(.debug_macinfo) }
  /* SGI/MIPS DWARF 2 extensions */
  .debug_weaknames 0 : { *(.debug_weaknames) }
  .debug_funcnames 0 : { *(.debug_funcnames) }
  .debug_typenames 0 : { *(.debug_typenames) }
  .debug_varnames  0 : { *(.debug_varnames) }

  .note.gnu.arm.ident 0 : { KEEP (*(.note.gnu.arm.ident)) }
  .ARM.attributes 0 : { KEEP (*(.ARM.attributes)) }
  /DISCARD/ : { *(.note.GNU-stack) }
}
