#include <QApplication>
#include "tableau_bord.hh"



int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	tableau_bord tableau;
  tableau.dessin_system();
 
  QGraphicsView system(&tableau.get_system());
	system.show();
	
  tableau.show();
  


	return app.exec();
}
