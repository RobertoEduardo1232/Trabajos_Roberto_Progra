Bin/main: src/main.cpp include/*
	c++ src/main.cpp -o Bin/main -lcurses -I include

run : Bin/main
	./Bin/main

