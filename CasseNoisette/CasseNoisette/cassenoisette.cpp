#include "cassenoisette.h"
#include <iostream>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QDateTime>

#include "../CrackEngine/Parameter.h"
#include "../CrackEngine/CrackFactoryParams.h"
#include "GenerateDictionaryDialog.h"

// #include "vld.h" // VLD cause des problèmes de null pointer exceptions pour des raisons étranges
                    // quand je charge de très gros fichiers ( > 50Mo)

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

	/// Ce que le crackingWorker émet à son thread (crackingWorkerThread)
	connect(crackingWorker.get(), SIGNAL(finished()), crackingWorkerThread.get(), SLOT(deleteLater()));

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
	crackFactoryParams.addParameter(Parameter(PWD_FILE_PATH, ui.pwdFileSelectTxt->text().toStdString()));
	auto seperator = ui.txtPwdsSeperator->text().isEmpty() ? ":" : ui.txtPwdsSeperator->text().toStdString();
	crackFactoryParams.addParameter(Parameter(SEPERATOR, seperator));
	//crackFactoryParams.addParameter(Parameter(RESULTS_FILE_PATH, ui.resultsFileFolderSelectTxt->text().toStdString()));
	crackFactoryParams.addParameter(Parameter(HASH_TYPE, ui.hashFunctionsComboBox->currentText().toStdString()));

	// Paramètres spécifique 
	if (tabIndex == 0)
	{
		crackFactoryParams.addParameter(Parameter(CHARSET, ui.charsetSelectorWidget->getCharset()));
		crackFactoryParams.addParameter(Parameter(MAX_PWD_LENGTH, ui.spinMaxPwdLenght->text().toStdString()));
		crackingWorker->setCrackEngineType(BRUTE_FORCE);
	} else if (tabIndex == 1)
	{
		crackFactoryParams.addParameter(Parameter(DICTIONARY_PATH, ui.dictFileSelectTxt->text().toStdString()));
		crackingWorker->setCrackEngineType(DICTIONARY);
	} else
	{
		//QMessageBox msgBox("Pas implémenté encore");
		return; // TODO: En attendant d'implémenter le cassage par arc-en-ciel
	}

	
	crackingWorker->setCrackFactoryParameters(crackFactoryParams);

	// On informe à ceux qui écoutent qu'on veut démarrer le cassage
	// Dans notre cas, c'est le crackingWorker qui écoute.
	emit startCracking();
}

void CasseNoisette::on_pwdFileSelectBtn_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(this, "Choisir un fichier contenant des mots de passe", QDir::currentPath(), tr("Password File (*.txt *.pwd)"));
	ui.pwdFileSelectTxt->setText(fileName);
}

void CasseNoisette::on_dictFileSelectBtn_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(this, "Choisir un fichier contenant une liste de mots", QDir::currentPath(), tr("Dictionary File (*.txt *.dict)"));
	ui.dictFileSelectTxt->setText(fileName);
}

void CasseNoisette::handleResults()
{
	ResultDialog resultDialog(this);
	auto results = crackingWorker->getResults();

	QString totalCrackingTime = QString::number(crackingTime->elapsed() * 0.001);

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

void CasseNoisette::errorString(QString error)
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

void CasseNoisette::on_aboutBtn_triggered(){
	AboutDialog aboutDialog(this);

	aboutDialog.exec();
}

void CasseNoisette::on_generateDictionaryBtn_triggered()
{
	GenerateDictionaryDialog generateDictionaryDialog(this);
	generateDictionaryDialog.exec();
}

void CasseNoisette::on_hashFunctionsComboBox_currentIndexChanged(int _newIndex)
{
	// C'est temporaire. Pour l'instant il y a seulement MD5 qui fonctionne.
	if (_newIndex != 0)
	{
		QMessageBox::information(this, "Information", "Cette fonction de hachage n'est pas implémentée.");
		ui.hashFunctionsComboBox->setCurrentIndex(0);
	}
}

void CasseNoisette::closeEvent(QCloseEvent*)
{
	if (crackingInProgress) crackingWorker->exit();
}
