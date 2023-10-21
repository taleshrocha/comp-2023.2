// #ifndef TYPEDEFS_H
// #define TYPEDEFS_H

// #include <stddef.h>
// #include <stdbool.h>



// typedef struct ArrayData {
//   E_TYPE type;
//   int size;
//   int id;
// } ArrayData;

// typedef struct TypeNamePair {
//   E_TYPE type;
//   char* name;
// } TypeNamePair;

// typedef struct RecordData {
//   TypeNamePair* fields;
//   int id;
// } RecordData;

// typedef struct FunctionData {
//   TypeNamePair* params;
//   E_TYPE return_type;
//   // ??? comandos ???
//   int id;
// } FunctionData;

// typedef struct ProcedureData {  // ??? precisa ser uma struct diferente entre
//                                 // function e procedure?
//   TypeNamePair* params;
//   // ??? comandos ???
//   int id;
// } ProcedureData;

// typedef union TokenData {
//   unsigned int id_index;
//   int int_value;
//   float real_value;
//   bool bool_value;
//   char char_value;
//   char* string_value;
// } TokenData;

// typedef struct SymbolEntry {
//   char* name;
//   E_TYPE type;
//   union {
//     ArrayData array_data;
//     RecordData record_data;
//     FunctionData function_data;
//     ProcedureData procedure_data;
//     bool bool_data;
//     int int_data;
//     float real_data;
//     char char_data;
//     char* string_data;
//     // VarData var_data
//   };
// } SymbolEntry;

// typedef struct ScopeEntry {
//   SymbolEntry* symbol_table;
//   size_t capacity;
//   size_t size;
//   struct ScopeEntry* previous_scope;
//   struct ScopeEntry* next_scopes;
//   size_t next_scopes_size;

// } ScopeEntry;
// struct Node;
// typedef struct Node {
//   int identifier;
//   struct Node* children;
// } Node;

// Node* createNode(int identifier, Node* children);


// #endif  // TYPEDEFS_H