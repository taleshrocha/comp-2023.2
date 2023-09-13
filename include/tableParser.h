#ifndef TABLEPARSER_H
#define TABLEPARSER_H

#include "defines.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

extern int capacity;
extern int curr_size;

extern int matrix[45][56][10];

extern int* stack;

void initialize_stack();

int pop();

int peek();

void push(int value);

int* get_symbols(int nt, int t);

void insert_symbols(int* symbols);

void error();

void print_stack();

// int main() {
//   int current_terminal = yylex();
//   int current_symbol = pop();
//   while (peek() != EndOfInput) {
//     if (current_symbol == current_terminal) {
//       current_terminal = yylex();
//     //   current_symbol = pop();
//     } else if (current_symbol < 100) {
//         error();
//     } else if (get_symbols(current_symbol-100, current_terminal-1)[0] == 0) {
//         error();
//     } else {
//         insert_symbols(get_symbols(current_symbol-100, current_terminal-1));
//     }
//     current_symbol = pop();
//   }
// }

#endif  // TABLEPARSER_H
