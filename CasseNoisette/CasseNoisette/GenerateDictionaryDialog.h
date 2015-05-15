#pragma once

#include <QtWidgets/QDialog>
#include "ui_GenerateDictionaryDialog.h"

class GenerateDictionaryDialog :
	public QDialog
{
	Q_OBJECT
public:
	GenerateDictionaryDialog(QWidget * parent = 0);
	~GenerateDictionaryDialog();
public slots:
	void on_btnGenerateDictionary_clicked();
	void on_btnCloseDialog_clicked();
	void on_btnDictionaryFileName_clicked();
	void on_spinMaxCombinationLength_valueChanged();
private:
	bool AllInputsValid();

	Ui::GenerateDictionaryDialog ui;
	bool ignoreFutureWarnings = false;
};

