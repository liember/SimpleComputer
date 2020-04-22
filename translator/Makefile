.PHONY: clean
.PHONY: all

CC = clang++
CFLAGS = -Wall -std=c++17 -g -I include
DEPFLAGS = -MP -MMD 
DEPDIR = dep/

OBJDIR = build/
BINDIR = bin/

SRCDIR = src/
SRC_FILES := $(wildcard $(SRCDIR)*.cpp)
OBJ_FILES := $(patsubst $(SRCDIR)%.cpp,$(OBJDIR)%.o,$(SRC_FILES))
DEP_FILES := $(wildcard $(DEPDIR)*.d)
EXECUTABLE = $(BINDIR)main

all: dirs $(EXECUTABLE)
 
$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@
 
$(OBJDIR)%.o : $(SRCDIR)%.cpp
	$(CC) $(CFLAGS) $(DEPFLAGS) $(LIBS) -c -o $@ $< 
	mv -f $(OBJDIR)$*.d $(DEPDIR)$*.d

dirs:
	mkdir -p $(OBJDIR) $(BINDIR) $(DEPDIR)
		
clean:
	rm -f $(BINDIR)* $(OBJDIR)*.o $(DEPDIR)*.d 

cleanall:
	rm -R bin build dep

include $(DEP_FILES)