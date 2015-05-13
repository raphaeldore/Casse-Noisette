#include "cassenoisette.h"
#include <iostream>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QDateTime>

#include "../CrackEngine/Parameter.h"
#include "../CrackEngine/CrackFactoryParams.h"

#include "../CrackEngine/CharsetBuilder.h"

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

QString CasseNoisette::tupleToString(const tuple<string, string, string> & _tupleToConvert) const
{
	QString userName = QString::fromLocal8Bit(get<0>(_tupleToConvert).c_str());
	QString hashedPassword = QString::fromLocal8Bit(get<1>(_tupleToConvert).c_str());
	QString plainTextPassword = QString::fromLocal8Bit(get<2>(_tupleToConvert).c_str());

	return userName + " : " + hashedPassword + " : " + plainTextPassword;
}

string CasseNoisette::GetCharset() const
{
	CharsetBuilder charsetBuilder {
		ui.chkCharsetLower->isChecked(),
		ui.chkCharsetUpper->isChecked(),
		ui.chkCharsetNumeric->isChecked(),
		ui.chkCharsetSpace->isChecked(),
		ui.chkCharsetSpecial->isChecked(),
		ui.txtCustomCharset->text().toLocal8Bit().constData() // Les QString sont en UTF-16, 
		                                                      // et les std::string sont en UTF-8.
		                                                      // On doit les convertir.
	};

	return charsetBuilder.BuildCharset();
}

bool CasseNoisette::SaveResults(const QString& _contents)
{
	QString proposedFileName = QDate::currentDate().toString("'results_'dd_MM_yyyy'.txt'");
	QString filename = QFileDialog::getSaveFileName(this, tr("Sauvegarder les résultats"), proposedFileName, tr("Fichiers Textes (*.txt)"));
	QFile f(filename);
	f.open(QIODevice::WriteOnly);
	QTextStream stream(&f);
	stream << _contents;
	auto flushStatus = f.flush();
	f.close();

	return flushStatus;
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
		crackFactoryParams.addParameter(Parameter(CHARSET, GetCharset()));
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
	QMessageBox msgBox;
	msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Ok);
	QString passwords_found_message;
	auto results = crackingWorker->getResults();

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
		msgBox.setInformativeText("Essayez avec d'autres paramètres.");
	}

	passwords_found_message += "\n\nTemps total: " + QString::number(crackingTime->elapsed() * 0.001) + " secs";

	msgBox.setText("Le cassage des mots de passe est terminé!");
	msgBox.setInformativeText("Appuyez sur le bouton \"Show Details\" pour afficher les résultats");
	msgBox.setDetailedText(passwords_found_message);

	// La grosseur de QMessageBox
	QSpacerItem* horizontalSpacer = new QSpacerItem(500, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
	QGridLayout* layout = static_cast<QGridLayout*>(msgBox.layout());
	layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());

	int ret = msgBox.exec();

	switch (ret)
	{
	case QMessageBox::Save:
		SaveResults(passwords_found_message);
		break;
	}
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