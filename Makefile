DIR = $(shell find inc -type d)
BINDIR = $(DIR:inc%=bin%)
LIBS =
SAN =
CPPFLAGS = -MMD -MP -Ibin -Iinc $(SAN)
CFLAGS = $(SAN)
CXXFLAGS = -std=c++17 -ggdb3 $(SAN)
LDFLAGS = $(SAN)

CC = gcc
CXX = g++
LD = g++
RM = rm

BIN = ./bin/main

HDR = $(shell find inc -type f)

SRC = $(shell find src -type f)
OBJ = $(SRC:src/%=bin/%.o)

DEP = $(OBJ:bin/%.o=bin/%.d)

all:: $(BINDIR) $(BIN)

$(BIN): $(OBJ)
	$(LD) -o $@ $^ $(LDFLAGS)

bin/%.c.o: src/%.c
	$(CC) $(CPPFLAGS) -c -o $@ $< $(CFLAGS)

bin/%.cpp.o: src/%.cpp
	$(CC) $(CPPFLAGS) -c -o $@ $< $(CXXFLAGS)

run:: all
	$(BIN)

clean::
	$(RM) -rf bin

$(BINDIR): %:
	mkdir -p $@

-include $(DEP)

