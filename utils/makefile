#
# Makefile created based on auto-generated makefile from arduino IDE
#

#folders
PROJECT_ROOT=..
OUT_DIR	 = $(PROJECT_ROOT)/out
MCAL_DIR = $(PROJECT_ROOT)/mcal
DRV_DIR	 = $(PROJECT_ROOT)/drv
APP_DIR  = $(PROJECT_ROOT)/app
LIB_DIR  = $(PROJECT_ROOT)/lib
OS_DIR   = $(PROJECT_ROOT)/os

MCAL_MODULES = 	startup \
				config \
				isr \
				utils \
				adc \
				timer0
				
DRV_MODULES  = 	distance_sensor_drv \
				line_sensor_drv \
				motor_drv \
				i2c_drv \
				user_input_drv \
				uart_drv
APP_MODULES  = logger_swc \
			   state_machine_swc
LIB_MODULES  = avr_i2c/twi

#assemble list of source files
SRC_LIST += $(foreach module, $(MCAL_MODULES), $(wildcard $(MCAL_DIR)/$(module)/*.c))
SRC_LIST += $(foreach module, $(DRV_MODULES),  $(wildcard $(DRV_DIR)/$(module)/*.c))
SRC_LIST += $(foreach module, $(APP_MODULES),  $(wildcard $(APP_DIR)/$(module)/*.c))
SRC_LIST += $(foreach module, $(LIB_MODULES),  $(wildcard $(LIB_DIR)/$(module)/*.c))
SRC_LIST += $(wildcard $(OS_DIR)/*.c)

#assemble list of include directories
INCLUDE_DIR += $(foreach module, $(MCAL_MODULES), -I $(wildcard $(MCAL_DIR)/$(module)))
INCLUDE_DIR += $(foreach module, $(DRV_MODULES),  -I $(wildcard $(DRV_DIR)/$(module)))
INCLUDE_DIR += $(foreach module, $(APP_MODULES),  -I $(wildcard $(APP_DIR)/$(module)))
INCLUDE_DIR += $(foreach module, $(LIB_MODULES),  -I $(wildcard $(LIB_DIR)/$(module)))
INCLUDE_DIR += -I $(OS_DIR)

#compiler
CC=avr-gcc
MMCU=atmega328P
CFLAGS= -Wall -Os -std=c99 -mmcu=$(MMCU)
DEFINES = 	-D DUMMY_DEFINE_1 \

include ../mcal/config/global_config

#default rule
all: clean minisumo_mk4.elf minisumo_mk4.hex mem print_ok

#compile project Minisumo IV into .elf file
minisumo_mk4.elf: 
	$(info  ********************************************************************************************************* )
	$(info 	Building target: $@)
	$(info List of file to be build:)
	$(foreach file, $(SRC_LIST),  $(info $(file)))
	@$(CC) $(SRC_LIST) $(INCLUDE_DIR) $(CFLAGS) $(DEFINES) -o $(OUT_DIR)/$@
	$(info OK	Finished building target: $@)

#convert .elf file into flashable .hex
minisumo_mk4.hex: minisumo_mk4.elf
	$(info	Create Flash image (ihex format))
	@-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex $(OUT_DIR)/$< $(OUT_DIR)/$@
	$(info  OK	Finished building: $@)
	$(info   ********************************************************************************************************* )

#make clean
clean:
	@rm -f $(OUT_DIR)/minisumo_mk4.elf
	@rm -f $(OUT_DIR)/minisumo_mk4.hex
	$(info ### Clean finished! ###)
#memory analysis
mem: minisumo_mk4.elf 
	avr-size --format=berkeley --common --totals ../out/minisumo_mk4.elf

#just decoration
print_ok:
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


