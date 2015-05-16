#ifndef CASSENOISETTE_H
#define CASSENOISETTE_H

#include <QtWidgets/QMainWindow>
#include <QThread>
#include "ui_cassenoisette.h"
#include "CrackingWorker.h"
#include <QElapsedTimer>
#include "AboutDialog.h"
#include "ResultDialog.h"
#include "CharsetSelector.h"

class CasseNoisette : public QMainWindow
{
	Q_OBJECT
	unique_ptr<QThread> crackingWorkerThread;
	unique_ptr<CrackingWorker> crackingWorker;
	unique_ptr<QElapsedTimer> crackingTime;

public:
	CasseNoisette(QWidget *parent = 0);
	~CasseNoisette();

public slots:
	void on_startCrackBtn_clicked();
	void on_pwdFileSelectBtn_clicked();
	void on_dictFileSelectBtn_clicked();
	void on_aboutBtn_triggered();
	void on_generateDictionaryBtn_triggered();
	void on_hashFunctionsComboBox_currentIndexChanged(int _newIndex);
	void handleResults();
	void crackingStarted();
	void crackingStopped();
	void errorString(QString error);
	void engineInCreation();
	void engineReady();
	void engineUnloading();
signals:
	void startCracking();
	void stopCracking();
	void error(QString err);
protected:
	void closeEvent(QCloseEvent*);
private:
	Ui::CasseNoisetteClass ui;
	bool crackingInProgress;
	QWidget * charsetSelector;
};

#endif // CASSENOISETTE_H
