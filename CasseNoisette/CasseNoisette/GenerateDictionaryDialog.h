#pragma once

#include <QtWidgets/QDialog>
#include "ui_GenerateDictionaryDialog.h"
#include <memory>
#include <QThread>
#include "GenerateDictionaryWorker.h"

class GenerateDictionaryDialog :
	public QDialog
{
	Q_OBJECT
	std::unique_ptr<QThread> generateDictionaryWorkerThread;
	std::unique_ptr<GenerateDictionaryWorker> generateDictionaryWorker;
public:
	GenerateDictionaryDialog(QWidget * parent = 0);
	~GenerateDictionaryDialog();
public slots:
	void on_btnGenerateDictionary_clicked();
	void on_btnCloseDialog_clicked();
	void on_btnDictionaryFileName_clicked();
	void on_spinMaxCombinationLength_valueChanged();
	void generationStarted();
	void generationFinished();
	void errorString(QString error);
signals:
	void generateDictionary();

private:
	bool AllInputsValid();

	Ui::GenerateDictionaryDialog ui;
	bool ignoreFutureWarnings = false;
};

