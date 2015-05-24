#include "cassenoisette.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setApplicationName("Casse-Noisette");
	a.setApplicationVersion("1.0");
	CasseNoisette w;
	w.show();
	return a.exec();
}
