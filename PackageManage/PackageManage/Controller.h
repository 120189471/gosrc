#pragma once

#ifndef __CONTROLLER_H_
#define __CONTROLLER_H_

#include <QtWidgets/QMainWindow>
#include <QDir>
#include <QFile>
#include <QSettings>
#include <QProcess>
#include <QTextCodec>
#include <QMessageBox> 
#include <QTime>
#include <QCryptographicHash>

#include "Base.h"
//#include "PackageManage.h"

class Controller :public QObject
{
	Q_OBJECT;
public:
	Controller();
	~Controller();

	void FindFile(QString, QVector<QString>*, QString);
	void FindFile_old(QString, QVector<QString>*, QString, QString);
	void WriteScript2(QFile*, QString, QsInfo*, QVector<QString>, QString);
	void nsis(QString);
	void rar(QString,QString,QString);
	void MD5Info(QString, QString);
	void MergeDir(QVector<QString>, QsInfo*, QString, QVector<QString>*);
	QString package(QsInfo*, QString, QString);
	void AddPath(QVector<QString>*, QString);

	void FindFile_2(QString, QVector<FileInfo>*, QString);
	QVector<FileInfo> MergeDir_2(QVector<FileInfo> *, QVector<FileInfo> *);
	void WriteScript_2(pminfo, QFile*, QVector<FileInfo>*);
	void Controller::init();
	
	QVector<QString> run_qs_list;

public slots:
	void WriteScript();
	void onepackage();
	void UpServer();
	void UPPackage();
	void DisplayPath();

signals:
	void progress(int);
	void progress_str(QString);
	void button_status(bool);
};

#endif