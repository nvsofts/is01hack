ifdef TOPDIR

obj-m += own.o

else

KERNEL_DIR := ~/is01/kernel
CROSS_COMPILE := ~/is01/prebuilt/linux-x86/toolchain/arm-eabi-4.2.1/bin/arm-eabi-
CROSS_COMPILE_NDK := /opt/android-ndk-r4b/build/prebuilt/linux-x86/arm-eabi-4.2.1/bin/arm-eabi-

ANDROID_CFLAGS := -mandroid --sysroot=/opt/android-ndk-r4b/build/platforms/android-4/arch-arm
LDFLAGS := -static -Wl,-T,armelf.x

.c.o: 
	$(CROSS_COMPILE_NDK)gcc $(ANDROID_CFLAGS) -c $<

all: default exploit prepare

default:
	$(MAKE) -C $(KERNEL_DIR) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) KBUILD_VERBOSE=1 M=$(PWD) modules

exploit: exploit.o own.o
	$(CROSS_COMPILE_NDK)gcc $(ANDROID_CFLAGS) $(LDFLAGS) -o $@ $^
	$(CROSS_COMPILE_NDK)readelf -S $@ | grep null
	$(CROSS_COMPILE_NDK)readelf -d $@
	$(CROSS_COMPILE_NDK)strip $@

prepare: prepare.o
	$(CROSS_COMPILE_NDK)gcc $(ANDROID_CFLAGS) $(LDFLAGS) -o $@ $^
	$(CROSS_COMPILE_NDK)strip $@

clean:
	rm -f exploit prepare *.ko *.o .*.cmd *.mod.c Module.symvers modules.order

endif
