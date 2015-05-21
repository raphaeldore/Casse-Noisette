#include "CharsetSelector.h"
#include "../CrackEngine/CharsetBuilder.h"

using namespace std;

CharsetSelector::CharsetSelector(QWidget *parent) : QWidget(parent)
{
	ui.setupUi(this);
}


CharsetSelector::~CharsetSelector()
{
}

string CharsetSelector::getCharset()
{
	CrackEngine::CharsetBuilder charsetBuilder {
		ui.chkCharsetLower->isChecked(),
		ui.chkCharsetUpper->isChecked(),
		ui.chkCharsetNumeric->isChecked(),
		ui.chkCharsetSpace->isChecked(),
		ui.chkCharsetSpecial->isChecked(),
		ui.txtCustomCharset->text().toLocal8Bit().constData() // Les QString sont en UTF-16, 
		                                                      // et les std::string sont en UTF-8.
		                                                      // On doit les convertir.
	};

	return charsetBuilder.BuildCharset();
}

const Ui::CharsetSelector& CharsetSelector::getUi() const
{
	return ui;
}