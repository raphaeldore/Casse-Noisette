#include "PasswordGeneratorDialog.h"

#include <QtWidgets/QMessageBox>

PasswordGeneratorDialog::PasswordGeneratorDialog(QWidget * parent) : QDialog(parent)
{
	ui.setupUi(this);
	this->setModal(true);
	this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
}


PasswordGeneratorDialog::~PasswordGeneratorDialog()
{
}

void PasswordGeneratorDialog::on_btnGeneratePwd_clicked()
{
	int pwdLenght = ui.spinMaxPwdLength->value();
	std::string charset = ui.charsetSelectorWidget->getCharset();
	
	if (charset.empty())
	{
		QMessageBox msgBox;
		msgBox.setIcon(QMessageBox::Critical);
		msgBox.setText("Vous n'avez pas choisi les caractères du mot de passe");
		msgBox.exec();
		return;
	}
	
}

void PasswordGeneratorDialog::on_btnCloseDialog_clicked()
{
	this->close();
}