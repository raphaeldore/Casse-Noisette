#ifndef HAVEIBEENPWNEDDIALOG_H
#define HAVEIBEENPWNEDDIALOG_H

#include "ui_HaveIBeenPwnedDialog.h"
#include <memory>

class QNetworkAccessManager;
class QNetworkReply;

class HaveIBeenPwnedDialog : public QDialog
{
	Q_OBJECT
public:
	HaveIBeenPwnedDialog(QWidget* parent = 0);
	~HaveIBeenPwnedDialog();
public slots:
	void on_btnAccountSearch_clicked();
	void onResult(QNetworkReply * reply);
private:
	Ui::HaveIBeenPwnedDialog ui;
	std::unique_ptr<QNetworkAccessManager> networkManager = nullptr;
};

#endif
