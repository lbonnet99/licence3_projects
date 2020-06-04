import java.util.Scanner;

public enum Application {

    ENVIRONNEMENT;

    public void run (String[]args)
    {

        System.out.println("----------Mode de jeu----------");
        System.out.println("Vous VS IA - Tapez 1");
        System.out.println("IA VS IA - Tapez 2");
        System.out.println("Veuillez entrer votre choix : ");
        Scanner sc = new Scanner(System.in);
        String lecture = sc.nextLine();
        int choix = Character.getNumericValue(lecture.charAt(0));

        while(((choix != 1)&&(choix != 2))||(lecture.length()!=1))
        {
            System.out.println("ERREUR : entrée invalide. Veuillez à nouveau entrer votre choix");
            lecture = sc.nextLine();
            choix = Character.getNumericValue(lecture.charAt(0));
        }

        if(choix == 1)
        {
            IA ia = new IA("ia",1);
            Personne J = new Personne("Bibi",0);
            Plateau p = new Plateau();
            int a_jouer;

            p.init_plateau();

			Piece r1=new Roi(0,'i',2);/*futurs roi*/
			Piece r2=new Roi(1,'i',2);/*placer à des positions impossibles pour les instancier*/
			for (Piece i : p.getListe())
			{
				if(i instanceof Roi)
				{
					if(i.getCoul()==0)
					{
						r1 = i;
					}
					else
					{
						r2 = i;/* récupérer les 2 rois*/
					}
				}
			}
			int i = 1;
            while(!(((Roi) r1).echec_et_mat(p) || ((Roi) r2).echec_et_mat(p)))
            {
                System.out.println(p.getUndo().getPile().getPileCoord());
                System.out.println(p.getUndo().getPile().getPilePiece());
                System.out.println("##########Tour "+i+"##########");
                System.out.println("Au tour de : "+J.getNom());
                System.out.print("Entrez les coordonnées : ");
                lecture = J.saisie(sc);

                if(lecture.equals("undo"))
                {
                    while(lecture.equals("undo"))
                    {
                        p.getUndo().sup_mov(p);
                        System.out.println("Que voulez-vous faire ?");
                        System.out.println("Annuler un coup ? Tapez undo.");
                        System.out.println("Quitter ? Tapez quit.");
                        System.out.println("Entrez votre choix : ");
                        lecture = J.saisie(sc);
                    }

                    if(p.getUndo().getPile().getPilePiece().isEmpty())
                    {
                        System.out.println("Au tour de : "+J.getNom());
                        System.out.print("Entrez les coordonnées : ");
                        lecture = J.saisie(sc);
                        J.jouer(p,lecture,sc);
                    }
                    else if(p.getUndo().getPile().getPilePiece().peek().getCoul() == ia.getCouleur())
                    {
                        System.out.println("Au tour de : "+J.getNom());
                        System.out.print("Entrez les coordonnées : ");
                        lecture = J.saisie(sc);
                        J.jouer(p,lecture,sc);
                    }
                }
                else
                {
                    a_jouer = J.jouer(p,lecture,sc);

                    while(a_jouer == 0)
                    {
                        System.out.println("ERREUR : Pas de pièce à cet endroit");
                        System.out.println("Entrez les coordonnées : ");
                        lecture = J.saisie(sc);
                        a_jouer = J.jouer(p,lecture,sc);
                    }
                }

                System.out.print('\n');
                System.out.println("Au tour de : "+ia.getNom());
                ia.jouer(p);

                System.out.print('\n');
                i++;
				for (Piece j : p.getListe())
				{
					if(j instanceof Roi)
					{
						if(j.getCoul()==0)
						{
							r1 = j;
						}
						else
						{
							r2 = j;/* récupérer les 2 rois*/
						}
					}
				}
            }
        }
        else if(choix == 2)
        {
            IA ia = new IA("ia",1);
            IA ia1 = new IA("ia1",0);
            Plateau p = new Plateau();
            Piece r1=new Roi(0,'i',2);/*futurs roi*/
			Piece r2=new Roi(1,'i',2);/*placer à des positions impossibles pour les instancier*/
			for (Piece i : p.getListe())
			{
				if(i instanceof Roi)
				{
					if(i.getCoul()==0)
					{
						r1 = i;
					}
					else
					{
						r2 = i;/* récupérer les 2 rois*/
					}
				}
			}


            p.init_plateau();

            int i = 1;
            while(!(((Roi) r1).echec_et_mat(p) || ((Roi) r2).echec_et_mat(p)))
            {


				System.out.println(p.getUndo().getPile().getPileCoord());
                System.out.println(p.getUndo().getPile().getPilePiece());
                System.out.println("##########Tour "+i+"##########");
                System.out.println("Au tour de : "+ia.getNom());
                ia.jouer(p);
                try {
                    Thread.sleep(2000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                System.out.print('\n');
                System.out.println("Au tour de : "+ia1.getNom());
                ia1.jouer(p);
                i++;
				for (Piece j : p.getListe())
				{
					if(j instanceof Roi)
					{
						if(j.getCoul()==0)
						{
							r1 = j;
						}
						else
						{
							r2 = j;/* récupérer les 2 rois*/
						}
					}
				}
            }
        }

        sc.close();
        /*
		Plateau p = new Plateau();
		Roi R = new Roi(1,'d',8);
		Reine T = new Reine(0,'d',7); //Initialiser la pièce de votre choix
		Roi R1 = new Roi(0,'c',6); // A utiliser pour tester la capture
		//Tour T1 = new Tour(1,'h',7);
		//Ajout dans la liste
	    p.add_elem(R);
		p.add_elem(R1);
		p.add_elem(T);
		//p.add_elem(T1);

		p.getUndo().add_mov(R);
		p.getUndo().add_mov(R1);
		p.getUndo().add_mov(T);
		//p.getUndo().add_mov(T1);

		System.out.print(R.echec_et_mat(p));

		//Test du déplacement

		l.deplacement(p,'a',7);
		System.out.print(l.getAbs());
		System.out.print(l.getOrd());*/





    }

    public static void main(String[]args)
    {
        ENVIRONNEMENT.run(args);
    }
}
