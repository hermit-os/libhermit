MAKE = make
NASM = nasm
NASMFLAGS = -fbin

default: all
	
all: smp_setup.hex

smp_setup.bin: smp_setup.asm
	$(NASM) $(NASMFLAGS) -o $@ $<

smp_setup.hex: smp_setup.bin
	hexdump -v -e '"0x" 1/1 "%02X" ", "' $< > $@

scc_setup.bin: scc_setup.asm
	$(NASM) $(NASMFLAGS) -o $@ $<

clean:
	$(RM) -rf *.o *~ *.bin *.obj *.hex

depend:
	$(CC) -MM $(CFLAGS) *.c > Makefile.dep

-include Makefile.dep
# DO NOT DELETE
