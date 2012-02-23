CPP=g++
CPPFLAGS=-g -Wextra  -Wall 

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
