#include "cassenoisette.h"
#include <iostream>
#include "../CrackEngine/Parameter.h"
#include "../CrackEngine/CrackFactoryParams.h"
#include "../CrackEngine/CrackFactory.h"

#include <QMessageBox>

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
	using namespace CrackEngine;
	
	ui.tabWidget->currentIndex();

	CrackFactoryParams crackFactoryParams;
	crackFactoryParams.addParameter(Parameter(PWD_FILE_PATH, ui.pwdFileSelectTxt->text().toStdString()));
	crackFactoryParams.addParameter(Parameter(RESULTS_FILE_PATH, "chemin/bidon/fichier_bidon.txt"));
	crackFactoryParams.addParameter(Parameter(CHARSET, "abcdefghijklmnopqrstuvwxyz"));
	crackFactoryParams.addParameter(Parameter(MAX_PWD_LENGTH, ui.spinBox->text().toStdString()));
	// TODO: Remplace la ligne ci-dessous par: crackFactoryParams.addParameter(Parameter(HASH_TYPE, ui.hashFunctionsComboBox->currentText().toStdString()));
	crackFactoryParams.addParameter(Parameter(HASH_TYPE, "MD5"));

	unique_ptr<ICrackEngine> crackEngine;

	QMessageBox errorBox;
	errorBox.setText("Il y a eut une erreur avec vos choix");

	try
	{
		crackEngine = CrackFactory::GetCrackFactory()->CreateCrackEngine(BRUTE_FORCE, crackFactoryParams);
	} catch (const runtime_error & err)
	{
		cerr << err.what();
		errorBox.exec();		
	} catch(const exception & ex)
	{
		cerr << ex.what();
		errorBox.exec();
	}

	ui.startCrackBtn->setEnabled(false);

	crackEngine->Crack();

	ui.startCrackBtn->setEnabled(true);

	QString passwords("Mots de passe trouvés:");

	for (auto pass : crackEngine->getResults())
	{
		passwords += "\n";
		passwords += QString(pass.c_str());
	}

	QMessageBox msgBox;
	QString message("Le cassage des mots de passe est terminé!");
	msgBox.setText(passwords);
	msgBox.exec();
}

void CasseNoisette::on_pwdFileSelectBtn_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(this, "Choisir un fichier contenant des mots de passe", QDir::currentPath(), tr("Password File (*.txt *.pwd)"));
	ui.pwdFileSelectTxt->setText(fileName);
}