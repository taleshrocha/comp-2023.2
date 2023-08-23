#include <stdbool.h>
#include <stdio.h>


typedef struct TokenValue {
    unsigned int token;
    union {
        int value;
        float value;
        char value;
        bool value;
        unsigned int value; 
    };
} TokenValue;

int main(int argc, char const *argv[])
{
    TokenValue a;
    a.token = 1;
    a.value = 1.0;

    printf("token_id %d\n", a.token);
    printf("value %f\n", a.value);

    return 0;
}
