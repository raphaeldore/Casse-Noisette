#include "cassenoisette.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CasseNoisette w;
	w.show();
	return a.exec();
}
