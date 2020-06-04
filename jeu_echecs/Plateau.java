import java.util.ArrayList;

public class Plateau {

    private ArrayList<Piece> LP;
    private Undo undo;

    /**Constructeur de la classe Plateau
     * Création d'une liste de pièce.
     * Création d'une pile pour le Undo.
     */
    public Plateau() {
        LP = new ArrayList<Piece>();
        undo = new Undo(new Pile());
    }

    /**Méthode d'ajout dans la liste de pièces
     *
     * @param p, la pièce à ajouter.
     */
    public void add_elem(Piece p)
    {
        LP.add(p);
    }

    /**Méthode de supression dans la liste de pièces
     *
     * @param p, la pièce à retirer.
     */
    public void sup_elem(Piece p)
    {
        LP.remove(p);
    }

    /**Méthode d'initialisation de l'échiquier
     * Ajout de toutes les pièces de départ dans la liste.
     */
    public void init_plateau()
    {

        //Ajout des pièces blanches
        add_elem(new Pion(0,'a',2));
        add_elem(new Pion(0,'b',2));
        add_elem(new Pion(0,'c',2));
        add_elem(new Pion(0,'d',2));
        add_elem(new Pion(0,'e',2));
        add_elem(new Pion(0,'f',2));
        add_elem(new Pion(0,'g',2));
        add_elem(new Pion(0,'h',2));
        add_elem(new Roi(0,'e',1));
        add_elem(new Reine(0,'d',1));
        add_elem(new Fou(0,'c',1));
        add_elem(new Fou(0,'f',1));
        add_elem(new Cavalier(0,'b',1));
        add_elem(new Cavalier(0,'g',1));
        add_elem(new Tour(0,'a',1));
        add_elem(new Tour(0,'h',1));

        //Ajout des pièces noires
        add_elem(new Pion(1,'a',7));
        add_elem(new Pion(1,'b',7));
        add_elem(new Pion(1,'c',7));
        add_elem(new Pion(1,'d',7));
        add_elem(new Pion(1,'e',7));
        add_elem(new Pion(1,'f',7));
        add_elem(new Pion(1,'g',7));
        add_elem(new Pion(1,'h',7));
        add_elem(new Roi(1,'e',8));
        add_elem(new Reine(1,'d',8));
        add_elem(new Fou(1,'c',8));
        add_elem(new Fou(1,'f',8));
        add_elem(new Cavalier(1,'b',8));
        add_elem(new Cavalier(1,'g',8));
        add_elem(new Tour(1,'a',8));
        add_elem(new Tour(1,'h',8));

    }

    /**Méthode de récupération de la liste de pièces
     *
     * @return la liste de pièces.
     */
    public ArrayList<Piece> getListe()
    {
        return LP;
    }

    /**Méthode de récupération de la pile de sauvegarde
     *
     * @return la pile de sauvegarde des mouvements.
     */
    public Undo getUndo()
    {
        return undo;
    }
}
