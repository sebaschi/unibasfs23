# To run, enter: make all

all: diningphilosophers

diningphilosophers: main.o dining.o philosopher.o
	gcc -o diningphilosophers main.o dining.o philosopher.o -lpthread -fcommon

main.o: main.c dp.h
	gcc -lpthread -c main.c -lpthread -fcommon

dining.o: dining.c dp.h
	gcc -lpthread -c dining.c -lpthread -fcommon

philosopher.o: philosopher.c dp.h
	gcc -lpthread -c philosopher.c -lpthread -fcommon

clean: 
	rm *.o
	rm diningphilosophers
