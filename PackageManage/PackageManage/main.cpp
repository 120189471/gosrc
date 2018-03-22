#include "PackageManage.h"
#include <QtWidgets/QApplication>
#include <QTextCodec>			//编码头文件
#include <QSettings>
#include <QMessageBox>
#include "Base.h"

int main(int argc, char *argv[])
{

	//界面创建
	QApplication a(argc, argv);
	PackageManage w;
	w.show();
	return a.exec();
}
