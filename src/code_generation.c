#include "code_generation.h"
#include "symtab.h"

char* get_c_type(int type_id) {
    switch (type_id) {
        case E_INT:
            return "int";
        case E_REAL:
            return "float";
        case E_CHAR:
            return "char";
        case E_STRING:
            return "char*";
        case E_BOOL:    
            return "short";
        default:
            return "__ERROR__";
    }    
        
}
