#include "typedefs.h"

char* type_name(int type_id) {
    switch (type_id) {
        case E_INT:
            return "int";
        case E_REAL:
            return "real";
        case E_CHAR:
            return "char";
        case E_BOOL:    
            return "bool";
        case E_ARRAY:   
            return "array";
        case E_RECORD:  
            return "record";
        case E_FUNCTION:
            return "function";
        case E_PROCEDURE:
            return "procedure";
        default:
            return "undefined";
    }
}
