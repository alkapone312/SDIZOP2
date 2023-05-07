CPP_FILES := $(wildcard **/*.cpp) $(wildcard *.cpp)
OBJECT_FILES := $(patsubst %.cpp,%.o,$(CPP_FILES))

all: $(OBJECT_FILES) archive

%.o: %.cpp
	$(COMPILER) -g -c $^ -I ../include

archive: # creates library named SDIZO linking all objects together
	find . -type f -name "*.o" | xargs $(ARCHIVE) rsc ../lib/libSDIZO.a

