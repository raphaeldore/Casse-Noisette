#ifndef CASSENOISETTE_H
#define CASSENOISETTE_H

#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include "ui_cassenoisette.h"

class CasseNoisette : public QMainWindow
{
	Q_OBJECT

public:
	CasseNoisette(QWidget *parent = 0);
	~CasseNoisette();
	private slots:
	void on_startCrackBtn_clicked();
	void on_pwdFileSelectBtn_clicked();
private:
	Ui::CasseNoisetteClass ui;
};

#endif // CASSENOISETTE_H
