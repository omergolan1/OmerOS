#include "../intDef/idt.h"
#include "../intDef/isr.h"
#include "../Memory/mem.h"
#include "../intDef/irq.h"
#include "../Drivers/VGA_Text.h"
#include "../Shell/shell.h"

void write_string( int colour, const char *string )
{
    volatile char *video = (volatile char*)0xb8000;
    *(char*)0xb8002='r';
    while( *string != 0 )
    {
        *video++ = *string++;
        *video++ = colour;
    }
}

extern "C" void main(){

	idt_install();
    isrs_install();
	irq_install();

    load_shell();
    return;
}
