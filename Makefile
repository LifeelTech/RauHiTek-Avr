#Parameter for avrdude port
PORT =
DEBUG =

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
			-I $(PLATFORMDIR)/../util \
			-I thermistor \
			-I humidity \
			-I brightness \
			-I $(PLATFORMDIR)/..

#Define source code
CSOURCES = thermistor/thermistor.c \
			humidity/humidity.c \
			brightness/brightness.c
CXXSOURCES = app/main.cpp

LIBC = avr-lib.lib
LIBCXX = avr-libxx.lib
LIBCSRCS = $(LIBDIR)/wiring.c \
			$(LIBDIR)/wiring_digital.c \
			$(LIBDIR)/wiring_analog.c \
			$(LIBDIR)/WInterrupts.c \
			$(LIBDIR)/hooks.c
ifeq ($(DEBUG),1)
LIBCXXSRCS = $(LIBDIR)/HardwareSerial.cpp \
			$(LIBDIR)/HardwareSerial0.cpp \
			$(LIBDIR)/CDC.cpp
LIBCXXOBJS = $(subst .cpp,.o,$(LIBCXXSRCS))
endif
LIBCOBJS = $(subst .c,.o,$(LIBCSRCS))
COBJS = $(subst .c,.o,$(CSOURCES))
CXXOBJS = $(subst .cpp,.o,$(CXXSOURCES))

#Define preprocesor
CDEFS = -D$(MCU) -DF_CPU=16000000UL -D__AVR_ATmega328P__
COPTIMIZE = -Os -funsigned-char -funsigned-bitfields -fno-inline-small-functions
#Define compiler options
CFLAGS = -mmcu=$(MCU) -g -Wall -std=c99 $(COPTIMIZE) $(CDEFS) $(CINCLUDES)
ifeq ($(DEBUG),1)
CXXFLAGS = -mmcu=$(MCU) -x c++ -g -Wall $(COPTIMIZE) $(CDEFS) $(CINCLUDES)
CFLAGS += -DDEBUG_MODE 
endif
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
AVRDUDE_WRITE_FLASH = -U flash:w:$(TARGET).hex
AVRDUDE_PORT = $(PORT)

# Config file location
AVRDUDE_CFG_LOCATION = lib/hardware/tools/avr/etc/avrdude.conf

AVRDUDE_FLAGS = -p $(MCU_AVRDUDE) -F -P $(AVRDUDE_PORT) -c $(AVRDUDE_PROGRAMMER) -C $(AVRDUDE_CFG_LOCATION) -b 115200

#Build process
all: $(LIBC) $(LIBCXX) $(TARGET).$(EXTENSION) hex

$(TARGET).$(EXTENSION): $(COBJS) $(CXXOBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBC) $(LIBCXX)

$(LIBC): $(LIBCOBJS)
	$(AR) $(ARFLAGS) $@ $^
$(LIBCXX): $(LIBCXXOBJS)
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

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $(@:.o=.cpp)

$(LIBCOBJS): $(LIBCSRCS)
	$(CC) $(CFLAGS) -c -o $@ $(@:.o=.c)

$(LIBCXXOBJS): $(LIBCXXSRCS)
	$(CC) $(CXXFLAGS) -c -o $@ $(@:.o=.cpp)
