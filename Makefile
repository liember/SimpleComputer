.PHONY: test
.PHONY: clean
.PHONY: all

LIBS = -linterpreter -lmemory -lregisters

CC = g++
CFLAGS = -Wall -g

DEPFLAGS = -MP -MMD 

INCLUDE_FLAG = -I include
LIBS_FLAG = -L libs

DEPDIR = dep/
OBJDIR = build/
BINDIR = bin/
SRCDIR = src/
LIBDIR = libs/
INCDIR = include/
MODDIR = $(SRCDIR)modules/

SRC_FILES := $(wildcard $(SRCDIR)*.cpp)
OBJ_FILES := $(patsubst $(SRCDIR)%.cpp,$(OBJDIR)%.o,$(SRC_FILES))
DEP_FILES := $(wildcard $(DEPDIR)*.d)
EXECUTABLE = $(BINDIR)main

all: dirs libgen $(EXECUTABLE)
 
$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ $(INCLUDE_FLAG) $(LIBS_FLAG) $(LIBS) -o $@
 
$(OBJDIR)%.o : $(SRCDIR)%.cpp
	$(CC) $(CFLAGS) $(DEPFLAGS) $(INCLUDE_FLAG) $(LIBS_FLAG) $(LIBS) -c -o $@ $< 
	mv -f $(OBJDIR)$*.d $(DEPDIR)$*.d

libgen:
	cd $(MODDIR)/memory && make
	cd $(MODDIR)/interpreter && make
	cd $(MODDIR)/registers && make


dirs:
	mkdir -p $(OBJDIR) $(BINDIR) $(DEPDIR)
		
clean:
	rm -f $(BINDIR)* $(OBJDIR)*.o $(DEPDIR)*.d

cleanall:
	rm -R bin build dep

include $(DEP_FILES)