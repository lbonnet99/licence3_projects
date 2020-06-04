import javax.swing.JFrame;

public class Fenetre extends JFrame{

    private Echequier e;

    public Fenetre()
    {

        this.setTitle("Echequier");
        this.setSize(600,600);
        this.setLocationRelativeTo(null);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        e = new Echequier();
        this.setContentPane(e);
    }

}
