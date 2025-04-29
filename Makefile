.PHONY: all
.PHONY: build
.PHONY: build-arm
.PHONY: debug
.PHONY: debug-arm
.PHONY: tests
.PHONY: run-tests
.PHONY: run
.PHONY: run-dbg
.PHONY: clean

override CPPFILES := $(shell find  -L src/* -type f -name '*.cpp')
override OBJ := $(addprefix obj/,$(CPPFILES:.cpp=.cpp.o))

TARGET =  server
CC = g++
ARM_CC = arm-none-eabi-g++
LIBS = -lcrypto -lssl
CXXINCLUDE = include/
CXXFLAGS = -std=c++17
DEBUG_FLAGS =
OUTDIR = public/

all:build

run: build
	./$(TARGET)

run-dbg: debug
	./$(TARGET)_dbg

build: CXXFLAGS+=-O3
build: $(OBJ)
	$(CC) $(CXXFLAGS) -I $(CXXINCLUDE) -D RELEASE -c main.cpp -o main.cpp.o
	$(CC) -I $(CXXINCLUDE) $(OBJ) -D RELEASE main.cpp.o $(LDFLAGS) -o $(OUTDIR)$(TARGET) $(LIBS)

build-arm: $(OBJ)
	$(ARM_CC) $(CXXFLAGS) -I $(CXXINCLUDE) -g  -c main.cpp -o main.cpp.o
	$(ARM_CC) -I $(CXXINCLUDE) $(OBJ) main.cpp.o $(LDFLAGS) -o $(OUTDIR)$(TARGET) $(LIBS)

debug: CXXFLAGS+=-g -O0 -D DEBUG_FLAGS
debug: $(OBJ)
	$(CC) $(CXXFLAGS) -I $(CXXINCLUDE)  -g  -c main.cpp -o main.cpp.o
	$(CC) -I $(CXXINCLUDE)  $(OBJ) main.cpp.o -g  -o $(OUTDIR)$(TARGET)_dbg $(LIBS)

debug-arm: CXXFLAGS+=-g -O0 -D DEBUG_FLAGS
debug-arm: $(OBJ)
	$(ARM_CC) $(CXXFLAGS) -I $(CXXINCLUDE)  -g  -c main.cpp -o main.cpp.o
	$(ARM_CC) -I $(CXXINCLUDE)  $(OBJ) main.cpp.o -g  -o $(OUTDIR)$(TARGET)_dbg $(LIBS)

tests: CXXFLAGS+=-g -O0
tests: $(OBJ)
	$(CC)  -g $(CXXFLAGS) -I $(CXXINCLUDE) -c tests.cpp -o   tests.cpp.o
	$(CC)  -g -I $(CXXINCLUDE)  $(OBJ) tests.cpp.o -o tests $(LIBS) -lUnitTest++

run-tests: tests
	./tests

obj/%.cpp.o: %.cpp
	mkdir -p "$$(dirname $@)"
	$(CC) $(CXXFLAGS) -I  $(CXXINCLUDE) -c $< -o $@

clean:
	rm -rf obj
	rm -f $(OUTDIR)$(TARGET)
	rm -f $(OUTDIR)$(TARGET)_dbg
	rm -f tests
