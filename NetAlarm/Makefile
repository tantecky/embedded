LIB_NAME := lib.so
SRC_DIR := src
BUILD_DIR := build

CPP_FILES :=	$(foreach dir,$(SRC_DIR),$(notdir $(wildcard $(dir)/*.cpp)))
OBJ_FILES  :=	$(addprefix $(BUILD_DIR)/,$(CPP_FILES:.cpp=.o))

INC_DIRS := -I/home/tom/arduino-1.6.6/hardware/arduino/avr/cores/arduino \
	-I/home/tom/arduino-1.6.6/hardware/tools/avr/avr/include \
	-I/home/tom/arduino-1.6.6/hardware/arduino/avr/variants/standard

CXX := g++
CXX_FLAGS := -Wall -Wextra -g -D__AVR_ATmega328P__ -DF_CPU -D__OPTIMIZE__ \
	-Wno-attributes
VPATH := $(SRC_DIR)

.PHONY: build depend clean

build: $(BUILD_DIR)/$(LIB_NAME)

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(BUILD_DIR)
	@echo Compiling $<...
	$(CXX) $(CXX_FLAGS) $(INC_DIRS) -fpic -c -o $@ $<

$(BUILD_DIR)/lib.so: $(OBJ_FILES)
	$(CXX) -shared -o $(BUILD_DIR)/$(LIB_NAME) $(OBJ_FILES)

depend: .depend

.depend: $(CPP_FILES)
	@rm -f ./.depend
	@echo -n $(BUILD_DIR)/ >> ./.depend
	@$(CXX) $(CXX_FLAGS) -MM $^ >> ./.depend

-include .depend

clean:
	rm -rf $(BUILD_DIR)
	rm -f ./.depend

