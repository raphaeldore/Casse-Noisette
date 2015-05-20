#include "HaveIBeenPwnedDialog.h"

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QtWidgets/QMessageBox>

using namespace std;

HaveIBeenPwnedDialog::HaveIBeenPwnedDialog(QWidget* parent) : QDialog(parent)
{
	ui.setupUi(this);
	this->setModal(true);
	this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

	networkManager = make_unique<QNetworkAccessManager>(this);
}


HaveIBeenPwnedDialog::~HaveIBeenPwnedDialog()
{
}

void HaveIBeenPwnedDialog::on_btnAccountSearch_clicked()
{
	QNetworkRequest request;
	QString accountToSearch = ui.txtAcountName->text();
	QUrl url("https://haveibeenpwned.com/api/v2/breachedaccount/" + accountToSearch.toHtmlEscaped() + "?includeUnverified=true");

	request.setUrl(url);
	QNetworkReply * reply = networkManager->get(request);

	connect(networkManager.get(), SIGNAL(finished(QNetworkReply*)), this, SLOT(onResult(QNetworkReply*)));
}

void HaveIBeenPwnedDialog::onResult(QNetworkReply * reply)
{
	QString html;

	if (reply->error() != QNetworkReply::NoError && reply->error() != QNetworkReply::HostNotFoundError)
	{
		QMessageBox msgBox;
		msgBox.setIcon(QMessageBox::Critical);
		msgBox.setText(reply->errorString());
		msgBox.exec();
		return;
	}
	
	if (reply->error() == QNetworkReply::HostNotFoundError)
	{
		html += "<p>Vous êtes chanceux, ce compte n'a pas été victime d'un fuite de données!</p>";
	}
	// La requête s'est bien effectée


	//parse json
	QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
	

	QJsonArray awesomeArray = jsonResponse.array();

	for (auto i = 0; i < awesomeArray.size(); i++)
	{
		QJsonObject value = awesomeArray.at(i).toObject();

		QString title = value["Title"].toString();
		QString description = value["Description"].toString();
		QString domain = value["Domain"].toString();

		html += "<p><b>Titre : </b>" + title + "<br />" + "<b>Site Web : </b>" + domain + "<br />" + "<b>Description : </b>" + description + "</p>";
	}

	ui.searchResults->setHtml(html);

}