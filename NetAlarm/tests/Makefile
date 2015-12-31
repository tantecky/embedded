APP_NAME := tests
CPP_FILES := $(wildcard *.cpp)
OBJ_FILES  :=	$(CPP_FILES:.cpp=.o)

INC_DIRS := -I./googletest-master/googletest/include 

LIBS_DIRS := -L./googletest-master/build/googlemock/gtest
LIBS := -lgtest -lpthread

CXX := g++
CXX_FLAGS := -Wall -Wextra -g -DNETALARM_TESTING
# LD_FLAGS := -Wl,--unresolved-symbols=ignore-in-shared-libs

.PHONY: clean depend

$(APP_NAME): $(OBJ_FILES)
	$(CXX) $(LIBS_DIRS) -o $(APP_NAME) $(OBJ_FILES) $(LIBS) $(LD_FLAGS)

%.o: %.cpp
	$(CXX) $(CXX_FLAGS) $(INC_DIRS) -c -o $@ $<

depend: .depend

.depend: $(CPP_FILES)
	@rm -f ./.depend
	@$(CXX) $(CXX_FLAGS) -MM $^ >> ./.depend

-include .depend

clean:
	rm -f tests
	rm -f *.o
	rm -f ./.depend
