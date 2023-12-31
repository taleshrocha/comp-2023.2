# Simple Makefile

CC = gcc
LIBS = -lfl
LEX = lex
YACC = yacc

CFLAGS = -Wall -Wextra -Werror 
 
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

debug: CFLAGS += -DDEBUG -g -O0
debug: all

sanitize: CFLAGS += -DDEBUG -g -O0 -fsanitize=address -fno-omit-frame-pointer
sanitize: all

release: CFLAGS += -O3
release: all


# executable

$(BIN)/parser: $(OBJS)/symtab.o $(OBJS)/parser.o $(OBJS)/lexer.o $(OBJS)/exception.o $(OBJS)/code_generation.o
	$(CC) $(CFLAGS) $^ $(LIBS) -I $(INCLUDE) -o $@ 

# objects

$(OBJS)/lexer.o: $(SRC)/lexer.l.c 
	$(CC) $(CFLAGS) -c $< $(LIBS) -I$(INCLUDE) -o $@ 

$(OBJS)/parser.o: $(SRC)/parser.y.c $(SRC)/lexer.l.c
	$(CC) $(CFLAGS) -c $< $(LIBS) -I$(INCLUDE) -o $@ 

$(OBJS)/symtab.o: $(SRC)/symtab.c
	$(CC) $(CFLAGS) -c $< $(LIBS) -I$(INCLUDE) -o $@ 

$(OBJS)/lexerTest.o: $(SRC)/lexerTest.c
	$(CC) $(CFLAGS) -c $< $(LIBS) -I$(INCLUDE) -o $@ 

$(OBJS)/exception.o: $(SRC)/exception.c 
	$(CC) $(CFLAGS) -c $< $(LIBS) -I$(INCLUDE) -o $@ 

$(OBJS)/code_generation.o: $(SRC)/code_generation.c 
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


valgrind:
	valgrind -s --leak-check=full --show-leak-kinds=all ./bin/parser $(file)