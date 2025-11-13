DIR = $(shell find src/include -type d)
BINDIR = $(DIR:src/include%=bin%)
LIBS = pthread
SAN =
CPPFLAGS = -MMD -MP -Ibin -Isrc/include $(SAN)
CFLAGS = $(SAN)
CXXFLAGS = -std=c++20 -ggdb3 $(SAN)
LDFLAGS = $(SAN) $(addprefix -L,$(LIBS))

CC = gcc
CXX = g++
LD = g++
RM = rm

BIN = test client server
BIN_PATH = $(BIN:%=bin/%)

HDR = $(shell find src/include -type f)

SRC = $(shell find src -type f -name "*.cpp")
SRC_NOMAIN = $(filter-out $(BIN:%=src/%.cpp),$(SRC))
OBJ = $(SRC:src/%=bin/%.o)
OBJ_NOMAIN = $(SRC_NOMAIN:src/%=bin/%.o)

DEP = $(SRC:src/%=bin/%.d)

all:: $(BINDIR) $(BIN_PATH)

$(BIN_PATH): bin/%: bin/%.cpp.o $(OBJ_NOMAIN)
	$(LD) -o $@ $^ $(LDFLAGS)

bin/%.c.o: src/%.c
	$(CC) $(CPPFLAGS) -c -o $@ $< $(CFLAGS)

bin/%.cpp.o: src/%.cpp
	$(CXX) $(CPPFLAGS) -c -o $@ $< $(CXXFLAGS)

run-%:: all
	$(@:run-%=bin/%)

clean::
	$(RM) -rf bin

$(BINDIR): %:
	mkdir -p $@

-include $(DEP)

