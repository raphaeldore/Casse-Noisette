#include <QtGui>
#include "AboutDialog.h"

AboutDialog::AboutDialog(QWidget * parent)
	:QDialog(parent)
{
	ui.setupUi(this);
	this->setModal(true);
	this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

void AboutDialog::on_closeBtn_clicked(){
	this->close();
}