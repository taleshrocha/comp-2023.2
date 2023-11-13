#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct abacatea {
	float c;
} abacatea;


typedef struct abacate {
	abacatea c;
} abacate;


int main() {
abacate a;
abacatea t1;
float t2;

t1 = a.c;
t2 = t1.c;
t2 = 3.4;

a.c.c = 3.4;
return 0;
}
