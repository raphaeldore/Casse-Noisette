#ifndef CHARSETSELECTOR_H
#define CHARSETSELECTOR_H

#include "QWidget.h"
#include "ui_CharsetSelector.h"

class CharsetSelector :	public QWidget
{
	Q_OBJECT
public:
	CharsetSelector(QWidget *parent = 0);
	~CharsetSelector();

	std::string getCharset();
private:
	Ui::CharsetSelector ui;
};

#endif
