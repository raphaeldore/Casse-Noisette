#include <QtGui>
#include "ResultDialog.h"
#include <QtWidgets/QFileDialog>

using namespace std;

ResultDialog::ResultDialog(QWidget * parent)
	:QDialog(parent)
{
	ui.setupUi(this);

	this->setModal(true);
	this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

void ResultDialog::setInformativeText(const string & informativeText)
{
	ui.informativeTxt->setPlainText(QString::fromStdString(informativeText));
}

void ResultDialog::setCrackingResults(const vector<tuple<string, string, string>> & _results, const QString & _crackingTime)
{
	QString passwords_found_message;
	if (_results.size() == 1)
	{
		passwords_found_message = "1 mot de passe trouvé:\n\n" + resultTupleToString(_results.front());
	}
	else if (_results.size() > 1)
	{
		passwords_found_message = QString::number(_results.size()) + " mots de passe trouvés:\n ";
		for (auto pass : _results)
		{
			passwords_found_message += "\n" + resultTupleToString(pass);
		}
	}
	else
	{
		passwords_found_message = "Aucun mot de passe trouvé";
	}

	passwords_found_message += "\n\nTemps total: " + _crackingTime + " secs";

	ui.resultTxt->setPlainText(passwords_found_message);

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
	QString proposedFileName = QDate::currentDate().toString("'results_'yyyy_MM_dd'.txt");
	QString filename = QFileDialog::getSaveFileName(this, tr("Sauvegarder les résultats"), proposedFileName, tr("Fichiers Textes (*.txt)"));
	QFile f(filename);
	f.open(QIODevice::WriteOnly);
	QTextStream stream(&f);
	stream << ui.resultTxt->toPlainText();
	f.flush();
	f.close();
}

QString ResultDialog::resultTupleToString(const tuple<string, string, string>& _resultTuple) const
{
	QString userName = QString::fromLocal8Bit(get<0>(_resultTuple).c_str());
	QString hashedPassword = QString::fromLocal8Bit(get<1>(_resultTuple).c_str());
	QString plainTextPassword = QString::fromLocal8Bit(get<2>(_resultTuple).c_str());

	return userName + " : " + hashedPassword + " : " + plainTextPassword;
}