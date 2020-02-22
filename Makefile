# type make TARGET=test for using test/main.cpp instead default input point path
# you may see default value in " TARGET " variable
# use " se456es " with ctrl + F for fast searc it

# ------------------------------------------------------------------------------------
.PHONY: test
.PHONY: clean
.PHONY: cleanall
.PHONY: all

# compiler 
CC = g++

# list of used modules
LIBS = -linterpreter -lmemory -lregisters -lmyterm

# compiler flags
CFLAGS := -Wall -g

# name and directory of yor project
PROJ := project.cpp
PROJDIR = project/

# mutable variable for different compile targets
# se456es
TARGET ?= test

# name and directory of tests files
TEST := test.cpp
TESTDIR = test/

# include and module destination flags
# and him destinations 
LIBDIR = libs
INCDIR = include

INCLUDE_FLAG = -I $(INCDIR)
LIBS_FLAG = -L $(LIBDIR)

# necessary flag for compiling 
# do not touch!!!
DEPFLAGS := -MP -MMD 
DEPDIR = dep/

# directoryes
OBJDIR = build/
BINDIR = bin/
SRCDIR = src/

# directory of modules sourses
MODDIR = $(SRCDIR)modules/

# aoutosearch of sources files
SRC_FILES = $(wildcard $(SRCDIR)*.cpp) $(TARGET)/main.cpp

# autogen of ".o" file dependenses
OBJ_FILES = $(patsubst $(SRCDIR)%.cpp,$(OBJDIR)%.o,$(SRC_FILES))

# autogen of ".d" file dependenses (DEPDIR)
DEP_FILES = $(wildcard $(DEPDIR)*.d)

# destination of executeable file
EXECUTABLE = $(BINDIR)main

all:clrBin dirs libgen $(EXECUTABLE)

# remove old exec file
clrBin:
	rm -rf bin/main

# now its not autoconfigurable dependece
libgen:
	cd $(MODDIR)/memory && make
	cd $(MODDIR)/interpreter && make
	cd $(MODDIR)/registers && make
	cd $(MODDIR)/myterm && make

$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ $(INCLUDE_FLAG) $(LIBS_FLAG) $(LIBS) -o $@
 
$(OBJDIR)%.o : $(SRCDIR)%.cpp
	$(CC) $(CFLAGS) $(DEPFLAGS) $(INCLUDE_FLAG) $(LIBS_FLAG) $(LIBS) -c -o $@ $< 
	mv -f $(OBJDIR)$*.d $(DEPDIR)$*.d

dirs:
	mkdir -p $(OBJDIR) $(BINDIR) $(DEPDIR) $(LIBDIR)
		
clean:
	rm -f $(BINDIR)* $(OBJDIR)*.o $(DEPDIR)*.d

cleanall:
	rm -R $(OBJDIR) $(BINDIR) $(DEPDIR) $(LIBDIR)

include $(DEP_FILES)