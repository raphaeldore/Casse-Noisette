#ifndef CASSENOISETTE_H
#define CASSENOISETTE_H

#include <QtWidgets/QMainWindow>
#include <QThread>
#include <QFileDialog>
#include "ui_cassenoisette.h"
//#include "../CrackEngine/ICrackEngine.h"
#include <memory>
#include "CrackingWorker.h"

class CasseNoisette : public QMainWindow
{
	Q_OBJECT
	QThread crackingWorkerThread;
	CrackingWorker * crackingWorker;
public:
	CasseNoisette(QWidget *parent = 0);
	~CasseNoisette();
public slots:
	void on_startCrackBtn_clicked();
	void on_pwdFileSelectBtn_clicked();
	void handleResults(std::vector<std::string> _results);
signals:
	//void operateCrackingWorker(std::unique_ptr<CrackEngine::ICrackEngine> _crackEngine);
private:
	Ui::CasseNoisetteClass ui;
};

#endif // CASSENOISETTE_H
