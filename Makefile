CPP=g++
CPPFLAGS=-g -Wextra  -Wall 

SRC=$(wildcard *.cpp)
INC=$(wildcard *.hpp)
OBJS=$(SRC:.cpp=.o)

LFLAGS= -lIrrlicht -lGL 
EXEC=Fortress_Constructor 

.PHONY: all clean mrproper

all : $(EXEC)

$(EXEC) : $(OBJS) $(INC)
	@$(CPP) $(OBJS) -o $@  $(LFLAGS)

%.o:%.c
	@$(CPP) -c $< -o $@ $(CPPFLAGS)

clean :
	@rm *.o
mrproper :
	@rm $(EXEC)