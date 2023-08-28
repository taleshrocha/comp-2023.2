#include "symbolTable.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "typedefs.h"

size_t maxNumSymbols = SYMBOL_TABLE_INITIAL_SIZE;
int SCOPE = SCOPE_LEVEL;
// Dynamic array
ScopeEntry* curr_scope;
size_t numSymbols = 0;
TokenData yylval;

void initializeSymbolTable() {
  curr_scope = (ScopeEntry*)malloc(sizeof(ScopeEntry));
  curr_scope->previous_scope = NULL;
  curr_scope->symbol_table =
      (SymbolEntry*)malloc(SYMBOL_TABLE_INITIAL_SIZE * sizeof(SymbolEntry));
  curr_scope->capacity = SYMBOL_TABLE_INITIAL_SIZE;
  curr_scope->size = 0;
}

void destroySymbolTable() {
  ScopeEntry* aux;
  while (curr_scope->previous_scope != NULL) {
    for (size_t i = 0; i < curr_scope->size; i++) {
      free(curr_scope->symbol_table[i].name);
    }
    free(curr_scope->symbol_table);
    aux = curr_scope->previous_scope;
    free(curr_scope);
    curr_scope = aux;
  }
  free(curr_scope->symbol_table);
  free(curr_scope);
}

unsigned int addSymbol(const char* name) {
  // TODO: Analisar abordagem O(1) usando hashtable com chave string sendo unica
  // (ex.: lexema+escopo)
  for (size_t i = 0; i < curr_scope->size; i++) {
    if (strcmp(curr_scope->symbol_table[i].name, name) == 0) {
      printf(
          "Ja existe um token na tabela de simbolos com o lexema \"%s\".\n",
          name);
      return i;
    }
  }
  if (curr_scope->size == curr_scope->capacity) {
    increaseTableSize();
  }

  curr_scope->symbol_table[curr_scope->size].name = strdup(name);
  return curr_scope->size++;
}

void printFirst10Entries() {
  printf("\n\n\tTABELA DE SIMBOLOS (10 primeiros)\n");
  for (int i = 0; i < 10; i++) {
    printf("TokenName: %s \t TokenClass: %d \n",
           curr_scope->symbol_table[i].name, curr_scope->symbol_table[i].type);
  }
}

void increaseTableSize() {
  // Memory allocation (doubling symbol_table current size)
  SymbolEntry* new_symbol_table =
      (SymbolEntry*)malloc(2 * curr_scope->capacity * sizeof(SymbolEntry));

  if (new_symbol_table == NULL) {
    printf(
        "Error: could not increase Symbol Table. No free memory available.\n");
    exit(1);
  }

  // Deep copy
  for (size_t i = 0; i < curr_scope->capacity; i++) {
    new_symbol_table[i].name = curr_scope->symbol_table[i].name;
    new_symbol_table[i].type = curr_scope->symbol_table[i].type;
  }

  curr_scope->capacity = curr_scope->capacity * 2;

  free(curr_scope->symbol_table);
  curr_scope->symbol_table = new_symbol_table;
}
// Acho que seria interessante ter uma forma de ver toda a tabela de símbolos para fins de debug
void showFullTable() {
    printf("Tabela de Simbolos completa: \n \n");
  for (size_t i = 0; i < curr_scope->size; i++) {
    printf("Token: %s \t Class: %d \n", curr_scope->symbol_table[i].name, curr_scope->symbol_table[i].type);
  }
}

void increaseScopeLevel() {
  SCOPE++;
  printf("Nível de escopo aumentado \n Escopo: %d \n", SCOPE);
}

void decreaseScopeLevel() {
  SCOPE--;
  printf("Nível de escopo reduzido \n Escopo: %d \n", SCOPE);
}
