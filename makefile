#
# Makefile created based on auto-generated makefile from arduino IDE
#

#folders
INC_DIR=include
OUT_DIR=out
# LIB_DIR=lib
SRC_DIR=src

#compiler
CC=avr-gcc
MMCU=atmega8
CFLAGS=-I $(INC_DIR) -Wall -Os -std=c99

# [target]:[prerequisites]
#	[recipe]
# -c 		Generate object file (compile file without linking)
# -o <dest>	Put compilation output to <dest>
# $@		Target file
# $< 		First prerequisite - here %.c

#source files list
SRC_LIST =  $(SRC_DIR)/main.c \
			$(SRC_DIR)/serial_tx.c \
			$(SRC_DIR)/serial_rx.c \
			$(SRC_DIR)/serial_progmem.c \
			# $(SRC_DIR)/ICCM.c \
			# $(SRC_DIR)/distance_sensor.c \
			# $(SRC_DIR)/line_sensor.c \
			# $(SRC_DIR)/ADC.c \
			# $(SRC_DIR)/AI.c \

DEFINES = 	-D DUMMY_DEFINE_1 \
			-D DUMMY_DEFINE_2 \

#make all rule
all: minisumo_mk4.elf minisumo_mk4.hex mem
	@echo '					              ____'
	@echo '					            /____ `\'
	@echo '					           ||_  _`\ \'
	@echo '					     .-.   `|O, O  ||'
	@echo '					     | |    (/    -)\'
	@echo '					     | |    |`- ` |\`'
	@echo '					  __/  |    | _/  |'
	@echo '					 (___) \.  _.\__. `\___'
	@echo '					 (___)  )\/  \    _/  ~\.'
	@echo '					 (___) . \   `--  _   `\	'
	@echo '					  (__)-    ,/        (   |'
	@echo '					       `--~|         |   |'
	@echo '					           |         |   |'
	@echo '				******                             ******'
	@echo '				****  Finished building all targets  ****'
	@echo '				******                             ******'

#compile project Minisumo IV into .elf file
minisumo_mk4.elf: 
	@echo ' ********************************************************************************************************* '
	@echo 'Building target: $@.. '
	$(CC) $(SRC_LIST) $(CFLAGS) $(DEFINES) -mmcu=$(MMCU) -o $(OUT_DIR)/$@
	@echo 'Finished building target: $@'
	@echo ' ********************************************************************************************************* '
	@echo ' '

#convert .elf file into flashable .hex
minisumo_mk4.hex: minisumo_mk4.elf
	@echo ' ********************************************************************************************************* '
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex $(OUT_DIR)/$< $(OUT_DIR)/$@
	@echo 'Finished building: $@'
	@echo ' ********************************************************************************************************* '
	@echo ' '

#make clean
clean:
	@rm -f $(OUT_DIR)/minisumo_mk4.elf
	@rm -f $(OUT_DIR)/minisumo_mk4.hex
	@echo '### Clean finished! ###'
	@echo ' '

#memory analysis
mem: minisumo_mk4.elf 
	@echo ' ********************************************************************************************************* '
	avr-size --format=berkeley out/minisumo_mk4.elf


