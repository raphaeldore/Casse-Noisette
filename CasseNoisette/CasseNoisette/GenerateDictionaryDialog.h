#pragma once

#include "ui_GenerateDictionaryDialog.h"
#include <memory>

class GenerateDictionaryWorker;
class QThread;

class GenerateDictionaryDialog : public QDialog
{
	Q_OBJECT

public:
	GenerateDictionaryDialog(QWidget* parent = 0);
	~GenerateDictionaryDialog();

signals:
	void generateDictionary();

private slots:
	// Actions des contrôles du GUI
	void on_btnGenerateDictionary_clicked();
	void on_btnCloseDialog_clicked();
	void on_btnDictionaryFileName_clicked();
	void on_spinMaxCombinationLength_valueChanged();

	// Réactions face aux signaux de GenerateDictionaryWorker
	void generationStarted();
	void generationFinished();
	void errorString(QString error);

private:
	bool AllInputsValid();

	Ui::GenerateDictionaryDialog ui;
	std::unique_ptr<QThread> generateDictionaryWorkerThread;
	std::unique_ptr<GenerateDictionaryWorker> generateDictionaryWorker;

	bool ignoreFutureWarnings = false;
};

