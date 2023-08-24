#!/usr/bin/zsh

cd test_fold
nasm -f elf64 test.s && gcc -Wall -Wextra -Werror -nostartfiles -no-pie test.o -o test
objdump -d -j .text test > tmp
python3 ./clean_objdump.py tmp
cd ..