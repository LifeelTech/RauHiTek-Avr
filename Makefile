#Define general target
MCU = atmega328p
MCU_AVRDUDE = atmega328p
TARGETNAME = Product
EXTENSION = elf
FORMAT = ihex
TARGET = $(TARGETNAME).$(EXTENSION)

#Define tool chain
CC = avr-gcc
AR = avr-ar
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

#Define directory
AVRDIR = lib/hardware/arduino/avr
LIBDIR = $(AVRDIR)/cores/arduino
PLATFORMDIR = lib/hardware/tools/avr/avr/include/avr
ADEFS =
CINCLUDES = -I $(LIBDIR) \
			-I $(AVRDIR)/variants/standard \
			-I $(PLATFORMDIR) \
			-I $(PLATFORMDIR)/../util
			
			
#Define source code
CSOURCES = app/main.c \
			thermistor/thermistor.c \
			humidity/humidity.c \
			brightness/brightness.c
LIB = avr-lib.lib
LIBCSRCS = $(LIBDIR)/wiring.c \
			$(LIBDIR)/wiring_digital.c \
			$(LIBDIR)/WInterrupts.c \
			$(LIBDIR)/hooks.c

LIBCOBJS = $(subst .c,.o,$(LIBCSRCS))
COBJS = $(subst .c,.o,$(CSOURCES))

#Define preprocesor
CDEFS = -D$(MCU) -DF_CPU=16000000UL -D__AVR_ATmega328P__
COPTIMIZE = -Os -funsigned-char -funsigned-bitfields -fno-inline-small-functions

#Define compiler options
CFLAGS = -mmcu=$(MCU) -g -Wall -std=c99 $(COPTIMIZE) $(CDEFS) $(CINCLUDES)

LDFLAGS = -Wl,-Map,$(TARGET).map
ARFLAGS = rcs

#---------------- Programming Options (avrdude) ----------------
# Fuse settings for Arduino Uno DFU bootloader project
AVRDUDE_FUSES = -U efuse:w:0xF4:m -U hfuse:w:0xD9:m -U lfuse:w:0xFF:m 

# Lock settings for Arduino Uno DFU bootloader project
AVRDUDE_LOCK = -U lock:w:0x0F:m

# Programming hardware
AVRDUDE_PROGRAMMER = arduino

# com1 = serial port. Use lpt1 to connect to parallel port.
AVRDUDE_PORT = com4
AVRDUDE_WRITE_FLASH = -U flash:w:$(TARGET).hex

# Config file location
AVRDUDE_CFG_LOCATION = lib/hardware/tools/avr/etc/avrdude.conf

AVRDUDE_FLAGS = -p $(MCU_AVRDUDE) -F -P $(AVRDUDE_PORT) -c $(AVRDUDE_PROGRAMMER) -C $(AVRDUDE_CFG_LOCATION) -b 115200

#Build process
all: $(LIB) $(TARGET).$(EXTENSION) hex

$(TARGET).$(EXTENSION): $(COBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIB)

$(LIB): $(LIBCOBJS)
	$(AR) $(ARFLAGS) $@ $^

program: $(TARGET).hex $(TARGET).eep
	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_WRITE_FLASH) $(AVRDUDE_WRITE_EEPROM)
clean:
	rm -rf *.s *.hex *.elf *.map *.eep *.lib
	rm -rf $(COBJS) $(LIBCOBJS)

hex:  $(TARGET).hex

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

%.eep: %.elf
	-$(OBJCOPY) -j .eeprom --set-section-flags=.eeprom="alloc,load" \
	--change-section-lma .eeprom=0 --no-change-warnings -O $(FORMAT) $< $@ || exit 0