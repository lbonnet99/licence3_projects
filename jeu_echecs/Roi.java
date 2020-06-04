import java.util.ArrayList;
public class Roi extends Piece{

    /**
     * Constructeur
     *
     * @param C, la couleur de la pièce (0 pour blanc, 1 pour noir).
     * @param x, l'abscisse de départ.
     * @param y, l'ordonnée de départ.
     */
    public Roi(int C,char x,int y)
    {
        super(C,x,y);
    }


    @Override
    /**
     * Méthode de vérification du déplacement pour un Roi.
     * @param E, l'échequier.
     * @param xa, l'abscisse d'arrivée.
     * @param ya, l'ordonnée d'arrivée.
     * @return Vrai si le Roi est déplaçable, faux sinon.
     */
    public boolean est_deplacable(Plateau E,char xa,int ya)
    {
        char xdep = getAbs();
        int ydep = getOrd();
        int coul = getCoul();

        int x = Math.abs(xa - xdep);
        int y = Math.abs(ya - ydep);


        if((x>1) || (y>1) || ((y==0)&&(x==0)))/*il faut que la valeur absolue soit comprise entre 0 et 1 et que le roi ne
        soit pas déplaçable sur place*/
        {
            return false;
        }

        for(Piece p : E.getListe())
        {
            if(coul==p.getCoul()) {
                if (p.getAbs() == xa && p.getOrd() == ya) {
                    return false;/*ne pas manger une pièce qui appartient au roi lui-même*/
                }
            }
        }
        return true;

    }

    /**
     * Méthode pour vérifier si le Roi est en situation d'échec.
     * @param E, l'échequier.
     * @return Vrai si le Roi est en situation d'échec, faux sinon.
     */

    public boolean echec(Plateau E)
    {
        int coul = getCoul();
        for(Piece p : E.getListe())
        {
            if(coul!=p.getCoul())
            {
                if(p instanceof Pion)
                {
                    if(((Pion) p).est_mangeable(E,getAbs(),getOrd()))
                    {
                        return true;/*si un pion adverse peut manger le roi*/
                    }
                }
                else
                {
                    if(p.est_deplacable(E,getAbs(),getOrd()))
                    {
                        return true;/*ou une autre piece peut manger le roi*/

                    }
                }
            }
        }
        return false;
    }

    /**
     * Méthode pour vérifier à partir de tous les déplacemnts du roi,s'il peut sortir de sa situation d'échec.
     * @param E, l'échequier.
     * @return Vrai si le Roi ne peut plus se sortir de sa situation d'échec, faux sinon.
     */
    public boolean roi_ne_pas_sortir_pos_echec(Plateau E)
    {

        if(echec(E))
        {
            for(char i ='a';i<='h';i++) {
                for (int j = 1; j <= 8; j++) {/* parcourir toutes le cases du plateau*/
                    if(est_deplacable(E,i,j)){/*si le roi est déplaçable*/
                        deplacement(E,i,j); /* on teste le déplacement*/
                        if(!echec(E)) {
                            E.getUndo().sup_mov(E);/*revenir à la position initiale*/
                            return false;/*cela signifie qu'il y a au moins un déplacement possible pour sortir
                            de la position d'échec*/
                        }
                        E.getUndo().sup_mov(E); /*revenir à la position initiale*/
                    }

                }
            }
            return true;
        }
        else
            return false;//s'il n'y a pas d'échec

    }

    /**
     * Méthode pour vérifier que parmi les pièces appartenant au joueur du roi, il en existe au moins une qui couvre le roi
     * @param E, l'échequier.
     * @return Vrai si il existe une pièce qui couvre le Roi qui ne sera plus en échec, faux sinon.
     */

    public boolean aucune_piece_couvre_roi(Plateau E)
    {

        if(echec(E)) {
            for (char i = 'a'; i <= 'h'; i++) {
                for (int j = 1; j <= 8; j++) {/* parcourir toutes les cases du plateau*/
                    for(Piece p : E.getListe())
                    {
                        if(p.getCoul()==getCoul())/*toutes les pièces du joueur du roi*/
                        {
                            if(! (p instanceof Roi)) {/*sauf le roi lui-même*/
                                if (p.est_deplacable(E, i, j)) {
                                    deplacement(E,i,j);/*faire le déplacement*/
                                    if (!echec(E)) {/*tester s'il y a échec après déplacement*/
                                        E.getUndo().sup_mov(E);/*revenir à la position initiale*/
                                        return false;
                                    }
                                   E.getUndo().sup_mov(E);/*revenir à la position initiale*/
                                }
                            }
                        }

                    }
                }
            }
            return true;
        }
        else return false;/*quand le roi n'est pas en échec*/

    }

    /**
     * Méthode pour vérifier que parmi les pièces mettant en danger le roi, il existe une pièce du joueur du roi qui peut
     * capturer la pièce qui met en danger le roi
     * @param E, l'échequier.
     * @return Vrai si il existe une piece qui peut manger la piece mettant en danger, ainsi le roi n'est plus en
     * échec, Faux sinon
     */
    public boolean aucune_piece_mange_piece_mettant_danger(Plateau E)
    {

        {
            ArrayList<Piece> sauv = new ArrayList<Piece>();

            /*Trouver la pièce mettant en échec le roi*/

            for(Piece p : E.getListe())
            {
                if(p.getCoul()!= getCoul())
                {
                    /*Vérification que la pièce peut se déplacer sur la case du Roi*/
                    if(p instanceof Pion)
                    {
                        if(((Pion)p).est_mangeable(E,getAbs(),getOrd())) sauv.add(p);
                    }
                    else if(p.est_deplacable(E,getAbs(),getOrd())) sauv.add(p);
                }
            }

            System.out.println(sauv);
            Piece capturee = null;
            /*Si il existe une pièce qui met en danger le roi*/
            if(!(sauv.isEmpty()))
            {
                for(Piece p1 : sauv) {
                    /*Vérification qu'aucune pièce adverse ne peut la manger*/
                    for (Piece p : E.getListe()) {
                        if ((p != p1) && (p.getCoul() != p1.getCoul())) {
                            if (p instanceof Pion) {
                                if (((Pion)p).est_mangeable(E, p1.getAbs(), p1.getOrd())) {

                                    char abs = p.getAbs(); int ord = p.getOrd();
                                    char abs1 = p1.getAbs(); int ord1 = p1.getOrd();
                                    p.modif_pos(p1.getAbs(),p1.getOrd());/*manger la pièce mettant en danger*/
                                    p1.modif_pos('i',2);/*placer provisoirement la pièce mangée à une pos impossible*/
                                    if(!echec(E))/*tester s'il y a échec après ces déplacements*/
                                    {
                                        p.modif_pos(abs,ord);/*revenir à la position initiale*/
                                        p1.modif_pos(abs1,ord1);/*revenir à la position initiale*/
                                        return false;
                                    }
                                    p.modif_pos(abs,ord);/*revenir à la position initiale*/
                                    p1.modif_pos(abs1,ord1);/*revenir à la position initiale*/
                                }
                            } else if (p.est_deplacable(E, p1.getAbs(), p1.getOrd()))
                            {
                                char abs = p.getAbs(); int ord = p.getOrd();
                                char abs1 = p1.getAbs(); int ord1 = p1.getOrd();
                                p.modif_pos(p1.getAbs(),p1.getOrd());/*manger la pièce mettant en danger*/
                                p1.modif_pos('i',2);/*placer provisoirement la pièce mangée à une pos impossible*/
                                if(!echec(E))/*tester s'il y a échec après ces déplacements*/
                                {
                                    p.modif_pos(abs,ord);/*revenir à la position initiale*/
                                    p1.modif_pos(abs1,ord1);/*revenir à la position initiale*/
                                    return false;
                                }
                                p.modif_pos(abs,ord);/*revenir à la position initiale*/
                                p1.modif_pos(abs1,ord1);/*revenir à la position initiale*/
                            }
                        }
                    }
                }
            }

            return true;
        }

    }

    /**
     * Méthode pour tester si le roi est en échec et mat
     * @param E, l'échequier.
     * @return Vrai si le roi est en situation d'échec et mat, Faux sinon
     */
    public boolean echec_et_mat(Plateau E)
    {
        if(echec(E) &&
                roi_ne_pas_sortir_pos_echec(E) &&
                aucune_piece_couvre_roi(E) &&
                aucune_piece_mange_piece_mettant_danger(E))
            return true;
        else
            return false;
    }

}


