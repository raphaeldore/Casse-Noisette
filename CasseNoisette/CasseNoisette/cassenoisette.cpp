#include "cassenoisette.h"
#include <iostream>
#include "../CrackEngine/Parameter.h"
#include "../CrackEngine/CrackFactoryParams.h"
//#include "../CrackEngine/CrackFactory.h"

#include <QMessageBox>

//#include "CrackingWorker.h"

#include <thread>

CasseNoisette::CasseNoisette(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

CasseNoisette::~CasseNoisette()
{
}

void CasseNoisette::on_startCrackBtn_clicked()
{
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
	//unique_ptr<ICrackEngine> crackEngine;

	QMessageBox errorBox;
	QString errorText = "Il y a eut une erreur avec vos choix:\n";

	//try
	//{
	//	crackEngine = CrackFactory::GetCrackFactory()->CreateCrackEngine(BRUTE_FORCE, crackFactoryParams);
	//}
	//catch (const runtime_error & err)
	//{
	//	cerr << err.what();
	//	errorBox.setText(errorText + QString(err.what()));
	//	errorBox.exec();
	//}
	//catch (const exception & ex)
	//{
	//	cerr << ex.what();
	//	errorBox.setText(errorText + QString(ex.what()));
	//	errorBox.exec();
	//}

	//CrackingWorker * crackingWorker = new CrackingWorker(BRUTE_FORCE, crackFactoryParams);
	//crackingWorker->moveToThread(&crackingWorkerThread);
	//connect(&crackingWorkerThread, &QThread::finished, crackingWorker, &QObject::deleteLater);
	//connect(this, &CasseNoisette::operateCrackingWorker, crackingWorker, &CrackingWorker::startCracking);
	//connect(crackingWorker, &CrackingWorker::resultsReady, this, &CasseNoisette::handleResults);
	//crackingWorkerThread.start(QThread::HighPriority);

	/*CrackingWorker * crackingWorker = new CrackingWorker(BRUTE_FORCE, crackFactoryParams);
	crackingWorker->moveToThread(&crackingWorkerThread);
	connect(&crackingWorkerThread, &QThread::finished, crackingWorker, &QObject::deleteLater);
	connect(this, &CasseNoisette::operateCrackingWorker, crackingWorker, &CrackingWorker::startCracking);
	connect(crackingWorker, &CrackingWorker::resultsReady, this, &CasseNoisette::handleResults);
	crackingWorkerThread.start(QThread::HighPriority);*/


	//CrackingWorker * crackingWorker = new CrackingWorker(BRUTE_FORCE, crackFactoryParams);
	crackingWorker = new CrackingWorker(BRUTE_FORCE, crackFactoryParams);
	crackingWorker->moveToThread(&crackingWorkerThread);
	//connect(crackingWorker, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
	connect(&crackingWorkerThread, SIGNAL(started()), crackingWorker, SLOT(startCracking()));
	connect(crackingWorker, SIGNAL(finished()), &crackingWorkerThread, SLOT(quit()));
	connect(crackingWorker, SIGNAL(finished()), &crackingWorkerThread, SLOT(deleteLater()));
	connect(&crackingWorkerThread, SIGNAL(finished()), &crackingWorkerThread, SLOT(deleteLater()));
	crackingWorkerThread.start(QThread::HighPriority);




	/*
	
	QThread* thread = new QThread;
Worker* worker = new Worker();
worker->moveToThread(thread);
connect(worker, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
connect(thread, SIGNAL(started()), worker, SLOT(process()));
connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
thread->start();
	*/

	/*
	
	connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
        connect(this, &Controller::operate, worker, &Worker::doWork);
        connect(worker, &Worker::resultReady, this, &Controller::handleResults);
        workerThread.start();
	*/

	//ui.startCrackBtn->setEnabled(false);
	//crackEngine->Crack(); // TODO: Démarrer ça dans un autre thread. Car pour l'instant ça bloque l'application.
	//ui.startCrackBtn->setEnabled(true);

	//QString passwords_found_message;

	//auto results = crackEngine->getResults();

	//if (results.size() > 0)
	//{
	//	passwords_found_message = QString::number(results.size()) + " mot(s) de passe trouvé(s):\n ";
	//	for (auto pass : results)
	//	{
	//		passwords_found_message += "\n";
	//		passwords_found_message += QString(pass.c_str());
	//	}
	//}
	//else
	//{
	//	passwords_found_message = "Aucun mot de passe trouvé";
	//}

	//QMessageBox msgBox;
	//msgBox.setText(passwords_found_message);
	//msgBox.exec();
}

void CasseNoisette::on_pwdFileSelectBtn_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(this, "Choisir un fichier contenant des mots de passe", QDir::currentPath(), tr("Password File (*.txt *.pwd)"));
	ui.pwdFileSelectTxt->setText(fileName);
}

void CasseNoisette::handleResults(vector<string> _results)
{
	QString passwords_found_message;
	auto results = crackingWorker->getResults();

	if (results.size() > 0)
	{
		passwords_found_message = QString::number(results.size()) + " mot(s) de passe trouvé(s):\n ";
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

	QMessageBox msgBox;
	msgBox.setText(passwords_found_message);
	msgBox.exec();
}