/*
 *  @(#) $Id: lpc2478_ram.ld renwei $
 *  if you want to run it in sdram
 *  don't forget to init the sdram
 */
MEMORY
{	
	SRAM		: ORIGIN = 0x40000000, LENGTH  = 0x10000	/* 64KB */
    SDRAM  		: ORIGIN = 0xA0000000, LENGTH  = 0x4000000 	/*  64Mbyte */
}

OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm","elf32-littlearm") 
OUTPUT_ARCH(arm)

PROVIDE(hardware_init_hook = 0);
PROVIDE(software_init_hook = 0);
PROVIDE(software_term_hook = 0);
/*STARTUP(start.o)*/

SECTIONS
{
    
	 .vector :
    {	
        *(.vector)
    } > SRAM

	.text :
    {
        __text = . ; 	
      /*  *(.vector) */
        *(.text)

    } > SDRAM
    _etext = .	;
    PROVIDE (etext = .)	;
   	 .rodata : 
	 { 
		*(.rodata) 
		*(.rodata.*) 
	} > SDRAM 
    . = ALIGN(4);
    __idata_start = . ;
    .data   :  AT(__idata_start) 
    {
        __data_start = . ;
        *(.data)
    } > SDRAM 
	. = ALIGN (4);
    __idata_end = __idata_start + SIZEOF(.data);
    _edata  =  . ;
    PROVIDE (edata = .);
    . = ALIGN(4);
    .bss       :
    {
      __bss_start = .	;
      *(.bss)
      *(COMMON)
	   __bss_end = .;
    } > SDRAM
   . = ALIGN(32 / 8);
     _end = .		;
    PROVIDE (end = .)	;
    .comment 0 : { *(.comment) }	

  /* DWARF debug sections.
     Symbols in the DWARF debugging sections are relative to 
     the beginning of the section so we begin them at 0.  */

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
  .debug_info     0 : { *(.debug_info) }
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
}
