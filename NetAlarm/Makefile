LIBRARY_NAME := NetAlarm
SRC_DIR := src
BUILD_DIR := build
INSTALL_DIR := ~/Arduino/libraries/$(LIBRARY_NAME)

CPP_FILES :=	$(subst $(SRC_DIR)/,,$(wildcard $(SRC_DIR)/*.cpp))
OBJ_FILES  :=	$(addprefix $(BUILD_DIR)/,$(CPP_FILES:.cpp=.o))

INC_DIRS := -I/home/tom/arduino-1.6.6/hardware/arduino/avr/cores/arduino \
	-I/home/tom/arduino-1.6.6/hardware/tools/avr/avr/include \
	-I/home/tom/arduino-1.6.6/hardware/arduino/avr/variants/standard

CXX := g++
CXX_FLAGS := -Wall -Wextra -g -D__AVR_ATmega328P__ -DF_CPU -D__OPTIMIZE__ \
	-Wno-attributes
VPATH := $(SRC_DIR)

.PHONY: build depend clean install

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
	@echo -n $(BUILD_DIR)/ >> ./.depend
	@$(CXX) $(CXX_FLAGS) -MM $^ >> ./.depend

-include .depend

install:
	rm -rf $(INSTALL_DIR)
	mkdir -p $(INSTALL_DIR)
	mkdir -p $(INSTALL_DIR)/examples/$(LIBRARY_NAME)
	cp $(SRC_DIR)/* $(INSTALL_DIR)
	cp -r examples/* $(INSTALL_DIR)/examples

clean:
	rm -rf $(BUILD_DIR)
	rm -f ./.depend

