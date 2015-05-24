#pragma once

#include "ui_GuessHashDialog.h"

class GuessHashDialog : public QDialog
{
	Q_OBJECT

public:
	GuessHashDialog(QWidget* parent = 0);
	~GuessHashDialog();

private slots:

private:
	Ui::GuessHashDialog ui;
};

