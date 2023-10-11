# Simple Makefile

CC = gcc
LIBS = -lfl
LEX = lex
YACC = yacc

CFLAGS = -Wall -Wextra #-Werror 
 
BIN=./bin
OBJS=./objs
SRC=./src
INCLUDE=./include

# main target
all: mkfolders  $(BIN)/parser 

# create folders

mkfolders:
	mkdir -p bin
	mkdir -p objs

# debug

debug: CFLAGS += -DDEBUG -g -O0 #-fsanitize=address -fno-omit-frame-pointer
debug: all

release: CFLAGS += -O3
release: all


# executables

# $(BIN)/lexer_test: $(OBJS)/lexer.o $(OBJS)/symbolTable.o $(OBJS)/lexerTest.o
# 	$(CC) $(CFLAGS) $^ $(LIBS) -I $(INCLUDE) -o $@ 

# $(BIN)/nonRecursiveParser: $(OBJS)/lexer.o $(OBJS)/symbolTable.o $(OBJS)/nonRecursiveParser.o
# 	$(CC) $(CFLAGS) $^ $(LIBS) -I $(INCLUDE) -o $@ 

# $(BIN)/recursiveParser: $(OBJS)/lexer.o $(OBJS)/symbolTable.o $(OBJS)/recursiveParser.o
# 	$(CC) $(CFLAGS) $^ $(LIBS) -I $(INCLUDE) -o $@ 

$(BIN)/parser: $(OBJS)/parser.o $(OBJS)/lexer.o $(OBJS)/symbolTable.o
	$(CC) $(CFLAGS) $^ $(LIBS) -I $(INCLUDE) -o $@ 

# objects

$(OBJS)/lexer.o: $(SRC)/lexer.l.c 
	$(CC) $(CFLAGS) -c $< $(LIBS) -I$(INCLUDE) -o $@ 

$(OBJS)/parser.o: $(SRC)/parser.y.c
	$(CC) $(CFLAGS) -c $< $(LIBS) -I$(INCLUDE) -o $@ 

$(OBJS)/symbolTable.o: $(SRC)/symbolTable.c
	$(CC) $(CFLAGS) -c $< $(LIBS) -I$(INCLUDE) -o $@ 

$(OBJS)/lexerTest.o: $(SRC)/lexerTest.c
	$(CC) $(CFLAGS) -c $< $(LIBS) -I$(INCLUDE) -o $@ 

$(OBJS)/nonRecursiveParser.o: $(SRC)/nonRecursiveParser.c
	$(CC) $(CFLAGS) -c $< $(LIBS) -I$(INCLUDE) -o $@ 

$(OBJS)/recursiveParser.o: $(SRC)/recursiveParser.c
	$(CC) $(CFLAGS) -c $< $(LIBS) -I$(INCLUDE) -o $@ 

# sources

$(SRC)/lexer.l.c: $(SRC)/lexer.l
	$(LEX) -t --header-file=$(INCLUDE)/lexer.l.h $< > $@ 

$(SRC)/parser.y.c: $(SRC)/parser.y
	$(YACC) -d -Wother -Wcex $< -o $@ 
	mv $(SRC)/parser.y.h $(INCLUDE)/parser.y.h

clean:
	rm -f $(OBJS)/*
	rm -f $(BIN)/*
	rm -f $(SRC)/*.l.c
	rm -f $(SRC)/*.y.c
	rm -f $(INCLUDE)/*.y.h
