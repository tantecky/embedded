PROJECT := NetAlarm
LIBRARY_NAME := libnetalarm
SRC_DIR := src
BUILD_DIR := build
INSTALL_DIR := ~/Arduino/libraries/$(PROJECT)
MAJOR_VERSION := $(shell grep -m 1 MAJOR_VERSION $(SRC_DIR)/NetAlarm.h \
	| grep -Eo '[0-9]+')
MINOR_VERSION := $(shell grep -m 1 MINOR_VERSION $(SRC_DIR)/NetAlarm.h \
	| grep -Eo '[0-9]+')

ARCHIVE := $(PROJECT)-$(MAJOR_VERSION).$(MINOR_VERSION).zip

CPP_FILES :=	$(subst $(SRC_DIR)/,,$(wildcard $(SRC_DIR)/*.cpp))
OBJ_FILES  :=	$(addprefix $(BUILD_DIR)/,$(CPP_FILES:.cpp=.o))

INC_DIRS := -I/home/tom/arduino-ide/hardware/arduino/avr/cores/arduino \
	-I/home/tom/arduino-ide/hardware/tools/avr/avr/include \
	-I/home/tom/arduino-ide/hardware/arduino/avr/variants/standard \
	-I/home/tom/arduino-ide/libraries/Ethernet/src \
	-I/home/tom/Arduino/libraries/rc-switch-2.52 \
	-I/home/tom/arduino-ide/hardware/arduino/avr/libraries/SPI

CXX := g++
CXX_FLAGS := -Wall -g -D__AVR_ATmega328P__ -DF_CPU -D__OPTIMIZE__ \
	-Wno-attributes -DARDUINO=100
VPATH := $(SRC_DIR)

.PHONY: build depend clean install tests pack

build: $(BUILD_DIR)/$(LIBRARY_NAME).so

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(BUILD_DIR)
	@echo Compiling $<...
	$(CXX) $(CXX_FLAGS) $(INC_DIRS) -fpic -c -o $@ $<

$(BUILD_DIR)/$(LIBRARY_NAME).so: $(OBJ_FILES)
	$(CXX) -shared -o $(BUILD_DIR)/$(LIBRARY_NAME).so $(OBJ_FILES)

depend: .depend

.depend: $(CPP_FILES)
	@rm -f ./.depend
	@$(CXX) $(CXX_FLAGS) -MM $^ >> ./.depend
	@sed -i 's/^\(.*:\)/build\/\1/g' .depend

-include .depend

install: build
	rm -rf $(INSTALL_DIR)
	mkdir -p $(INSTALL_DIR)
	cp $(SRC_DIR)/* $(INSTALL_DIR)
	cp -r examples $(INSTALL_DIR)

tests: build
	@$(MAKE) -C tests

pack: tests install
	@rm -f *.zip
	@rm -rf $(PROJECT)
	@cp -r $(INSTALL_DIR) .
	zip -r $(ARCHIVE) $(PROJECT)
	@rm -rf $(PROJECT)

clean:
	@$(MAKE) -C tests clean
	rm -rf $(BUILD_DIR)
	rm -f ./.depend

