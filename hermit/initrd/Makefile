FAKEROOT=fakeroot

# Prettify output
V = 0
ifeq ($V,0)
	Q = @
	P = > /dev/null
endif

default: all
	
all: initrd.cpio
	

initrd.cpio:
	$Q$(FAKEROOT) ./initrd.sh

clean:
	@echo Cleaning initrd
	$Q$(RM) initrd.cpio

veryclean: clean
	$Q$(RM) -r busybox-*
