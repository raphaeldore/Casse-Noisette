#include "cassenoisette.h"

#include "../CrackEngine/Parameter.h"
#include "../CrackEngine/CrackFactoryParams.h"
#include "../CrackEngine/CrackFactory.h"

#include "CrackingWorker.h"
#include "ResultDialog.h"
#include "AboutDialog.h"
#include "GenerateDictionaryDialog.h"
#include "HaveIBeenPwnedDialog.h"
#include "PasswordGeneratorDialog.h"
#include "../Utilities/GuessHash.h"

#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QThread>
#include <QElapsedTimer>


// #include "vld.h" // VLD cause des problèmes de null pointer exceptions pour des raisons étranges
                    // quand je charge de très gros fichiers ( > 50Mo)

using namespace std;

CasseNoisette::CasseNoisette(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
	crackingTime = make_unique<QElapsedTimer>();

	crackingInProgress = false;

	// On instancie un crackingWorker inactif (par défaut)
	crackingWorker = make_unique<CrackingWorker>();
	crackingWorkerThread = make_unique<QThread>();

	// crackingWorker passe du main thread à son propre thread.
	// (alors il ne bloquera pas l'interface)
	crackingWorker->moveToThread(crackingWorkerThread.get());

	
	// On configure les différentes connections (Patron observer de QT):

	/// Ce que cette classe (CasseNoisette) émet au crackingWorker.
	connect(this, SIGNAL(startCracking()), crackingWorker.get(), SLOT(startCracking()));
	connect(this, SIGNAL(stopCracking()), crackingWorker.get(), SLOT(stopCracking()));

	/// Ce que le crackingWorker émet à cette classe (CasseNoisette)
	connect(crackingWorker.get(), &CrackingWorker::resultsReady, this, &CasseNoisette::handleResults);
	connect(crackingWorker.get(), SIGNAL(error(QString)), this, SLOT(errorString(QString)));
	connect(crackingWorker.get(), SIGNAL(running()), this, SLOT(crackingStarted()));
	connect(crackingWorker.get(), SIGNAL(stopped()), this, SLOT(crackingStopped()));
	connect(crackingWorker.get(), SIGNAL(creatingEngine()), this, SLOT(engineInCreation()));
	connect(crackingWorker.get(), SIGNAL(engineCreated()), this, SLOT(engineReady()));
	connect(crackingWorker.get(), SIGNAL(unloadingEngine()), this, SLOT(engineUnloading()));

	/// Ce que le crackingWorkerThread émet à lui-même
	connect(crackingWorkerThread.get(), SIGNAL(finished()), crackingWorkerThread.get(), SLOT(deleteLater()));

	// On démarre le thread. (En stand-by car crackingWorker est inactif par défaut).
	crackingWorkerThread->start(QThread::HighPriority);
}

CasseNoisette::~CasseNoisette()
{
}

void CasseNoisette::closeEvent(QCloseEvent*)
{
	if (crackingInProgress) crackingWorker->exit();
}

void CasseNoisette::on_startCrackBtn_clicked()
{
	if (crackingInProgress) {
		// On informe à ceux qui écoutent qu'on veut arrêter le cassage
		// Dans notre cas, c'est le crackingWorker qui écoute.
		crackingWorker->stopCracking();
		emit stopCracking();
		return;
	}

	using namespace CrackEngine;

	// Si currentIndex == 0 : BruteForce
	// Si == 1 : Dictionnaire
	// Si == 2 : Table arc-en-ciel
	int tabIndex = ui.tabWidget->currentIndex();
	CrackFactoryParams crackFactoryParams;

	// Paramètres universels
	crackFactoryParams.addParameter(Parameter(PWD_FILE_PATH, ui.pwdFileSelectTxt->text().toLocal8Bit().constData()));
	auto seperator = ui.txtPwdsSeperator->text().isEmpty() ? ":" : ui.txtPwdsSeperator->text().toLocal8Bit().constData();
	crackFactoryParams.addParameter(Parameter(SEPERATOR, seperator));
	crackFactoryParams.addParameter(Parameter(HASH_TYPE, ui.hashFunctionsComboBox->currentText().toStdString()));

	// Paramètres spécifique 
	if (tabIndex == 0)
	{
		crackFactoryParams.addParameter(Parameter(CHARSET, ui.charsetSelectorWidget->getCharset()));
		crackFactoryParams.addParameter(Parameter(MAX_PWD_LENGTH, ui.spinMaxPwdLenght->text().toStdString()));
		crackingWorker->setCrackEngineType(BRUTE_FORCE);
	} else if (tabIndex == 1)
	{
		crackFactoryParams.addParameter(Parameter(DICTIONARY_PATH, ui.dictFileSelectTxt->text().toLocal8Bit().constData()));
		crackingWorker->setCrackEngineType(DICTIONARY);
	} else
	{
		// TODO: En attendant d'implémenter le cassage par arc-en-ciel
		QMessageBox::information(this, tr("Casse-Noisette"), tr("Cette section n'est malheureusement pas implémentée encore :("));
		return;
	}

	
	crackingWorker->setCrackFactoryParameters(crackFactoryParams);

	// On informe à ceux qui écoutent qu'on veut démarrer le cassage
	// Dans notre cas, c'est le crackingWorker qui écoute.
	emit startCracking();
}

void CasseNoisette::on_pwdFileSelectBtn_clicked()
{
	QString selectedPwdsFile = QFileDialog::getOpenFileName(this, "Choisir un fichier contenant des mots de passe", "", tr("Password File (*.txt *.pwd)"));

	if (!selectedPwdsFile.isEmpty()) {
		ui.pwdFileSelectTxt->setText(selectedPwdsFile);
	}
}

void CasseNoisette::on_dictFileSelectBtn_clicked()
{
	QDir dir;
	if (!ui.pwdFileSelectTxt->text().isEmpty())
	{
		// Ici on assume que le dictionnaire se situe dans le même dossier
		// que les mots de passe. Si ce n'est pas le cas ce n'est pas grave,
		// mais si c'est le cas, l'utilisateur n'a pas à recommencer le processus
		// de sélection de fichier (puisqu'il est déjà dans le bon dossier!).
		// Ce sont les détails qui comptent :D
		dir = QFileInfo(ui.pwdFileSelectTxt->text()).absoluteDir();
	}

	QString fileName = QFileDialog::getOpenFileName(this, "Choisir un fichier contenant une liste de mots", dir.absolutePath(), tr("Dictionary File (*.txt *.dict)"));
	ui.dictFileSelectTxt->setText(fileName);
}

void CasseNoisette::on_aboutBtn_triggered(){
	AboutDialog aboutDialog(this);
	aboutDialog.exec();
}

void CasseNoisette::on_generateDictionaryBtn_triggered()
{
	GenerateDictionaryDialog generateDictionaryDialog(this);
	generateDictionaryDialog.exec();
}

void CasseNoisette::on_actionQuitter_triggered()
{
	this->close();
}

void CasseNoisette::on_actionHaveIBeenPwned_triggered()
{
	HaveIBeenPwnedDialog haveIBeenPwnedDialog(this);
	haveIBeenPwnedDialog.exec();
}

void CasseNoisette::on_actionPwdGenerator_triggered()
{
	PasswordGeneratorDialog passwordGeneratorDialog(this);
	passwordGeneratorDialog.exec();
}

void CasseNoisette::on_GuessHashCheckBox_toggled(bool _toggledState)
{
	if (_toggledState)
	{
		bool ok = false;
		QString hashSample = QInputDialog::getText(this, tr("Deviner le hash"), "Échantillon de hash :", QLineEdit::Normal, "", &ok);

		// Si l'utilisateur a cliqué sur le bouton "Cancel"
		if (!ok)
		{
			ui.GuessHashCheckBox->setCheckState(Qt::Unchecked);
			return;
		}

		string hashGuess;
		if (Utilities::GuessHash::Guess(hashSample.toLocal8Bit().constData(), hashGuess))
		{
			QString qhashGuess = QString::fromLocal8Bit(hashGuess.c_str());
			ui.hashFunctionsComboBox->setCurrentIndex(ui.hashFunctionsComboBox->findText(qhashGuess));
			QMessageBox::information(this, "Casse-Noisette", "La fonction de hachage est " + qhashGuess);
		}
		else
		{
			ui.hashFunctionsComboBox->setCurrentIndex(0);
			QMessageBox::warning(this, "Casse-Noisette", "Impossible d'identifier cet échantillon de hash");
		}
	}
}

void CasseNoisette::handleResults()
{
	// On va chercher les résultats et le temps que ça a pris
	auto results = crackingWorker->getResults();
	QString totalCrackingTime = QString::number(crackingTime->elapsed() * 0.001);
	
	// On donne ensuite les résultats au ResultDialog pour que celui-ci 
	// puisse préparer les résultats pour les afficher à l'utilisateur.
	ResultDialog resultDialog(this);
	resultDialog.setCrackingResults(results, totalCrackingTime);
	resultDialog.setInformativeText("Le cassage des mots de passe est terminé! \n\nAppuyez sur le bouton \"Enregistrer\" pour enregistrer les résultats dans un fichier.");
	resultDialog.exec();
}

void CasseNoisette::crackingStarted()
{
	crackingInProgress = true;
	ui.startCrackBtn->setText("Annuler le cassage");
}

void CasseNoisette::crackingStopped()
{
	ui.startCrackBtn->setEnabled(true);
	ui.startCrackBtn->setText("Démarrer le cassage");
	crackingInProgress = false;
}

void CasseNoisette::errorString(const QString & error)
{
	QMessageBox errorBox;
	errorBox.setText(error);
	errorBox.exec();
}

void CasseNoisette::engineInCreation()
{
	crackingTime->restart();
	ui.startCrackBtn->setText("Chargement des fichiers...");
	ui.startCrackBtn->setDisabled(true);
}

void CasseNoisette::engineReady()
{
	ui.startCrackBtn->setDisabled(false);
}

void CasseNoisette::engineUnloading()
{
	ui.startCrackBtn->setText("Déchargement de l'engin...");
	ui.startCrackBtn->setDisabled(true);
}
