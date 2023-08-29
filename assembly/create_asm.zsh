#!/usr/bin/zsh

cd $(pwd)/assembly/
nasm -f elf64 test.s && gcc -Wall -Wextra -Werror -nostartfiles -no-pie test.o -o test
objdump -d -j .text test > tmp
python3 ./clean_objdump.py tmp
if [ -e "./test.o" ]
then
    rm ./test.o
    rm ./tmp
    rm ./test
fi
cd ..