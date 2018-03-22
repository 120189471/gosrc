#pragma once

#include <QWidget>
#include "ui_AddVer.h"

class AddVer : public QWidget
{
	Q_OBJECT

public:
	AddVer(QWidget *parent = Q_NULLPTR);
	~AddVer();

private:
	Ui::AddVer ui;
};
