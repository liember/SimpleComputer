PROJECT_LIBS = -lregisters
OTHER_LIBS =

CC = g++

CFLAGS = -Wall
DEPFLAGS = -MP -MMD

INCLUDE_FLAG = -I ../../include
LIBS_FLAG = -L ../../libs

DEPDIR = dep/
OBJDIR = build/
SRCDIR = ./

SRC_FILES := $(wildcard $(SRCDIR)*.cpp)
OBJ_FILES = $(SRC_FILES:.cpp=.o)

OBJ_FILES := $(patsubst $(SRCDIR)%.cpp,$(OBJDIR)%.o,$(SRC_FILES))
DEP_FILES := $(wildcard $(DEPDIR)*.d)

MKFILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))
CURRENT_DIR := $(notdir $(patsubst %/,%,$(dir $(MKFILE_PATH))))

all: dirs $(OBJ_FILES)
	ar rvs ../../libs/lib$(CURRENT_DIR).a $(OBJ_FILES)

$(OBJDIR)%.o : $(SRCDIR)%.cpp
	$(CC) $(CFLAGS) $(DEPFLAGS) $(INCLUDE_FLAG) $(LIBS) -c -o $@ $< 
	mv -f $(OBJDIR)$*.d $(DEPDIR)$*.d

dirs:
	mkdir -p $(OBJDIR) $(DEPDIR)

.PHONY: clean
clean:
	rm -rf $(OBJDIR)*.o $(DEPDIR)*.d 

include $(DEP_FILES)