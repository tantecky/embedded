CXX := g++
CXX_FLAGS := -Wall -Wno-sign-compare -g -std=gnu++11
CPP_FILES :=	main.cpp SensorReceiver.cpp AudioFile.cpp

build: clean main

clean:
	@rm -f main

main:
	$(CXX) $(CXX_FLAGS) -o main $(CPP_FILES)
