#pragma once

#include <QWidget>
#include "ui_QsInfoGUI.h"

class QsInfoGUI : public QWidget
{
	Q_OBJECT

public:
	QsInfoGUI(QWidget *parent = Q_NULLPTR);
	~QsInfoGUI();
	
private:
	Ui::QsInfoGUI ui;

private:
	int edit_qs_no;

public slots:
	void saveqsinfo();
	void SetValue(int);

signals:
	void refreshQsList();
	
};
