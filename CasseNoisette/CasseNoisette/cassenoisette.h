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
	unique_ptr<QThread> crackingWorkerThread;
	unique_ptr<CrackingWorker> crackingWorker;
	unique_ptr<QElapsedTimer> crackingTime;

public:
	CasseNoisette(QWidget *parent = 0);
	~CasseNoisette();

	QString tupleToString(const tuple<string, string, string> & _tupleToConvert) const;
	string GetCharset() const;
	bool SaveResults(const QString & _contents);

public slots:
	void on_startCrackBtn_clicked();
	void on_pwdFileSelectBtn_clicked();
	void on_dictFileSelectBtn_clicked();
	void on_resultsFileFolderSelectBtn_clicked();
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

private:
	Ui::CasseNoisetteClass ui;
	bool crackingInProgress;
};

#endif // CASSENOISETTE_H
