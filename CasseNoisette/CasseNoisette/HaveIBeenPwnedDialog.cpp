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
	ui.searchResults->setOpenExternalLinks(true);
}

HaveIBeenPwnedDialog::~HaveIBeenPwnedDialog()
{
}

void HaveIBeenPwnedDialog::on_btnAccountSearch_clicked()
{
	if (ui.txtAcountName->text().isEmpty())
	{
		QMessageBox::warning(this, "Case-Noisette", "Vous devez fournir un nom de compte (nom d'utilisateur, courriel...).");
		return;
	}

	// C'est la seul manière que j'ai pu régler l'issue #25
	networkManager.reset(new QNetworkAccessManager(this));

	ui.btnAccountSearch->setEnabled(false);
	ui.searchResults->setHtml("<b>Recherche en cours...</b>");
	QNetworkRequest request;
	QString accountToSearch = ui.txtAcountName->text();
	QUrl url("https://haveibeenpwned.com/api/v2/breachedaccount/" + accountToSearch.toHtmlEscaped() + "?includeUnverified=true");

	request.setUrl(url);
	request.setRawHeader("User-Agent", "Casse-Noisette/1.0 (Nokia; Qt)");
	networkManager->get(request);

	connect(networkManager.get(), SIGNAL(finished(QNetworkReply*)), this, SLOT(onResult(QNetworkReply*)));
}

void HaveIBeenPwnedDialog::onResult(QNetworkReply * reply)
{
	ui.btnAccountSearch->setEnabled(true);
	QString html;

	if (reply->error() == QNetworkReply::ContentNotFoundError)
	{
		ui.searchResults->setHtml("<p style=\"font-size: 18px\">Vous êtes chanceux, ce compte n'a pas été victime d'une fuite de données!</p>");
		return;
	}

	// Pour tous les autres erreurs, on affiche un MessageBox
	if (reply->error() != QNetworkReply::NoError)
	{
		QMessageBox msgBox;
		msgBox.setIcon(QMessageBox::Critical);
		msgBox.setText(reply->errorString());
		msgBox.exec();
		return;
	}

	// Si on se rend jusqu'ici, la requête s'est bien effectuée et a retourné des résultats

	html += "<p style=\"font-size: 12px;\">"
		"<b>:( Oh non! Ce compte a été victime d'une ou plusieurs fuites."
		" Il est fortement conseillé de changer votre mot de passe.</b></p>"
		"<p>Note: Une « fuite » est un incident où les données d’un site"
		" ont été consultées illégalement par des pirates, puis rendues"
		" publiques. Passez en revue les types de données qui ont été"
		" compromises (adresses courriel, mots de passe, cartes de crédit,"
		" etc.) et prenez les mesures nécessaires, tel que de changez vos"
		" mots de passe.</p>"
		"<h2>Site affectés</h2>";

	// Parse json
	QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());

	QJsonArray awesomeArray = jsonResponse.array();

	for (auto i = 0; i < awesomeArray.size(); i++)
	{
		QJsonObject value = awesomeArray.at(i).toObject();

		QString title = value["Title"].toString();
		QString description = value["Description"].toString();
		QString domain = value["Domain"].toString();

		html += "<p><b>Titre : </b>" + title + "<br />" + "<b>Site Web : </b><a href=\"http://" + domain + "\">" + domain + "</a><br />" + "<b>Description : </b>" + description + "</p>";
	}

	ui.searchResults->setHtml(html);

	// On informe à l'environnement de supprimer le pointeur une fois
	// que tous les évènements impliquant l'objet soient terminés.
	reply->deleteLater();
}