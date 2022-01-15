#include "../intDef/idt.h"
#include "../intDef/isr.h"
#include "../Memory/mem.h"
#include "../intDef/irq.h"



//void write_string( int colour, const char *string )
//{
//    volatile char *video = (volatile char*)0xB8000;
//    while( *string != 0 )
//    {
//        *video++ = *string++;
//        *video++ = colour;
//    }
//}

extern "C" void main(){
	write_string(1,"omer1");
	
	//int y=0;
	//int x= 3/y;
	idt_install();
	isrs_install();
	irq_install();

    return;
}