L1:
	gcc -o mylib1.o -c l1.c
	gcc T3.c -o t3_case1.o -L. mylib1.o
L2:
	gcc -o mylib2.o -c l2.c
	gcc T3.c -o t3_case2.o -L. mylib2.o
L3:
	gcc -o t3_case3.o T3.c l1.c
clean:
	rm *.o
