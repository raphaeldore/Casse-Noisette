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
private:
	Ui::GenerateDictionaryDialog ui;
};

