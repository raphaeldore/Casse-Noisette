#ifndef RESULTDIALOG_H
#define RESULTDIALOG_H

#include "ui_resultdialog.h"

#include <QtWidgets/QDialog>

using namespace std;

class QCheckBox;

class ResultDialog : public QDialog{
	Q_OBJECT
public:
	ResultDialog(QWidget * parent = 0);
	void setInformativeText(string informativeText);
	void setCrackingResults(vector<tuple<string, string, string>> _results, const QString & _crackingTime);
	void setResultText(QString resultText);
	public slots:
	void on_closeBtn_clicked();
	void on_saveBtn_clicked();
private:
	QString resultTupleToString(const tuple<string, string, string> & _resultTuple) const;

	Ui::ResultDialog ui;
};

#endif