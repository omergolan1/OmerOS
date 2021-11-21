#include "../Memory/mem.h"
#include "../kernel/idt.h"
#include "../kernel/isr.h"
#include "../kernel/irq.h"

extern "C" void main(){
    

	idt_install();
    *(char*)0xb8000 = 'O';
    return;
}
