#include "PackageManage.h"
#include <QtWidgets/QApplication>
#include <QTextCodec>			//����ͷ�ļ�
#include <QSettings>
#include <QMessageBox>
#include "Base.h"

int main(int argc, char *argv[])
{

	//���洴��
	QApplication a(argc, argv);
	PackageManage w;
	w.show();
	return a.exec();
}
