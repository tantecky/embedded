APP_NAME := tests
CPP_FILES := $(wildcard *.cpp)
OBJ_FILES  :=	$(CPP_FILES:.cpp=.o)

INC_DIRS := -I./googletest-master/googletest/include \
	-I../src

LIBS_DIRS := -L./googletest-master/build/googlemock/gtest \
	-L../build
LIBS := -lgtest -lpthread -lnetalarm

CXX := g++
CXX_FLAGS := -Wall -Wextra -g -DNETALARM_TESTING

.PHONY: clean

$(APP_NAME): $(OBJ_FILES)
	$(CXX) $(LIBS_DIRS) -o $(APP_NAME) $(OBJ_FILES) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXX_FLAGS) $(INC_DIRS) -c -o $@ $<

clean:
	rm -f tests
	rm -f *.o
