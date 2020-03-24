# type make TARGET=test for using test/main.cpp instead default input point path
# you may see default value in " TARGET " variable
# use " se456es " with ctrl + F for fast searc it

# ------------------------------------------------------------------------------------
# compiler 
CC = g++
# compiler flags
CFLAGS := -Wall -g

# other modules
# just libraries that project not contain
C_MODULES = 
# list of used modules
MODULES = myterm interpreter memory mybigchars registers
LIBS = $(addprefix -l,$(MODULES)) $(addprefix -l,$(C_MODULES))

# name and directory of yor project
PROJ := project.cpp
PROJDIR = project/

# mutable variable for different compile targets
# se456es
TARGET ?= test

# name and directory of tests files
TEST := test.cpp
TESTDIR = test/

# directory of modules sourses
MODDIR = $(SRCDIR)modules/

# include and module destination flags
# and him destinations 
LIBDIR = libs
INCDIR = include

# directoryes
OBJDIR = build/
BINDIR = bin/
SRCDIR = src/

# necessary flag for compiling 
# do not touch!!!
DEPFLAGS := -MP -MMD 
DEPDIR = dep/


############################################ END OF CONFIGUREABLE VARIABLES #################################################


# add include flag to include paths
INCLUDE_FLAG = -I $(INCDIR)
LIBS_FLAG = -L $(LIBDIR)

# aoutosearch of sources files
SRC_FILES = $(wildcard $(SRCDIR)*.cpp) $(TARGET)/main.cpp

# autogen of ".o" file dependenses
OBJ_FILES = $(patsubst $(SRCDIR)%.cpp,$(OBJDIR)%.o,$(SRC_FILES))

# autogen of ".d" file dependenses (DEPDIR)
DEP_FILES = $(wildcard $(DEPDIR)*.d)

# generate modules dependenses
MOD_MAKES := $(addsuffix .lol,$(addprefix $(MODDIR),$(MODULES)))

# destination of executeable file
EXECUTABLE = $(BINDIR)main

all:clean dirs $(MOD_MAKES) $(EXECUTABLE)
	@echo
	@echo [!][!][!][!][!] COMPILATION SUCSESS [!][!][!][!][!]
	@echo
	
# now its not autoconfigurable dependece
$(MODDIR)%:
	echo lol
	make -C $(basename $@)

# link object file with modules and compile
$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ $(INCLUDE_FLAG) $(LIBS_FLAG) $(LIBS) -o $@
 
 # make object files from files in " SRCDIR " directory
$(OBJDIR)%.o : $(SRCDIR)%.cpp
	$(CC) $(CFLAGS) $(DEPFLAGS) $(INCLUDE_FLAG) -c -o $@ $< 
	mv -f $(OBJDIR)$*.d $(DEPDIR)$*.d

# make project's dirs
dirs:
	mkdir -p $(OBJDIR) $(BINDIR) $(DEPDIR) $(LIBDIR)

# remove unnecessary content of project's dirs	
clean:
	rm -f $(BINDIR)* $(OBJDIR)*.o $(DEPDIR)*.d

# remove project's dirs (don't remove " SRCDIR ")
cleanall:
	rm -R $(OBJDIR) $(BINDIR) $(DEPDIR) $(LIBDIR)

include $(DEP_FILES)

.PHONY: test
.PHONY: clean
.PHONY: cleanall
.PHONY: all