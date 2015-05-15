#include "GenerateDictionaryDialog.h"


GenerateDictionaryDialog::GenerateDictionaryDialog(QWidget * parent) : QDialog(parent)
{
	ui.setupUi(this);
	this->setModal(true);
	this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
}


GenerateDictionaryDialog::~GenerateDictionaryDialog()
{
}
