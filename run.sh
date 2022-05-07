export PATH=$PATH:/usr/local/i386elfgcc/bin

echo Boot:
nasm "Bootloader/boot.asm" -f bin -o "Binaries/boot.bin" -i Bootloader
nasm "Kernel/empty_end.asm" -f bin -o "Binaries/empty_end.bin"


nasm "Kernel/kernel_entry.asm" -f elf -o "Binaries/kernel_entry.o" -i Kernel
i386-elf-gcc -ffreestanding -m32 -g -c "Kernel/kernel.cpp" -o "Binaries/kernel.o" -I Kernel
nasm "Bootloader/zeroes.asm" -f bin -o "Binaries/zeroes.bin"

echo SHELL:
i386-elf-gcc -ffreestanding -m32 -g -c "Shell/shell.cpp" -o "Binaries/shell.o" -I Shell
i386-elf-gcc -ffreestanding -m32 -g -c "Shell/shellFunctions.cpp" -o "Binaries/shellFunctions.o" -I Shell

echo intDef
i386-elf-gcc -ffreestanding -m32 -g -c "intDef/idt.cpp" -o "Binaries/idt.o"
i386-elf-gcc -ffreestanding -m32 -g -c "intDef/isr.cpp" -o "Binaries/isr.o" -I intDef
i386-elf-gcc -ffreestanding -m32 -g -c "intDef/irq.cpp" -o "Binaries/irq.o" -I intDef
i386-elf-gcc -ffreestanding -m32 -g -c "intDef/timer.cpp" -o "Binaries/timer.o" -I intDef

i386-elf-gcc -ffreestanding -m32 -g -c "Memory/mem.cpp" -o "Binaries/mem.o"

echo Drivers:
i386-elf-gcc -ffreestanding -m32 -g -c "Drivers/port_io.cpp" -o "Binaries/port_io.o" -I Drivers
i386-elf-gcc -ffreestanding -m32 -g -c "Drivers/VGA_Text.cpp" -o "Binaries/VGA_Text.o" -I Drivers
i386-elf-gcc -ffreestanding -m32 -g -c "Drivers/Keyboard.cpp" -o "Binaries/Keyboard.o" -I Drivers
i386-elf-gcc -ffreestanding -m32 -g -c "Drivers/string.cpp" -o "Binaries/string.o" -I Utils
i386-elf-gcc -ffreestanding -m32 -g -c "Drivers/Conversions.cpp" -o "Binaries/Conversions.o" -I Drivers
i386-elf-gcc -ffreestanding -m32 -g -c "Drivers/CmdMode.cpp" -o "Binaries/CmdMode.o" -I Drivers
i386-elf-gcc -ffreestanding -m32 -g -c "Drivers/CodeMode.cpp" -o "Binaries/CodeMode.o" -I Drivers

i386-elf-ld -o "Binaries/full_kernel.bin" -Ttext 0x1000 "Binaries/kernel_entry.o" "Binaries/kernel.o" "Binaries/CmdMode.o" "Binaries/CodeMode.o" "Binaries/Keyboard.o" "Binaries/timer.o" "Binaries/Floppy.o" "Binaries/shellFunctions.o" "Binaries/shell.o" "Binaries/string.o" "Binaries/port_io.o" "Binaries/Conversions.o" "Binaries/VGA_Text.o" "Binaries/idt.o" "Binaries/isr.o" "Binaries/irq.o" "Binaries/mem.o" --oformat binary

cat "Binaries/boot.bin" "Binaries/full_kernel.bin" "Binaries/empty_end.bin"  > "Binaries/OS.bin"

qemu-system-x86_64 -drive format=raw,file="Binaries/OS.bin",index=0,if=floppy,  -m 128M
