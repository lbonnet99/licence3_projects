Exercice 1 :

question 1.
Compilation : gcc dm.c -o dm
Execution : ./dm arg[1] =(int[8] ) bits de la fonction de filtrage,  arg[2] = (int[16]) k0,  arg[3] = (int[16]) k1, arg[4] = (int[16]) k2, arg[5] =(int) taille n de la suite générée
Sortie : Suite chiffrante de taille n

question 2.
Compilation : gcc probas.c -o probas
Execution : ./probas
Sortie : Toutes les probabilités de corrélation de toutes les fonctions de filtrage

question 5.
Compilation : gcc attaque.c -o attaque
Execution : ./attaque arg[1] = (int*) suite chiffrante d’une taille minimale de 16 bits
Exemple d'exécution : ./attaque 01010111111110101
Sortie : Les trois clés k0, k1, k2 ou rien si on ne trouve pas

Exercice 2 :

question 2
Compilation : gcc q2exo2 -o exe
Execution : ./exe arg[1] = (int[32]) x0_L, arg[2] = (int[32]) x0_R, arg[3] = (int[32)] x1_L, arg[4] = (int[32]) x1_R
Sortie : clés k0 et k1

