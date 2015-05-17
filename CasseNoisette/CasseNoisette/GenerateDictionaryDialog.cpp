#include "GenerateDictionaryDialog.h"

#include "GenerateDictionaryWorker.h"

#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <QThread>

GenerateDictionaryDialog::GenerateDictionaryDialog(QWidget * parent) : QDialog(parent)
{
	ui.setupUi(this);
	this->setModal(true);
	this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
	
	generateDictionaryWorkerThread = std::make_unique<QThread>();
	generateDictionaryWorker = std::make_unique<GenerateDictionaryWorker>();

	generateDictionaryWorker->moveToThread(generateDictionaryWorkerThread.get());

	// Ce que cette classe émet au generateDictionaryWorker
	connect(this, SIGNAL(generateDictionary()), generateDictionaryWorker.get(), SLOT(startGeneration()));

	// Ce que le generateDictionaryWorker émet à cette clase
	connect(generateDictionaryWorker.get(), SIGNAL(generationStarted()), this, SLOT(generationStarted()));
	connect(generateDictionaryWorker.get(), SIGNAL(generationFinished()), this, SLOT(generationFinished()));
	connect(generateDictionaryWorker.get(), SIGNAL(error(QString)), this, SLOT(errorString(QString)));

	// Ce que le generateDictionaryWorkerThread émet à lui-même
	connect(generateDictionaryWorkerThread.get(), SIGNAL(finished()), generateDictionaryWorkerThread.get(), SLOT(deleteLater()));

	generateDictionaryWorkerThread->start(QThread::HighPriority);
}


GenerateDictionaryDialog::~GenerateDictionaryDialog()
{
}

void GenerateDictionaryDialog::on_btnGenerateDictionary_clicked()
{
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

	generateDictionaryWorker->setGenerationParameters(maxCombinationLength, charset, dictionaryPath);

	emit generateDictionary();
	
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

void GenerateDictionaryDialog::generationStarted()
{
	ui.btnGenerateDictionary->setDisabled(true);
	ui.btnCloseDialog->setDisabled(true);
}

void GenerateDictionaryDialog::generationFinished()
{
	ui.btnGenerateDictionary->setDisabled(false);
	ui.btnCloseDialog->setDisabled(false);
	QMessageBox msgBox;
	msgBox.setText("Génération terminée!");
	msgBox.exec();
}

void GenerateDictionaryDialog::errorString(QString error)
{
	QMessageBox msgBox;
	msgBox.setIcon(QMessageBox::Critical);
	msgBox.setText(error);
	msgBox.exec();
}

bool GenerateDictionaryDialog::AllInputsValid()
{
	return !ui.charsetSelectorWidget->getCharset().empty()
		   && !ui.txtDictionaryFileName->text().isEmpty();
}