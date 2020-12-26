###### PATHS #######
HEADPATH = .
BINPATH  = .
OBJPATH	 = .
SRCPATH	 = .

###### COMPIL ######
CPPFLAGS =
CFLAGS   =
LDLIBS   =

DEBUG  = YES

CC = g++

ifeq ($(DEBUG),YES)
	CPPFLAGS +=
	CFLAGS   += -Wall -Wextra -g
	LDLIBS   +=
	TEXTE 	 += " debug"

else
	CPPFLAGS +=
	CFLAGS   += -O2
	LDLIBS   +=
	TEXTE 	 += " release"
endif

###### FILES ######
EXEC = $(BINPATH)/main

SRC  = $(wildcard $(SRCPATH)/*.cpp)
HEAD = $(wildcard $(HEADPATH)/*.h)
OBJ  = $(SRC:$(SRCPATH)/%.cpp=$(OBJPATH)/%.o)
DIST = $(SRC) $(HEAD) Makefile Doxyfile

###### TARGETS ######
all: $(EXEC)
	@echo "${LCYAN}\nExécutable généré en mode"$(TEXTE)".${NC}"
	
$(EXEC): $(OBJ)
	@echo "${LCYAN}\n----Rule " $@ "----${NC}"
	$(CC) $(CPPFLAGS) -o $@ $^ $(CFLAGS) $(LDLIBS)
	

$(OBJPATH)/%.o: $(SRCPATH)/%.cpp
	@echo "${LCYAN}\n----Rule " $@ "----${NC}"
	$(CC) $(CPPFLAGS) -o $@ -c $< $(CFLAGS) $(LDLIBS)

clean:
	rm -rf $(OBJPATH)/*.o
	rm -rf $(EXEC)

## Depositories creation ##

######## DOC ########

#### DEPENDANCIES ####

###### MISC ######
LCYAN=\033[1;36m
NC=\033[0m # No Color

######
