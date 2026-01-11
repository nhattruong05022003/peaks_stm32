INCLUDE memory_regions.ld

ENTRY(Reset_Handler)

MEMORY
{
    FLASH(rx) :ORIGIN =ROM_START, LENGTH =ROM_LENGTH
    SRAM(rw) :ORIGIN =SRAM_START, LENGTH =SRAM_LENGTH
}

__max_heap_size = 0x400;    /*a symbol declaration. Not a variable !*/
__max_stack_size = 0x200;   /*a symbol declaration. Not a variable !*/

SECTIONS
{
    /* This section should include .text section of all input files */
    .text :
    {
        /* merge all .isr_vector section of all input files
        merge all .text section of all input files
        merge all .rodata section of all input files */
        KEEP(*(.exception_vector))
        KEEP(*(.irq_vector))
        *(.text)
        *(.text.*)
        *(.init)
        *(.fini)
        *(.rodata)
        *(.rodata.*)
        . = ALIGN(4); /*Align the address section (4 bytes)*/
        _etext = .; /* Store the updated location counter value into a symbol '_etext' */
    }> FLASH

    /* This section should include .data section of all input files */
    .data :
    {
        _sdata = .; /* Assign a value to a symbol '_sdata'. Location reset to start of VMA */
        /* here merge all .data section of all input files */
        *(.data)
        *(.data.*)
        . = ALIGN(4); /*Align the address section (4 bytes)*/
        _edata = .;
    }> SRAM  AT>  FLASH /* >(vma)AT>(lma) */

    _la_data = LOADADDR(.data); /* This is the physical address in FLASH */

    .bss :
    {
        _sbss = .;
        __bss_start__ = _sbss;
        *(.bss)
        *(.bss.*)
        . = ALIGN(4); /*Align the address section (4 bytes)*/
        _ebss = .;
        __bss_end__ = _ebss;
        . = ALIGN(4);
    }> SRAM

    .stack :
    {
        . = ALIGN(4);
        _sstack = .;
        *(.stack*)
        _estack = .;
        . = ALIGN(4);
        end = .;
    }> SRAM
}