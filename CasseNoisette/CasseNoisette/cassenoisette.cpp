#include "cassenoisette.h"
#include <iostream>
#include "../CrackEngine/Parameter.h"
#include "../CrackEngine/CrackFactoryParams.h"

#include <QMessageBox>

//#include <thread>

CasseNoisette::CasseNoisette(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
	crackingTimer = new QTimer;

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
	connect(crackingWorker, SIGNAL(stopped()), this, SLOT(crackingStopped()));

	/// Ce que le crackingWorkerThread émet à lui-même
	connect(crackingWorkerThread, SIGNAL(finished()), crackingWorkerThread, SLOT(deleteLater()));

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
		emit stopCracking();
		return;
	}

	/*
	TODO: Séparer cette méthode en plusieurs méthodes (Pour un autre sprint...Pour l'instant ça fait le travail)
	TODO: Validation de l'entée (Ex: Si aucun fichier choisi on ne devrait pas permettre le cassage).
	*/

	using namespace CrackEngine;

	// Si currentIndex == 0 : BruteForce
	// Si == 1 : Dictionnaire
	// Si == 2 : Table arc-en-ciel
	ui.tabWidget->currentIndex();

	CrackFactoryParams crackFactoryParams;
	crackFactoryParams.addParameter(Parameter(PWD_FILE_PATH, ui.pwdFileSelectTxt->text().toStdString()));
	crackFactoryParams.addParameter(Parameter(RESULTS_FILE_PATH, "chemin/bidon/fichier_bidon.txt"));
	crackFactoryParams.addParameter(Parameter(CHARSET, "abcdefghijklmnopqrstuvwxyz"));
	crackFactoryParams.addParameter(Parameter(MAX_PWD_LENGTH, ui.spinBox->text().toStdString()));
	// TODO: Remplace la ligne ci-dessous par: crackFactoryParams.addParameter(Parameter(HASH_TYPE, ui.hashFunctionsComboBox->currentText().toStdString()));
	crackFactoryParams.addParameter(Parameter(HASH_TYPE, "MD5"));

	crackingWorker->setCrackEngineType(BRUTE_FORCE);
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

	if (results.size() == 1)
	{
		passwords_found_message = "1 mot de passe trouvé:\n\n " + QString(results.at(0).c_str());
	} else if (results.size() > 1)
	{
		passwords_found_message = QString::number(results.size()) + " mots de passe trouvés:\n ";
		for (auto pass : results)
		{
			passwords_found_message += "\n";
			passwords_found_message += QString(pass.c_str());
		}
	}
	else
	{
		passwords_found_message = "Aucun mot de passe trouvé";
	}

	msgBox.setText(passwords_found_message);
	msgBox.exec();
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