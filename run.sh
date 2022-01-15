export PATH=$PATH:/usr/local/i386elfgcc/bin

nasm "Boot/boot.asm" -f bin -o "Binaries/boot.bin" -i Boot
nasm "Kernel/kernel_entry.asm" -f elf -o "Binaries/kernel_entry.o" -i intDef
i386-elf-gcc -ffreestanding -m32 -g -c "Kernel/kernel.cpp" -o "Binaries/kernel.o" 
nasm "Boot/zeroes.asm" -f bin -o "Binaries/zeroes.bin"

i386-elf-gcc -ffreestanding -m32 -g -c "intDef/idt.cpp" -o "Binaries/idt.o"
i386-elf-gcc -ffreestanding -m32 -g -c "intDef/isr.cpp" -o "Binaries/isr.o" -I intDef
i386-elf-gcc -ffreestanding -m32 -g -c "intDef/irq.cpp" -o "Binaries/irq.o" -I intDef

i386-elf-gcc -ffreestanding -m32 -g -c "Memory/mem.cpp" -o "Binaries/mem.o"


i386-elf-ld -o "Binaries/full_kernel.bin" -Ttext 0x1000 "Binaries/kernel_entry.o" "Binaries/kernel.o" "Binaries/idt.o" "Binaries/isr.o" "Binaries/irq.o" "Binaries/mem.o" --oformat binary

cat "Binaries/boot.bin" "Binaries/full_kernel.bin" "Binaries/zeroes.bin"  > "Binaries/OS.bin"

qemu-system-x86_64 -drive format=raw,file='Binaries/OS.bin',index=0,if=floppy,  -m 128M
