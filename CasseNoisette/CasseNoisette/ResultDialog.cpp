#include <QtGui>
#include "ResultDialog.h"
#include <QtWidgets/QFileDialog>

ResultDialog::ResultDialog(QWidget * parent)
	:QDialog(parent)
{
	ui.setupUi(this);

	this->setModal(true);
	this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

void ResultDialog::setInformativeText(string informativeText)
{
	ui.informativeTxt->setPlainText(QString::fromStdString(informativeText));
}

void ResultDialog::setResultText(QString resultText)
{
	ui.resultTxt->setPlainText(resultText);
}

void ResultDialog::on_closeBtn_clicked(){
	this->close();
}

void ResultDialog::on_saveBtn_clicked()
{
	QString proposedFileName = QDate::currentDate().toString("'results_'dd_MM_yyyy'.txt'");
	QString filename = QFileDialog::getSaveFileName(this, tr("Sauvegarder les résultats"), proposedFileName, tr("Fichiers Textes (*.txt)"));
	QFile f(filename);
	f.open(QIODevice::WriteOnly);
	QTextStream stream(&f);
	stream << ui.resultTxt->toPlainText();
	f.flush();
	f.close();
}