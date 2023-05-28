all: deps main clean

INCLUDE_DIR = include
LIB_DIR = lib
USE_LIBRARIES = -lSDIZO 

#DEFAULT COMPILE
# COMPILER = g++
# ARCHIVE = ar

#CROSS COMPILE FOR WINDOWS
COMPILER = x86_64-w64-mingw32-g++ -static-libgcc -static-libstdc++
ARCHIVE = x86_64-w64-mingw32-ar
export

deps: # executes makefile from src to build dependencies
	$(MAKE) -C src/

main: main.o # links object file with libraries and output executable
	$(COMPILER) -g main.o -O0 -L$(LIB_DIR) $(USE_LIBRARIES) -o bin/main

main.o: main.cpp # compiles main.cpp with include and outputs object file
	$(COMPILER) -g -c main.cpp -O0 -I $(INCLUDE_DIR) -o main.o

clean: # deletes all *.o file in subfolders
	find . -type f -name "*.o" | xargs rm