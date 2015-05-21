#pragma once

#include "ui_PasswordGeneratorDialog.h"

class PasswordGeneratorDialog : public QDialog
{
	Q_OBJECT

public:
	PasswordGeneratorDialog(QWidget* parent = 0);
	~PasswordGeneratorDialog();

	private slots:
	// Actions des contrôles du GUI
	void on_btnGeneratePwd_clicked();
	void on_btnCloseDialog_clicked();
	void on_txtGeneratedPwd_selectionChanged();

private:
	Ui::PasswordGeneratorDialog ui;
};

