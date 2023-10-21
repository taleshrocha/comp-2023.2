#include <stdio.h>
#include "typedefs.h"
char snum[32];

char* type_name(int type_id) {
    switch (type_id) {
        case E_UNDEFINED:
            return "undefined";
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
            printf("type_name func: %d\n", type_id);
            snprintf( snum, 32, "%d", type_id );
            return snum;
    }
}
