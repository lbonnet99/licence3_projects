Miller_Rabin: Miller_Rabin.o SquareAndMultiply.o
	gcc -o exe Miller_Rabin.o SquareAndMultiply.o -lgmp
	
Fermat:	Fermat.o SquareAndMultiply.o
	gcc -o exe Fermat.o SquareAndMultiply.o	-lgmp

Miller_Rabin.o:	Miller_Rabin.c
	gcc -c 	Miller_Rabin.c

Fermat.o:	Fermat.c
	gcc -c Fermat.c
	
SquareAndMultiply.o:	SquareAndMultiply.c SquareAndMultiply.h
	gcc -c SquareAndMultiply.c SquareAndMultiply.h

clean : 
	rm *.gch
	rm exe
	rm *.o