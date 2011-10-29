# ============================================================
# USBHostLite Makefile
# Yecunkui
# 2011/03/23
# Version 1.1
# ============================================================

# Target related
TARGETNAME	=	lpc2478_toppers_style
TARGETDIR	= 	./sources
TOOLCHAINPREFIX	= arm-none-eabi#定义toolchain的前缀
# Tool definitions
CC	= $(TOOLCHAINPREFIX)-gcc
LD	= $(TOOLCHAINPREFIX)-ld 
AR	= $(TOOLCHAINPREFIX)-ar
AS	= $(TOOLCHAINPREFIX)-as
CP	= $(TOOLCHAINPREFIX)-objcopy
OD	= $(TOOLCHAINPREFIX)-objdump
RM	= rm

# Tool flags
CFLAGS  = -I./ -I$(TARGETDIR) -I$(TARGETDIR)/includes  -c -W -Wall -g -mcpu=arm7tdmi
ASFLAGS = -c -g -Wa,-ahlms=$*.lst,-mapcs-32 -mcpu=arm7tdmi
LFLAGS  = -v -nostartfiles --warn-common
CPFLAGS = -O ihex
ODFLAGS	= -x --syms


# set virtual path
vpath %.c $(SRCDIR)
vpath %.S $(SRCDIR)
vpath %.o $(SRCDIR)
# Add a link library path
LSEARCHGCC = "/home/fanghuaqi/CodeSourcery/Sourcery_G++_Lite/lib/gcc/arm-none-eabi/4.4.1"

# Linker script
LINKFILE	= lpc2478_ram.ld

# C source files
CSRCS = lpc2478_main.c\
		$(TARGETDIR)/common/lpc2478_cpatch.c $(TARGETDIR)/common/lpc2478_target.c $(TARGETDIR)/drivers/target_clk.c\
		$(TARGETDIR)/drivers/target_hw.c $(TARGETDIR)/drivers/target_irq.c $(TARGETDIR)/drivers/target_pwm.c\
		$(TARGETDIR)/drivers/target_rtc.c $(TARGETDIR)/drivers/target_timer.c $(TARGETDIR)/drivers/target_uart.c\
		$(TARGETDIR)/drivers/target_i2c.c $(TARGETDIR)/drivers/target_lcd.c $(TARGETDIR)/drivers/target_lcd_code.c
		
# Assembler source files				
ASRCS = start.S

# Object files				
COBJS	= $(CSRCS:.c=.o)
AOBJS 	= $(ASRCS:.S=.o)

# Default target	
all: $(TARGETNAME)

$(TARGETNAME): $(AOBJS) $(COBJS)	
	@ echo
	@ echo Linking: $@.elf
	$(CC) -T $(LINKFILE) $(LFLAGS) $^ -o $@.elf -Wl,-Map,$@.map,-lgcc,-L$(LSEARCHGCC)
	$(CP) $(CPFLAGS) $@.elf $@.hex
	$(OD) $(ODFLAGS) $@.elf > $@.dmp


# Assemble: create object files from assembler source files.
$(AOBJS) : %.o : %.S
	@echo
	@echo Assembling: $<
	$(CC) $(ASFLAGS) $< -o  $@

# dependency checking
depend: $(CSRCS)
	@echo "make depend"
	$(CC) $(CFLAGS) -MM $^ > .depend || rm -f .depend

# Target: clean project.
clean:
	@ echo
	@ echo Cleaning project:
	$(RM) -f *.hex *.elf *.o *.lst *.dmp *.map .depend *_flymake.c *_flymake.h *.c~ *.h~
	cd sources;$(RM) -f *.hex *.elf *.o *.lst *.dmp *.map .depend *_flymake.c *_flymake.h  *.c~ *.h~
	cd sources/drivers;$(RM) -f *.hex *.elf *.o *.lst *.dmp *.map .depend *_flymake.c *_flymake.h *.c~ *.h~
	cd sources/common;$(RM) -f *.hex *.elf *.o *.lst *.dmp *.map .depend *_flymake.c *_flymake.h *.c~ *.h~
	cd sources/includes;$(RM) -f *.hex *.elf *.o *.lst *.dmp *.map .depend *_flymake.c *_flymake.h *.c~ *.h~

# Listing of phony targets.
.PHONY : all clean

-include .depend
