# Ed Callaghan
# G4 example Makefile
# October 2023

EXE			:= example
SRC			:= main.cpp
CPPFLAGS	:= -g -Og
CPPFLAGS	:= $(CPPFLAGS) -I./include
CPPFLAGS	:= $(CPPFLAGS) $(shell geant4-config --cflags)
LDFLAGS		:= $(LDFLAGS) $(shell geant4-config --libs)

SRCDIR		:= ./src
OBJDIR		:= ./build
SRCS		:= $(wildcard $(SRCDIR)/*.cpp)
OBJS		:= $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.cpp=.o)))

all: compile

compile: $(EXE) $(OBJS)

$(EXE): $(SRC) $(OBJS)
	$(CXX) -o $@ $(CPPFLAGS) $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) -o $@ -c $(CPPFLAGS) $^

clean:
	rm -f $(EXE) $(wildcard $(OBJDIR)/*.o)

.PHONY: clean
