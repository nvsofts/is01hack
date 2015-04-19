obj-m := modules_enabler.o

ROOTDIR  := ~/is01/kernel
PWD   := $(shell pwd)

default:
	$(MAKE) -C $(ROOTDIR) M=$(PWD) ARCH=arm CROSS_COMPILE=~/is01/prebuilt/linux-x86/toolchain/arm-eabi-4.2.1/bin/arm-eabi- modules

clean:
	rm -f *.o *.ko
