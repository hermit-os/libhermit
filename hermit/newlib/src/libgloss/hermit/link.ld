OUTPUT_FORMAT("elf64-x86-64")
STARTUP(crt0.o)
ENTRY(_start)
GROUP(-lc -lgloss)
SEARCH_DIR(.)
__DYNAMIC  =  0;
phys = 0x40200000;
PAGE_SIZE = 0x1000;

/*
 * Initalize some symbols to be zero so we can reference them in the
 * crt0 without core dumping. These functions are all optional, but
 * we do this so we can have our crt0 always use them if they exist. 
 * This is so BSPs work better when using the crt0 installed with gcc.
 * We have to initalize them twice, so we multiple object file
 * formats, as some prepend an underscore.
 */
PROVIDE (hardware_init_hook = 0);
PROVIDE (software_init_hook = 0);
PROVIDE (__mem_start = phys);
PROVIDE (___mem_start = phys);
SECTIONS
{	
 .text phys : AT(phys) {
     _ftext = . ;
    *(.init)
     eprol  =  .;
    *(.text)
    PROVIDE (__runtime_reloc_start = .);
    *(.rel.sdata)
    PROVIDE (__runtime_reloc_stop = .);
    *(.fini)
    . = ALIGN(4);
     __CTOR_LIST__ = .;
    CONSTRUCTORS
    LONG(-1)
    *(.ctors)
    LONG(0)
    __CTOR_END__ = .;
    __DTOR_LIST__ = .;
    LONG(-1)
    *(.dtors)
     LONG(0)
    __DTOR_END__ = .;
    PROVIDE(_etext  =  .);
    PROVIDE(__etext  =  .);
  }
  . = ALIGN(PAGE_SIZE);
  .rdata : {
    *(.rdata)
  }
  .rodata : {
    *(.rodata)
    *(.rodata.*)
  }
  .eh_frame :
  {
    PROVIDE (__EH_FRAME_BEGIN__ = .);
    *(.eh_frame)
    PROVIDE (__EH_FRAME_END__ = .);
  }
  _fdata = ALIGN(16);
  . = ALIGN(PAGE_SIZE);
  .data : {
    *(.data)
    *(.gcc_except_table)
    *(.gcc_exc)
  }
  . = ALIGN(8);
  _gp = . + 0x8000;
  __global = . + 0x8000;
  .lit8 : {
    *(.lit8)
  }
  .lit4 : {
    *(.lit4)
  }
  .sdata : {
    *(.sdata)
  }
  . = ALIGN(4);
   PROVIDE(_edata  =  .);
   PROVIDE(__edata  =  .);
   fbss = .;
   _fbss = .;
  .sbss : {
    PROVIDE(__bss_start = .);
    *(.sbss)
    *(.scommon)
  }
  .bss : {
    *(.bss)
    *(COMMON)
    PROVIDE(__bss_end = .);
  }
  PROVIDE(_end = .);
  PROVIDE(__end = .);
}
