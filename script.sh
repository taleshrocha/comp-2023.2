echo "Cleaning...\n"
make clean
echo "\n"
echo "Compiling...\n"
make
echo "\n"
echo "Executing...\n\n"
./bin/parser < example4.txt