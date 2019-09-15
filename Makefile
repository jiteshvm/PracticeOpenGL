EXE = ./bin/PracticeOpenGL
CXX = /usr/bin/clang++
ARCH = -arch x86_64
SOURCES := $(wildcard include/*/*.c) $(wildcard src/*.c) $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
HEADERS := $(wildcard include/*/*.h) $(wildcard src/*.h) $(wildcard src/*.h) $(wildcard src/*/*.h)
OBJECTS := $(SOURCES:.cpp=.o)

INCLUDES +=	-Iinclude/
CFLAGS += $(ARCH) -Wall -O3 -std=c++11

CFLAGS += $(shell pkg-config --cflags glfw3)
LDFLAGS += $(shell pkg-config --libs glfw3)

%.o: %.cpp
	@echo $@
	$(CXX) $(CFLAGS) $(INCLUDES) -g -c $^ -o $@

all: $(EXE)

$(EXE): $(OBJECTS) $(HEADERS)
	$(CXX) $(CFLAGS) $(INCLUDES) $(OBJECTS) $(LDFLAGS) -o $@

clean:
	@rm -rvf $(EXE) src/*.o src/*/*.o include/*/*.o *.dSYM