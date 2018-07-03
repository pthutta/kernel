CC = gcc
CFLAGS = -ffreestanding -nostdlib -static -fno-stack-protector -m32 -fno-PIC -nostdinc -g
GRUB = $(HOME)/prog/grub/bin/
MKRESCUE = env PATH=$$PATH:$(GRUB) grub-mkrescue

boot.img: a.out textSection.out dataSection.out
	mkdir -p _boot/boot/grub
	cp a.out _boot
	cp grub.cfg _boot/boot/grub/
	cp testmodule.txt _boot
	cp anothermodule.txt _boot
	cp textSection.out _boot
	cp dataSection.out _boot
	$(MKRESCUE) -o $@ _boot
	rm -rf _boot

hello.out: user/hello.c user/syscall.S pdclib-master-user/_build/libpdc.a
	$(CC) -o $@ -T user/linkscript $(CFLAGS) $(LDFLAGS) -Iincludes/ user/hello.c memory.c user/syscall.S paging.S pdclib-master-user/_build/libpdc.a -lgcc

textSection.out: hello.out
	objcopy --dump-section .text=$@ hello.out

dataSection.out: hello.out
	objcopy --dump-section .data=$@ hello.out

a.out: boot.S io.S  calls_setup.S paging.S kernel.c memory.c serial.c calls.c userland.c pdclib-master/_build/libpdc.a
	$(CC) -o $@ -T linkscript $(CFLAGS) $(LDFLAGS) -Iincludes/ boot.S io.S paging.S kernel.c memory.c serial.c calls.c calls_setup.S userland.c pdclib-master/_build/libpdc.a -lgcc
LDFLAGS = -Wl,-melf_i386

pdclib-master/_build/libpdc.a:
	mkdir pdclib-master/_build
	(cd pdclib-master/_build ; cmake .. ; $(MAKE))

test: boot.img
	qemu-system-i386 -serial stdio -cdrom boot.img

clean:
	rm -f boot.img a.out
	rm -rf pdclib-master/_build
