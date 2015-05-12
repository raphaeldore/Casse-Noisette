#include <QtGui>
#include "AboutDialog.h"

AboutDialog::AboutDialog(QWidget * parent)
	:QDialog(parent)
{
	ui.setupUi(this);
}

void AboutDialog::on_closeBtn_clicked(){
	this->close();
}