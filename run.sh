export PATH=$PATH:/usr/local/i386elfgcc/bin

#boot
nasm "boot/boot.asm" -f bin -o "bin/boot.bin" -i boot
nasm "boot/zeroes.asm" -f bin -o "bin/zeroes.bin"


#kernel

i386-elf-gcc -ffreestanding -m32 -g -c "kernel/kernel.cpp" -o "bin/kernel.o" -I kernel
nasm "kernel/kernel_entry.asm" -f elf -o "bin/kernel_entry.o" -i kernel
i386-elf-gcc -ffreestanding -m32 -g -c "kernel/idt.cpp" -o "bin/idt.o"
i386-elf-gcc -ffreestanding -m32 -g -c "kernel/isr.cpp" -o "bin/isr.o" -I Kernel
i386-elf-gcc -ffreestanding -m32 -g -c "kernel/irq.cpp" -o "bin/irq.o" -I Kernel

#mem
i386-elf-gcc -ffreestanding -m32 -g -c "Memory/mem.cpp" -o "bin/mem.o"

#linker
i386-elf-ld -o "bin/full_kernel.bin" -Ttext 0x1000   "bin/mem.o" "bin/idt.o" "bin/irq.o" "bin/isr.o" "bin/kernel.o" "bin/kernel_entry.o"  --oformat binary

cat "bin/boot.bin" "bin/full_kernel.bin" "bin/zeroes.bin"  > "bin/OS.bin"

#qemu-system-x86_64 -drive format=raw,file="bin/OS.bin",index=0,if=floppy,  -m 128M
