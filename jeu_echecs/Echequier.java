import java.awt.Graphics;
import java.awt.Image;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;
import javax.swing.JPanel;

public class Echequier extends JPanel{

    protected void paintComponent(Graphics g)
    {

        int x1,x2,y1,y2;
        int Long = this.getWidth();
        int larg = this.getHeight();

        //Quadrillage
        for(int i=0;i<8;i++)
        {
            x1 = i*(Long/8); y1 = 0;
            x2 = x1; y2 = larg;
            g.drawLine(x1, y1, x2, y2);

            x1 = 0; y1 = i*(larg/8);
            x2 = Long; y2 = y1;
            g.drawLine(x1, y1, x2, y2);
        }

        //Mise en noir : Colonne impair
        for(int i = 0;i<8;i=i+2)
        {
            x1 = i*(Long/8);

            for(int j=1;j<8;j=j+2)
            {
                y1 = j*(larg/8);
                g.fillRect(x1, y1,(Long/8),(larg/8));
            }
        }

        //Mise en noir : Colonne pair
        for(int i = 1;i<8;i=i+2)
        {
            x1 = i*(Long/8);

            for(int j=0;j<8;j=j+2)
            {
                y1 = j*(larg/8);
                g.fillRect(x1, y1,(Long/8),(larg/8));
            }
        }

        //Affichage des pièces
        //Affichage des pièces blanches
        try {
            Image tourB1 = ImageIO.read(new File("/home/lauriane/eclipse-workspace/Projet/image/TourN.png"));
            g.drawImage(tourB1,50/4,500,this);

            Image tourB2 = ImageIO.read(new File("/home/lauriane/eclipse-workspace/Projet/image/TourN.png"));
            g.drawImage(tourB2,(50/4)*45,500,this);
        }
        catch (IOException e) {
            e.printStackTrace();
        }

    }

}
