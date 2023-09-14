#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defines.h"
#include "typedefs.h"
#include "symbolTable.h"
#include "lexer.h"

int main() {
  initializeSymbolTable();
  printf("starting!...\n");
  int token = yylex();
  while (token != 0) {
      printf("current token is %d-%s\n", token, terminal_mapping[token-1]);
      token = yylex();
  }
  printFirst10Entries();
  printf("end of input! Finalizing!\n");
  destroySymbolTable();
  yylex_destroy();
  return 0;
}
