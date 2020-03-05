mkdir bin 2> /dev/null
gcc -std=gnu99 -g -Wall -O2 $(ls src/*.c) -o bin/snake -lcurses
