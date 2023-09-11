#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include "defines.h"
#include "stdlib.h"

int capacity = 1000;
int curr_size = 0;

int matrix[45][55][10];

int *stack;

void initialize_stack() {
    stack = (int *)malloc(sizeof(int) * capacity);
}

int pop() {
    return stack[curr_size--];
}

int peek(){
    return stack[curr_size];
}

void push(int value) {
    if (curr_size == capacity) {
        capacity = capacity * 2;
        int new_stack = (int *)malloc(sizeof(int) * capacity);
        memcpy(new_stack, stack, sizeof(int) * curr_size);
        free(stack);
        stack = new_stack;
    }
    stack[curr_size++] = value;
}

int* get_symbols(int nt, int t) {
    return matrix[nt][t];
}

void insert_symbols(int* symbols) {
    int i = 0;
    while (i < 10 && symbols[i] != -1){
        push(symbols[i]);
        ++i;
    }
}

void error() {
    printf("Erro!\n"); // TODO: Implementar
}

int main() {
  int current_terminal = yylex(); 
  int current_symbol = pop();
  while (peek() != EndOfInput) {
    if (current_symbol == current_terminal) {
      current_terminal = yylex(); 
    //   current_symbol = pop();
    } else if (current_symbol < 100) {
        error();
    } else if (get_symbols(current_symbol-100, current_terminal-1) == NULL) {
        error();
    } else {
        insert_symbols(get_symbols(current_symbol-100, current_terminal-1));
    }
    current_symbol = pop();
  }
}

#endif // SYMBOLTABLE_H

