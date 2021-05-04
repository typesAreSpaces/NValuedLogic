IDIR=./include
ODIR=./obj
SDIR=./src
LDIR=/home/jose/Documents/GithubProjects/z3-interp-plus/build
SO_EXT=so
CC=g++

SRC=$(wildcard $(SDIR)/*.cpp)
DEPS=$(wildcard $(IDIR)/*.h)
OBJS=$(SRC:$(SDIR)/%.cpp=$(ODIR)/%.o) $(LDIR)/libz3.$(SO_EXT)
FLAGS=-I$(SDIR) -I$(IDIR) -std=c++11 -Wall

all: test

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS) $(LDIR)/libz3.$(SO_EXT)
	@mkdir -p ./obj
	$(CC) -g -c -o $@ $(FLAGS) $<

bin/main: $(OBJS) $(LDIR)/libz3.$(SO_EXT)
	@mkdir -p ./bin
	$(CC) -g -o $@ $(OBJS) $(FLAGS) -lpthread

test: bin/main
	./bin/main

.PHONY: clean
clean:
	rm -rf $(ODIR)/*
	rm -rf ./bin/main
