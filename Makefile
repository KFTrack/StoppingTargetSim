# Ed Callaghan
# G4 example Makefile
# October 2023

EXE			:= example
SRC			:= main.cpp
CPPFLAGS	:= $(CPPFLAGS) -I./include
CPPFLAGS	:= $(CPPFLAGS) $(shell geant4-config --cflags)
LDFLAGS		:= $(LDFLAGS) $(shell geant4-config --libs)

SRCS		:= $(wildcard ./src/*.cpp)
OBJS		:= $(addprefix ./build/, $(notdir $(SRCs:.cpp=.o)))

all: compile

compile: $(EXE) $(OBJS)

$(EXE): $(SRC) $(OBJS)
	$(CXX) -o $@ $(CPPFLAGS) $^ $(LDFLAGS)

clean:
	rm -f $(EXE)

.PHONY: clean
