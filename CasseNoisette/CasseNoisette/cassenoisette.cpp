#include "cassenoisette.h"
#include <iostream>

CasseNoisette::CasseNoisette(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

CasseNoisette::~CasseNoisette()
{

}

void CasseNoisette::on_pwdFileSelectBtn_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(this, "", "/", "*.txt");
	ui.pwdFileSelectTxt->setText(fileName);
}