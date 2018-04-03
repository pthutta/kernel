CC = gcc
CFLAGS = -ffreestanding -nostdlib -static -fno-stack-protector -m32 -fno-PIC -nostdinc
GRUB = $(HOME)/prog/grub/bin/
MKRESCUE = env PATH=$$PATH:$(GRUB) grub-mkrescue

boot.img: a.out
	mkdir -p _boot/boot/grub
	cp a.out _boot
	cp grub.cfg _boot/boot/grub/
	cp testmodule.txt _boot
	cp anothermodule.txt _boot
	$(MKRESCUE) -o $@ _boot
	rm -rf _boot

a.out: boot.S io.S paging.S kernel.c
	$(CC) -o $@ -T linkscript $(CFLAGS) $(LDFLAGS) -Iincludes/ boot.S io.S paging.S kernel.c memory.c serial.c pdclib-master/_build/libpdc.a -lgcc
LDFLAGS = -Wl,-melf_i386

test: boot.img
	qemu-system-i386 -serial stdio -cdrom boot.img

clean:
	rm -f boot.img a.out
