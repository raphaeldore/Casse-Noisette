#ifndef RESULTDIALOG_H
#define RESULTDIALOG_H

#include "ui_resultdialog.h"


class QCheckBox;

class ResultDialog : public QDialog
{
	Q_OBJECT

public:
	ResultDialog(QWidget* parent = 0);
	void setInformativeText(const std::string & informativeText);
	void setCrackingResults(const std::vector<std::tuple<std::string, std::string, std::string>> & _results, const QString& _crackingTime);
	void setResultText(QString resultText);
public slots:
	void on_closeBtn_clicked();
	void on_saveBtn_clicked();
private:
	QString resultTupleToString(const std::tuple<std::string, std::string, std::string>& _resultTuple) const;

	Ui::ResultDialog ui;
};

#endif