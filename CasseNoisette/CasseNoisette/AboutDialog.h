#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include "ui_aboutdialog.h"

class QCheckBox;

class AboutDialog : public QDialog
{
	Q_OBJECT

public:
	AboutDialog(QWidget* parent = 0);
public slots:
	void on_closeBtn_clicked();
private:
	Ui::AboutDialog ui;
};

#endif