ifneq ($(KERNELRELEASE),)
	obj-m := helloworld.o
else
	KERNELDIR ?= /usr/src/$(shell ls /usr/src/ | sort | tail -n 1)/
	PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules clean
endif


