/**
* @file   lpc2478_ram.ld
* @author fanghuaqi <578567190@qq.com>
* @date   Sun Mar 27 15:13:46 2011
* 
* @brief  
* 
* 
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
    
	 .vector :                                        /*collect all .vector sections that should go into SRAM*/
    {	
        *(.vector)                                    /*all .vector sections*/
    } > SRAM                                          /*put all the above into SRAM*/

	.text :                                           /*collect all .text sections that should go into SDRAM*/
    {
        __text = . ;                                  /*create a global symbol marking the start of the .text section*/
        *(.text)                                      /*all .text sections*/
    } > SRAM                                         /*put all the above into SDRAM*/
    _etext = .	;                                     /*define a global symbol marking the end of the .text section */
    PROVIDE (etext = .)	;                             /*define a symbol etext  only if it is referenced but not defined*/
    
   	.rodata :                                         /*collect all .rodata sections that should go into SDRAM*/ 
	{                                                           
		*(.rodata)                                    /*all .rodata sections*/              
		*(.rodata.*)                                  /*all .rodata.* sections*/ 
	} > SRAM                                         /*put all the above into SDRAM*/
    . = ALIGN(4);                                     /*advance location counter to the next 32-bit boundary */

    __idata_start = . ;                               /*define a global symbol marking the start of the .data section */
    .data   :  AT(__idata_start)                      /*collect all .data sections that should go into SDRAM and  LMA should be __idata_start*/ 
    {
        __data_start = . ;                            /*create a global symbol marking the start of the .data section*/  
        *(.data)                                      /*all .text sections*/           
    } > SRAM                                         /*put all the above into SDRAM*/
	. = ALIGN (4);                                    /*advance location counter to the next 32-bit boundary */
    __idata_end = __idata_start + SIZEOF(.data);      /*define a global symbol marking the end of the .data section */
    
    _edata  =  . ;                                    /*define a global symbol marking the end of the .data section */
    PROVIDE (edata = .);
    
    . = ALIGN(4);                                     /*advance location counter to the next 32-bit boundary */
    .bss       :                                      /*collect all .bss sections that should go into SDRAM*/           
    {          
      __bss_start = .	;                             /*define a global symbol marking the start of the .bss section */
      *(.bss)                                         /*all .bss sections*/ 
      *(COMMON)                                       /*all COMMON sections*/ 
	  __bss_end = .;                                  /*define a global symbol marking the end of the .bss section */
    } > SRAM                                         /*put all the above into SDRAM,it will be cleared in the startup code*/
    . = ALIGN(32 / 8);
     _end = .		;                                 /*define a global symbol marking the end of application RAM */
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
