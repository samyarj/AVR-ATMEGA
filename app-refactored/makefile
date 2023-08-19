# This Makefile allows you to compile projects
# for Atmel AVR microcontrollers on
# Linux or Unix, using the AVR-GCC tool.
# This Makefile supports C & C ++


# A microcontroller unit (MCU) is a small computer on a single integrated circuit.
# To compile for the ATmega324PA, we need to use the following MCU:
MCU=atmega324pa

PROJECTNAME=atemga 

# Source files
PRJSRC= main.cpp RobotManager.cpp
INC=-I ../library_refactored

LIBS= -l inf1900 -L ../lib 
OPTLEVEL=s  # s for size optimization

# Programmer ID  
AVRDUDE_PROGRAMMERID=usbasp  

# avr-gcc is a front end to the GNU Compiler Collection. 
# It translates C and C++ code into AVR instructions.CC=avr-gcc
CC=avr-gcc

OBJCOPY=avr-objcopy

# avrdude is a utility to download/upload/manipulate the ROM and EEPROM contents of AVR microcontrollers.
AVRDUDE=avrdude  
REMOVE=rm -f  # remove files when calling `make clean`
HEXFORMAT=ihex  # HEXFORMAT -- format for produced .hex files


# Flags for C compiler
CFLAGS=-I. -MMD $(INC) -g -mmcu=$(MCU) -O$(OPTLEVEL) \
	-fpack-struct -fshort-enums             \
	-funsigned-bitfields -funsigned-char    \
	-Wall -DF_CPU=8000000                                       

# Flags for C++ compiler
CXXFLAGS=-fno-exceptions     

# Linker for linking the libraries used
LDFLAGS=-Wl,-Map,$(TRG).map -mmcu=$(MCU)

# Default targets
TRG=$(PROJECTNAME).out
HEXROMTRG=$(PROJECTNAME).hex
HEXTRG=$(HEXROMTRG) $(PROJECTNAME).ee.hex


# different .c files from .cpp files
CFILES=$(filter %.c, $(PRJSRC))
CPPFILES=$(filter %.cpp, $(PRJSRC))

# list of object files
OBJDEPS=$(CFILES:.c=.o) \
	$(CPPFILES:.cpp=.o)

####### makefile commands ####### 

# Phony Targets
.PHONY: all install clean 
all: $(TRG) $(HEXROMTRG)
debug: CFLAGS+= -DDEBUG -g
debug: $(TRG) $(HEXROMTRG)

# target that depends on all the object files
$(TRG): $(OBJDEPS)
	$(CC) $(LDFLAGS) -o $(TRG) $(OBJDEPS) \
	-lm $(LIBS)

# from .c -> .o
%.o: %.c
	$(CC) $(CFLAGS) -c $<
# from .cpp -> .o
%.o: %.cpp
	$(CC) $(CFLAGS) $(CXXFLAGS) -c $<

# header dependencies verification 
-include *.d


# producing hex files from elf files
%.hex: %.out
	$(OBJCOPY) -j .text -j .data \
		-O $(HEXFORMAT) $< $@

# Make install allows you to compile the project and then
# write the program in flash memory in your
# microcontroller. It must be connected by USB cable 
install: $(HEXROMTRG)				
	$(AVRDUDE) -c $(AVRDUDE_PROGRAMMERID)   \
	-p $(MCU) -P -e -U flash:w:$(HEXROMTRG)

# Make clean allows you to erase all the files generated
# during compilation
clean:
	$(REMOVE) $(TRG) $(TRG).map $(OBJDEPS) $(HEXTRG) *.d

