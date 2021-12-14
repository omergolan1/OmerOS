#include "../Memory/mem.h"
#include "../kernel/idt.h"
#include "../kernel/isr.h"
#include "../kernel/irq.h"

#define VIDEO_MEMORY		(char*)0xB8000

extern "C" void main(){
    

    idt_install();
    *VIDEO_MEMORY = 'O';
    return;
}
