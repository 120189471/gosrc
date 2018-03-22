#pragma once

#ifndef __PACKAGEMANAGE_H_
#define __PACKAGEMANAGE_H_

#include <stdio.h>

#include <QtWidgets/QMainWindow>
#include <QSettings>
#include <QMessageBox>
#include <QDialog>
#include <QFile>
#include <QTextCodec>
#include <QtCore/QTextStream>
#include <QVector>
#include <QThread> 
#include <QProcess>
#include <QDebug>

#include "ui_PackageManage.h"
#include "AddVer.h"
#include "QsInfoGUI.h"
#include "Base.h"
#include "Controller.h"

class WorkThread :public QThread
{
	Q_OBJECT
public:
	explicit WorkThread(QObject *parent = 0)
		: QThread(parent)
	{
		qDebug() << "Worker Thread : " << QThread::currentThreadId();
	}
	void run() Q_DECL_OVERRIDE
	{
		emit resultReady();
	}
	signals:
	void resultReady();

};

class PackageManage : public QMainWindow
{
	Q_OBJECT

public:
	PackageManage(QWidget *parent = Q_NULLPTR);
	
private:
	Ui::PackageManageClass ui;
	AddVer *add_ver;
	QThread* workthread;
	Controller* controller;
	
	
public:
	//QThread * workthread;
	//Controller * controller;
	

private slots:
	void addver();
	void addqs();
	void delqs();
	void editqs();

public slots:
	void pmgAddQSInfo();
	void allClientPackage();
	void allClientUPPackage();
	void upRealseServer();
	void up360();
	void clearPMDir();
	void clearDir(QDir);
	void runVMP();

signals:
	void SetQSNo(int);
};

#endif