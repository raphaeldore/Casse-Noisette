#include "PasswordGeneratorDialog.h"

#include "../Utilities/PasswordGenerator.h"

#include <QtWidgets/QMessageBox>

PasswordGeneratorDialog::PasswordGeneratorDialog(QWidget * parent) : QDialog(parent)
{
	ui.setupUi(this);
	this->setModal(true);
	this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

	// Options sélectionnées par défaut
	ui.charsetSelectorWidget->getUi().chkCharsetUpper->setCheckState(Qt::Checked);
	ui.charsetSelectorWidget->getUi().chkCharsetLower->setCheckState(Qt::Checked);
	ui.charsetSelectorWidget->getUi().chkCharsetNumeric->setCheckState(Qt::Checked);
}


PasswordGeneratorDialog::~PasswordGeneratorDialog()
{
}

void PasswordGeneratorDialog::on_btnGeneratePwd_clicked()
{
	int pwdLenght = ui.spinPwdLength->value();
	std::string charset = ui.charsetSelectorWidget->getCharset();
	
	if (charset.empty())
	{
		QMessageBox msgBox;
		msgBox.setIcon(QMessageBox::Critical);
		msgBox.setText("Vous n'avez pas choisi les caractères du mot de passe");
		msgBox.exec();
		return;
	}

	std::string generatedPassword = PasswordGenerator::GeneratePassword(charset, pwdLenght);

	ui.txtGeneratedPwd->setText(QString::fromLocal8Bit(generatedPassword.c_str()));
	ui.txtGeneratedPwd->selectAll();
}

void PasswordGeneratorDialog::on_btnCloseDialog_clicked()
{
	this->close();
}

void PasswordGeneratorDialog::on_txtGeneratedPwd_selectionChanged()
{
	ui.txtGeneratedPwd->copy();
}