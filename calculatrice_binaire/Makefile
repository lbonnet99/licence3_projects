NOM=BONNET_Ludivine

test: eval run clean

clean:
	rm -f *.o *gch eval
	rm -fr $(NOM)
	
run :
	./eval
	
eval: eval.o liste_token.o arbre_token.o
	gcc -Wall eval.o liste_token.o arbre_token.o -o eval

liste_token.o: liste_token.c
	gcc -c -Wall liste_token.c liste_token.h

eval.o: eval.c
	gcc -c -Wall eval.c liste_token.h arbre_token.h

arbre_token.o: arbre_token.c
	gcc -c -Wall arbre_token.c liste_token.h
