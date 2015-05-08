#ifndef CASSENOISETTE_H
#define CASSENOISETTE_H

#include <QtWidgets/QMainWindow>
#include <QThread>
#include "ui_cassenoisette.h"
#include "CrackingWorker.h"
#include <QElapsedTimer>

class CasseNoisette : public QMainWindow
{
	Q_OBJECT
	QThread * crackingWorkerThread;
	CrackingWorker * crackingWorker;
	QElapsedTimer * crackingTime;

public:
	CasseNoisette(QWidget *parent = 0);
	~CasseNoisette();

public slots:
	void on_startCrackBtn_clicked();
	void on_pwdFileSelectBtn_clicked();
	void handleResults();
	void crackingStarted();
	void crackingStopped();
	void errorString(QString error);
signals:
	void startCracking();
	void stopCracking();
	void error(QString err);
private:
	Ui::CasseNoisetteClass ui;
	bool crackingInProgress;
};

#endif // CASSENOISETTE_H
