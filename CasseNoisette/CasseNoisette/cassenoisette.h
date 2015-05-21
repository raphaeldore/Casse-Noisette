#ifndef CASSENOISETTE_H
#define CASSENOISETTE_H

#include <QtWidgets/QMainWindow>
#include "ui_cassenoisette.h"
#include <memory>

class CrackingWorker;
class QThread;
class QElapsedTimer;

class CasseNoisette : public QMainWindow
{
	Q_OBJECT

public:
	CasseNoisette(QWidget* parent = 0);
	~CasseNoisette();

signals:
	/* Signaux qu'on envoit au CrackingWorker*/
	void startCracking();
	void stopCracking();

protected:
	void closeEvent(QCloseEvent*) override;

private slots:
	/* Actions de l'interface */
	void on_startCrackBtn_clicked();
	void on_pwdFileSelectBtn_clicked();
	void on_dictFileSelectBtn_clicked();
	void on_aboutBtn_triggered();
	void on_generateDictionaryBtn_triggered();
	void on_actionQuitter_triggered();
	void on_actionHaveIBeenPwned_triggered();
	void on_actionPwdGenerator_triggered();
	void on_hashFunctionsComboBox_currentIndexChanged(int _newIndex);

	/* Méthodes qui réagissent aux signaux de
	CrackingWorker */
	void handleResults();
	void crackingStarted();
	void crackingStopped();
	void errorString(QString error);
	void engineInCreation();
	void engineReady();
	void engineUnloading();

private:
	Ui::CasseNoisetteClass ui;
	std::unique_ptr<QThread> crackingWorkerThread = nullptr;
	std::unique_ptr<CrackingWorker> crackingWorker = nullptr;
	std::unique_ptr<QElapsedTimer> crackingTime = nullptr;

	bool crackingInProgress;
};

#endif // CASSENOISETTE_H
