LANG=en
CPP=g++

ifeq ($(LANG), fr)
	CPPFLAGS=-g -Wextra  -Wall -D_LANG_FR
else
	CPPFLAGS=-g -Wextra  -Wall -D_LANG_EN
endif

SRC=$(wildcard src/*.cpp)
INC=$(wildcard src/*.hpp)
OBJS=$(SRC:.cpp=.o)

LFLAGS= -lIrrlicht -lGL 
EXEC=bin/Fortress_Constructor 

.PHONY: all clean mrproper

all : $(EXEC)

$(EXEC) : $(OBJS) $(INC)
	@$(CPP) $(OBJS) -o $@  $(LFLAGS)

%.o:%.c
	@$(CPP) -c $< -o $@ $(CPPFLAGS)

clean :
	@rm $(OBJS)
mrproper :
	@rm $(EXEC)
