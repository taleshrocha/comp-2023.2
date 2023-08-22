#!/bin/bash

# Execute o comando 'make'
make

# Compile o arquivo 'teste.c' usando o GCC e a biblioteca 'l'
gcc teste.c -ll

# Execute o programa compilado 'a.out' com entrada redirecionada de 'teste.txt'
./a.out < teste.txt