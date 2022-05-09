/*********************
* TEXT MODE: 0xB8000 *
* GR.  MODE: 0xA000  *
*********************/

//IMPLEMENT STACK SMASHING PROTECTOR!!!!

#include "../Drivers/Typedefs.h"
#include "../Drivers/VGA_Text.h"
#include "../Drivers/Conversions.h"
#include "../Drivers/string.h"
#include "../Memory/mem.h"
#include "../intDef/idt.h"
#include "../intDef/isr.h"
#include "../intDef/irq.h"
#include "../intDef/timer.h"
#include "../Drivers/Keyboard.h"
#include "../Shell/shell.h"

int curMode;					        // Modes:	1: CMD, 2: code, 0: dummy text, 10: shell


extern const unsigned short MemSize;    // Approximate value of extended memory (under 4 GB)

extern "C" void main(){
	//asm volatile("1: jmp 1b");		// "entry breakpoint" (debug)
	
	
	idt_install();
	isrs_install();
	irq_install();
	asm volatile ("sti");
	timer_install();
	kb_install();
    initializeMem();
    
    load_shell();

    
	return;
}



