echo "Cleaning...\n"
make clean
echo "\n"
echo "Compiling...\n"
make
echo "\n"
echo "Executing...\n\n"
./bin/lexer < ./tests/recursive-parser/success1.txt