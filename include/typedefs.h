#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <stddef.h>
#include <stdbool.h>

typedef enum E_TYPE {
  E_UNDEFINED,
  E_INT,
  E_REAL,
  E_CHAR,
  E_BOOL,
  E_ARRAY,
  E_RECORD,
  E_FUNCTION,
  E_PROCEDURE
} E_TYPE;

typedef struct ArrayData {
  E_TYPE type;
  int size;
} ArrayData;

typedef struct TypeNamePair {
  E_TYPE type;
  char* name;
} TypeNamePair;

typedef struct RecordData {
  TypeNamePair* fields;
  char* name;  // um record obrigatoriamente precisa ter um nome?
} RecordData;

typedef struct FunctionData {
  TypeNamePair* params;
  E_TYPE return_type;
  // ??? comandos ???
  char* name;  // a função sabe seu proprio nome?
} FunctionData;

typedef struct ProcedureData {  // ??? precisa ser uma struct diferente entre
                                // function e procedure?
  TypeNamePair* params;
  // ??? comandos ???
  char* name;  // o procedure sabe seu proprio nome?
} ProcedureData;

typedef union TokenData {
  unsigned int id_index;
  int int_value;
  float real_value;
  bool bool_value;
  char char_value;
  char* string_value;
} TokenData;

typedef struct SymbolEntry {
  char* name;
  E_TYPE type;
  union {
    ArrayData array_data;
    RecordData record_data;
    FunctionData function_data;
    ProcedureData procedure_data;
  };
} SymbolEntry;

typedef struct ScopeEntry {
  struct ScopeEntry* previous_scope;
  SymbolEntry* symbol_table;
  size_t capacity;
  size_t size;

} ScopeEntry;

#endif  // TYPEDEFS_H