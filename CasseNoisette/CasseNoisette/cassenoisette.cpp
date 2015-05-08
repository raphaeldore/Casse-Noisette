#include "cassenoisette.h"
#include <iostream>
#include <QMessageBox>
#include <QFileDialog>

#include "../CrackEngine/Parameter.h"
#include "../CrackEngine/CrackFactoryParams.h"

#include "vld.h"

CasseNoisette::CasseNoisette(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
	crackingTime = new QElapsedTimer;

	crackingInProgress = false;

	// On instancie un crackingWorker inactif (par défaut)
	crackingWorker = new CrackingWorker;
	crackingWorkerThread = new QThread;

	// crackingWorker passe du main thread à son propre thread.
	// (alors il ne bloquera pas l'interface)
	crackingWorker->moveToThread(crackingWorkerThread);

	
	// On configure les différentes connections (Patron observer de QT):

	/// Ce que cette classe (CasseNoisette) émet au crackingWorker.
	connect(this, SIGNAL(startCracking()), crackingWorker, SLOT(startCracking()));
	connect(this, SIGNAL(stopCracking()), crackingWorker, SLOT(stopCracking()));

	/// Ce que le crackingWorker émet à son thread (crackingWorkerThread)
	connect(crackingWorker, SIGNAL(finished()), crackingWorkerThread, SLOT(deleteLater()));

	/// Ce que le crackingWorker émet à cette classe (CasseNoisette)
	connect(crackingWorker, &CrackingWorker::resultsReady, this, &CasseNoisette::handleResults);
	connect(crackingWorker, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
	connect(crackingWorker, SIGNAL(running()), this, SLOT(crackingStarted()));
	connect(crackingWorker, SIGNAL(stopped()), this, SLOT(crackingStopped()));

	/// Ce que le crackingWorkerThread émet à lui-même
	connect(crackingWorkerThread, SIGNAL(finished()), crackingWorkerThread, SLOT(deleteLater()));

	// On démarre le thread. (En stand-by car crackingWorker est inactif par défaut).
	crackingWorkerThread->start(QThread::HighPriority);
}

CasseNoisette::~CasseNoisette()
{
	delete crackingWorkerThread;
	delete crackingWorker;
	delete crackingTime;
}

QString CasseNoisette::tupleToString(const tuple<string, string, string> & _tupleToConvert) const
{
	QString userName = QString::fromLocal8Bit(get<0>(_tupleToConvert).c_str());
	QString hashedPassword = QString::fromLocal8Bit(get<1>(_tupleToConvert).c_str());
	QString plainTextPassword = QString::fromLocal8Bit(get<2>(_tupleToConvert).c_str());

	return userName + " : " + hashedPassword + " : " + plainTextPassword;
}

void CasseNoisette::on_startCrackBtn_clicked()
{
	if (crackingInProgress) {
		// On informe à ceux qui écoutent qu'on veut arrêter le cassage
		// Dans notre cas, c'est le crackingWorker qui écoute.
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
	crackFactoryParams.addParameter(Parameter(RESULTS_FILE_PATH, "chemin/bidon/fichier_bidon.txt"));
	crackFactoryParams.addParameter(Parameter(HASH_TYPE, ui.hashFunctionsComboBox->currentText().toStdString()));

	// Paramètres spécifique 
	if (tabIndex == 0)
	{
		crackFactoryParams.addParameter(Parameter(CHARSET, "abcdefghijklmnopqrstuvwxyz"));
		crackFactoryParams.addParameter(Parameter(MAX_PWD_LENGTH, ui.spinBox->text().toStdString()));
		crackingWorker->setCrackEngineType(BRUTE_FORCE);
	} else
	{
		return; // TODO: En attendant d'implémenter les autres engines
	}

	
	crackingWorker->setCrackFactoryParameters(crackFactoryParams);

	// On informe à ceux qui écoutent qu'on veut démarrer le cassage
	// Dans notre cas, c'est le crackingWorker qui écoute.
	emit startCracking();

	crackingInProgress = true;
	ui.startCrackBtn->setText("Annuler le cassage");
}

void CasseNoisette::on_pwdFileSelectBtn_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(this, "Choisir un fichier contenant des mots de passe", QDir::currentPath(), tr("Password File (*.txt *.pwd)"));
	ui.pwdFileSelectTxt->setText(fileName);
}

void CasseNoisette::handleResults()
{
	QMessageBox msgBox;
	QString passwords_found_message;
	auto results = crackingWorker->getResults();

	crackingTime->elapsed();

	if (results.size() == 1)
	{
		passwords_found_message = "1 mot de passe trouvé:\n\n " + tupleToString(results.front());
	} else if (results.size() > 1)
	{
		passwords_found_message = QString::number(results.size()) + " mots de passe trouvés:\n ";
		for (auto pass : results)
		{
			passwords_found_message += "\n";
			passwords_found_message += tupleToString(pass);
		}
	}
	else
	{
		passwords_found_message = "Aucun mot de passe trouvé";
	}

	passwords_found_message += "\n\n Temps total: " + QString::number(crackingTime->elapsed() * 0.001) + " secs";

	msgBox.setText(passwords_found_message);
	msgBox.exec();
}

void CasseNoisette::crackingStarted()
{
	crackingTime->restart();
}

void CasseNoisette::crackingStopped()
{
	ui.startCrackBtn->setText("Démarrer le cassage");
	crackingInProgress = false;
}

void CasseNoisette::errorString(QString error)
{
	QMessageBox errorBox;
	errorBox.setText(error);
	errorBox.exec();
}