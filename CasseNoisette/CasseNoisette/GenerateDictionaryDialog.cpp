#include "GenerateDictionaryDialog.h"
#include "../Utilities/DictionaryGenerator.h"
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>

GenerateDictionaryDialog::GenerateDictionaryDialog(QWidget * parent) : QDialog(parent)
{
	ui.setupUi(this);
	this->setModal(true);
	this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
}


GenerateDictionaryDialog::~GenerateDictionaryDialog()
{
}

void GenerateDictionaryDialog::on_btnGenerateDictionary_clicked()
{
	using namespace Utilities;

	QMessageBox msgBox;
	if (!AllInputsValid())
	{
		msgBox.setIcon(QMessageBox::Critical);
		msgBox.setText("Vous n'avez pas remplis tous les champs");
		msgBox.exec();
		return;
	}

	int maxCombinationLength = ui.spinMaxCombinationLength->value();
	std::string charset = ui.charsetSelectorWidget->getCharset();
	std::string dictionaryPath = ui.txtDictionaryFileName->text().toLocal8Bit().constData();

	try
	{
		DictionaryGenerator generator(maxCombinationLength, charset, dictionaryPath);
		ui.btnGenerateDictionary->setDisabled(true);
		generator.GenerateDictionary();
		msgBox.setText("Génération terminé!");
		msgBox.exec();
		ui.btnGenerateDictionary->setDisabled(false);
	} catch (const std::exception & ex)
	{
		msgBox.setIcon(QMessageBox::Critical);
		msgBox.setText(ex.what());
		msgBox.exec();
		ui.btnGenerateDictionary->setDisabled(false);
		return;
	}
	
}

void GenerateDictionaryDialog::on_btnCloseDialog_clicked()
{
	this->close();
}

void GenerateDictionaryDialog::on_btnDictionaryFileName_clicked()
{
	QString filename = QFileDialog::getSaveFileName(this, tr("Sauvegarder les résultats"), QDir::currentPath(), tr("Fichiers Textes (*.txt)"));
	ui.txtDictionaryFileName->setText(filename);
}

void GenerateDictionaryDialog::on_spinMaxCombinationLength_valueChanged()
{
	if (!ignoreFutureWarnings && ui.spinMaxCombinationLength->value() >= 6)
	{
		QMessageBox warningMsgBox;
		QPushButton* yesBtn = warningMsgBox.addButton(tr("Oui"), QMessageBox::YesRole);
		QPushButton* noBtn = warningMsgBox.addButton(tr("Non"), QMessageBox::NoRole);
		QPushButton* ignoreFutureWarningsBtn = warningMsgBox.addButton(tr("Ne plus m'avertir"), QMessageBox::ActionRole);

		warningMsgBox.setIcon(QMessageBox::Warning);
		warningMsgBox.setText("Le dictionnaire qui sera généré fera plusieurs Gigs.\n"
			"Voulez-vous vraiment augmenter la longueur max?");

		warningMsgBox.exec();

		if (warningMsgBox.clickedButton() == noBtn)
		{
			// On ne veut pas que le déclanger l'évènement valueChanged
			bool oldState = ui.spinMaxCombinationLength->blockSignals(true); // On bloque tous les signals
			int newSpinBoxValue = ui.spinMaxCombinationLength->value() - 1;
			ui.spinMaxCombinationLength->setValue(newSpinBoxValue);

			// On réactive les signals pour le spinBox
			ui.spinMaxCombinationLength->blockSignals(oldState);
		}
		else if (warningMsgBox.clickedButton() == ignoreFutureWarningsBtn)
		{
			ignoreFutureWarnings = true;
		}
	}
}

bool GenerateDictionaryDialog::AllInputsValid()
{
	return !ui.charsetSelectorWidget->getCharset().empty()
		   && !ui.txtDictionaryFileName->text().isEmpty();
}