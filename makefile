# Simple Makefile

CC = gcc
LIBS = -lfl
LEX = lex

CFLAGS = -Wall -Wextra -Werror
 
BIN=./bin
OBJS=./objs
SRC=./src
INCLUDE=./include

# main target
all: mkfolders $(BIN)/lexer

# create folders

mkfolders:
	mkdir -p bin
	mkdir -p objs

# debug

debug: CFLAGS += -DDEBUG -g -O0
debug: all

# executables

$(BIN)/lexer: $(OBJS)/lexer.o 
	$(CC) $< $(LIBS) -I $(INCLUDE) -o $@ 

# objects

$(OBJS)/lexer.o: $(SRC)/lexer.l.c
	$(CC) -c $< $(LIBS) -I$(INCLUDE) -o $@ 

# sources

$(SRC)/lexer.l.c: $(SRC)/lexer.l
	$(LEX) -t $< > $@ 

clean:
	rm -f $(OBJS)/*
	rm -f $(BIN)/*
	rm -f $(SRC)/*.l.c
