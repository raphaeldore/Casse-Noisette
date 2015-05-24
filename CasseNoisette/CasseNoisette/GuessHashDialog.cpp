#include "GuessHashDialog.h"

using namespace std;

GuessHashDialog::GuessHashDialog(QWidget* parent) : QDialog(parent)
{
	ui.setupUi(this);
	this->setModal(true);
	this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

GuessHashDialog::~GuessHashDialog()
{
}