#include "PackageManage.h"

PackageManage::PackageManage(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowIcon(QIcon(":/Resources/timg.ico"));

	//������ʾ����Ϊ���ĵ�3�з�ʽ����֤����
	//ui.toolButton->setText(QStringLiteral("���"));
	//ui.toolButton->setText(QString::fromLocal8Bit("���"));
	//ui.toolButton->setText(QString::fromWCharArray(L"���"));

	//��ʼ��
	GlobleVariable::m_workdir = QCoreApplication::applicationDirPath();
	GlobleVariable::m_workdir.replace("/", "\\");
	GlobleVariable::m_cfg_file.setFileName("PackageManage.ini");
	QSettings *g_cfg = new QSettings("PackageManage.ini", QSettings::IniFormat);
	g_cfg->setIniCodec(QTextCodec::codecForName("utf-8"));
	if (!GlobleVariable::m_cfg_file.exists())
	{
		//switch (QMessageBox::information(NULL, QStringLiteral("����ȷ��"), QStringLiteral("��ȷ�������ļ��Ƿ����"), QMessageBox::Ok, 0))
		//{
		//default:
		//	QApplication::exit();
		//}

		g_cfg->setValue("/Main/qscount", "0");
		g_cfg->setValue("/Main/ver", "");
		g_cfg->setValue("/Main/rar_path", "C:\\Program Files\\WinRAR\\rar.exe");
		g_cfg->setValue("/Main/NSIS_path", "C:\\Program Files (x86)\\NSIS\\makensis.exe");
		g_cfg->setValue("/Main/VMP_path", "C:\\Program Files (x86)\\VMProtect Professional\\VMProtect.exe");
		g_cfg->setValue("/Main/release_path", "D:\\release");
		g_cfg->setValue("/Main/updata_ini", false);
		GlobleVariable::rar_path = "C:\\Program Files\\WinRAR\\rar.exe";
		GlobleVariable::NSIS_path = "C:\\Program Files (x86)\\NSIS\\makensis.exe";
		GlobleVariable::VMP_path = "C:\\Program Files (x86)\\VMProtect Professional\\VMProtect.exe";
		GlobleVariable::release_path = "D:\\release\\";
		GlobleVariable::version = "1.0.0.1";
		GlobleVariable::updata_ini = false;

	}
	else
	{
		bool ok;
		GlobleVariable::version = g_cfg->value("/Main/ver").toString();
		GlobleVariable::rar_path = g_cfg->value("/Main/rar_path").toString();
		GlobleVariable::NSIS_path = g_cfg->value("/Main/NSIS_path").toString();
		GlobleVariable::VMP_path = g_cfg->value("/Main/VMP_path").toString();
		GlobleVariable::release_path = g_cfg->value("/Main/realease_path").toString();
		for (int i = 0; i < g_cfg->value("/Main/qscount").toInt(&ok); i++)
		{
			QString tmep = g_cfg->value("/qsinfo/qsinfo_" + QString::number(i, 10)).toString();
			GlobleVariable::qs_list.append(g_cfg->value("/qsinfo/qsinfo_" + QString::number(i, 10)).toString());
		}
		GlobleVariable::updata_ini = g_cfg->value("/Main/updata_ini").toBool();
	}

	delete g_cfg;

	ui.lineEdit->setText(GlobleVariable::version);

	//s���ñ�ͷ
	QStringList headerLabels;
	headerLabels << "ȯ��" << "ID"
		<< "ģ��" /*<< "sec"*/
		<< "ȫ��" /*<< "sec"*/
		<< "����" /*<< "sec"*/
		<< "�������";

	ui.tableWidget->setColumnCount(6);
	ui.tableWidget->setRowCount(GlobleVariable::qs_list.size());
	ui.tableWidget->setHorizontalHeaderLabels(headerLabels);

	for (int i = 0; i < GlobleVariable::qs_list.size(); i++)
	{
		QsInfo *widget_add_qsinfo = new QsInfo();
		QStringToQsInfo(GlobleVariable::qs_list[i], widget_add_qsinfo);
		ui.tableWidget->setItem(i, 0, new QTableWidgetItem(widget_add_qsinfo->qs_name));
		ui.tableWidget->setColumnWidth(0, 90);
		ui.tableWidget->setItem(i, 1, new QTableWidgetItem(widget_add_qsinfo->qs_code));
		ui.tableWidget->setColumnWidth(1, 45);
		ui.tableWidget->setItem(i, 2, new QTableWidgetItem((widget_add_qsinfo->qs_mn_status)));
		//ui.tableWidget->setItem(i, 3, new QTableWidgetItem(widget_add_qsinfo->qs_mn_sec_status));
		ui.tableWidget->setItem(i, 3, new QTableWidgetItem(widget_add_qsinfo->qs_fz_status));
		//ui.tableWidget->setItem(i, 5, new QTableWidgetItem(widget_add_qsinfo->qs_fz_sec_status));
		ui.tableWidget->setItem(i, 4, new QTableWidgetItem(widget_add_qsinfo->qs_sc_status));
		//ui.tableWidget->setItem(i, 7, new QTableWidgetItem(widget_add_qsinfo->qs_sc_sec_status));
		for (int j = 2; j < 8; j++)
			ui.tableWidget->setColumnWidth(j, 36);
		QPushButton *lonypackage = new QPushButton();
		lonypackage->setText("���");
		ui.tableWidget->setCellWidget(i, 5, lonypackage);
		ui.tableWidget->setColumnWidth(5, 90);
		ui.tableWidget->setRowHeight(i, 20);

		delete widget_add_qsinfo;
	}
	//������Ӹ�ѡ��
	//QTableWidgetItem *checkbox_mn = new QTableWidgetItem();
	//checkbox_mn->setCheckState(Qt::Unchecked);
	//checkbox_mn->setText(QStringLiteral("ģ��1"));
	//ui.tableWidget->setItem(0, 2, checkbox_mn);
	//�������޸�
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

	ui.progressBar->setValue(0);
	ui.progressBar->setMaximum(100);
	ui.label->setText("");
	
	connect(ui.pushButton_15, SIGNAL(clicked()), this, SLOT(allClientPackage()));
	connect(ui.pushButton_18, &QPushButton::clicked, this, &PackageManage::clearPMDir);
	connect(ui.pushButton_20, &QPushButton::clicked, this, &PackageManage::upRealseServer);
	connect(ui.pushButton_21, &QPushButton::clicked, this, &PackageManage::up360);
	connect(ui.pushButton_22, &QPushButton::clicked, this, &PackageManage::allClientUPPackage);
	connect(ui.pushButton_24, &QPushButton::clicked, this, &PackageManage::addqs);
	connect(ui.pushButton_25, &QPushButton::clicked, this, &PackageManage::editqs);
	connect(ui.pushButton_26, &QPushButton::clicked, this, &PackageManage::delqs);
	connect(ui.pushButton,&QPushButton::clicked,this,&PackageManage::runVMP);
	
	workthread = new QThread();
	controller = new Controller();
	controller->moveToThread(workthread);
	connect(workthread, &QThread::started, controller, &Controller::init);
	connect(controller, &Controller::progress_str, ui.label, &QLabel::setText);
	connect(workthread, &QThread::finished, controller, &QObject::deleteLater);
	
	workthread->start();

	//����δ����
	ui.pushButton_23->setEnabled(false);
}

void PackageManage::allClientPackage()
{
	if (ui.lineEdit->text()==NULL)
	{
		QMessageBox msgBox;
		msgBox.setText("������汾��");
		msgBox.setStandardButtons(QMessageBox::Yes);
		msgBox.exec();
		return;
	}
	else
	{
		if (GlobleVariable::version != ui.lineEdit->text())
		{
			QMessageBox msgBox;
			msgBox.setText("�ӿ�");
			msgBox.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
			msgBox.exec();
		}
		GlobleVariable::version = ui.lineEdit->text();
		infotoini("/Main/ver", GlobleVariable::version);
	}

	int ret = QMessageBox::warning(this, tr("ȷ��"),
		"��ȷ�ϰ汾�� **" + GlobleVariable::version + "** �Ƿ���ȷ��ӣ�\n" "�� ȷ�� ������װ\n" "�� ȡ�� �˳���װ",
		QMessageBox::Ok | QMessageBox::Cancel);
	switch (ret)
	{
	case QMessageBox::Cancel:
		return;
	case QMessageBox::Ok:
	default:
		break;
	}

	QList<QTableWidgetSelectionRange> select_line_no = ui.tableWidget->selectedRanges();
	
	GlobleVariable::pmList.clear();
	if (select_line_no.size() == 0 || (select_line_no.at(0).leftColumn()<2 && select_line_no.at(0).leftColumn()>4))
	{
		for (QString i : GlobleVariable::qs_list)
		{
			pminfo pm_info;
			pm_info.qsname = i.section("|", 0, 0);
			pm_info.qsid = i.section("|", 1, 1);
			pm_info.only_up_pack = false;

			if (i.section("|", 2, 2).mid(0, 1) == "1")
			{
				pm_info.status = "ģ��";
				GlobleVariable::pmList.append(pm_info);
			}
			if (i.section("|", 2, 2).mid(2, 1) == "1")
			{
				pm_info.status = "ȫ��";
				if (i.section("|", 2, 2).mid(3, 1) == "1")
					pm_info.only_up_pack = true;
				GlobleVariable::pmList.append(pm_info);
			}
			if (i.section("|", 2, 2).mid(4, 1) == "1")
			{
				pm_info.status = "����";
				if (i.section("|", 2, 2).mid(5, 1) == "1")
					pm_info.only_up_pack = true;
				GlobleVariable::pmList.append(pm_info);
			}
		}
	}
	else
	{
		//GlobleVariable::qs_list[select_line_no.at(0).topRow()];
		pminfo pm_info;
		pm_info.qsname = GlobleVariable::qs_list[select_line_no.at(0).topRow()].section("|", 0, 0);
		pm_info.qsid = GlobleVariable::qs_list[select_line_no.at(0).topRow()].section("|", 1, 1);

		switch (select_line_no.at(0).leftColumn())
		{
		case 2:
			pm_info.status = "ģ��";
			break;
		case 3:
			pm_info.status = "ȫ��";
			if (GlobleVariable::qs_list[select_line_no.at(0).topRow()].section("|", 2, 2).mid(3, 1) == "1")
				pm_info.only_up_pack = true;
			break;
		case 4:
			pm_info.status = "����";
			if (GlobleVariable::qs_list[select_line_no.at(0).topRow()].section("|", 2, 2).mid(5, 1) == "1")
				pm_info.only_up_pack = true;
			break;
		default:
			QMessageBox(QMessageBox::Warning, "����", "���ִ����·��Ӧ���ڣ�����Ĵ���", QMessageBox::Ok);
			break;
		}
		GlobleVariable::pmList.append(pm_info);
	}
	
	workthread = new QThread();
	controller = new Controller();

	controller->moveToThread(workthread);
	connect(workthread, SIGNAL(started()), controller, SLOT(onepackage()));
	ui.pushButton_15->setEnabled(false);
	connect(controller, &Controller::progress, ui.progressBar, &QProgressBar::setValue);
	connect(controller, &Controller::progress_str, ui.label, &QLabel::setText);
	connect(controller, &Controller::button_status, ui.pushButton_15, &QPushButton::setEnabled);
	connect(workthread, &QThread::finished, controller, &QObject::deleteLater);
	//connect(ui.pushButton_2, &QPushButton::click, controller, &Controller::display_path);
	
	workthread->start();
}

void PackageManage::allClientUPPackage()
{

	QList<QTableWidgetSelectionRange> select_line_no = ui.tableWidget->selectedRanges();

	GlobleVariable::pmList.clear();
	if (select_line_no.size() == 0 || (select_line_no.at(0).leftColumn()<2 && select_line_no.at(0).leftColumn()>4))
	{
		for (QString i : GlobleVariable::qs_list)
		{
			pminfo pm_info;
			pm_info.qsname = i.section("|", 0, 0);
			pm_info.qsid = i.section("|", 1, 1);
			pm_info.only_up_pack = false;

			if (i.section("|", 2, 2).mid(0, 1) == "1")
			{
				pm_info.status = "ģ��";
				GlobleVariable::pmList.append(pm_info);
			}
			if (i.section("|", 2, 2).mid(2, 1) == "1")
			{
				pm_info.status = "ȫ��";
				if (i.section("|", 2, 2).mid(3, 1) == "1")
					pm_info.only_up_pack = true;
				GlobleVariable::pmList.append(pm_info);
			}
			if (i.section("|", 2, 2).mid(4, 1) == "1")
			{
				pm_info.status = "����";
				if (i.section("|", 2, 2).mid(5, 1) == "1")
					pm_info.only_up_pack = true;
				GlobleVariable::pmList.append(pm_info);
			}
		}
	}
	else
	{
		//GlobleVariable::qs_list[select_line_no.at(0).topRow()];
		pminfo pm_info;
		pm_info.qsname = GlobleVariable::qs_list[select_line_no.at(0).topRow()].section("|", 0, 0);
		pm_info.qsid = GlobleVariable::qs_list[select_line_no.at(0).topRow()].section("|", 1, 1);

		switch (select_line_no.at(0).leftColumn())
		{
		case 2:
			pm_info.status = "ģ��";
			break;
		case 3:
			pm_info.status = "ȫ��";
			if (GlobleVariable::qs_list[select_line_no.at(0).topRow()].section("|", 2, 2).mid(3, 1) == "1")
				pm_info.only_up_pack = true;
			break;
		case 4:
			pm_info.status = "����";
			if (GlobleVariable::qs_list[select_line_no.at(0).topRow()].section("|", 2, 2).mid(5, 1) == "1")
				pm_info.only_up_pack = true;
			break;
		default:
			QMessageBox(QMessageBox::Warning, "����", "���ִ����·��Ӧ���ڣ�����Ĵ���", QMessageBox::Ok);
			break;
		}
		GlobleVariable::pmList.append(pm_info);
	}

	workthread = new QThread();
	controller = new Controller();

	controller->moveToThread(workthread);
	connect(workthread, SIGNAL(started()), controller, SLOT(UPPackage()));
	ui.pushButton_22->setEnabled(false);
	connect(controller, &Controller::progress, ui.progressBar, &QProgressBar::setValue);
	connect(controller, &Controller::progress_str, ui.label, &QLabel::setText);
	connect(controller, &Controller::button_status, ui.pushButton_22, &QPushButton::setEnabled);
	connect(workthread, &QThread::finished, controller, &QObject::deleteLater);

	workthread->start();
}

void PackageManage::upRealseServer()
{
	QList<QTableWidgetSelectionRange> select_line_no = ui.tableWidget->selectedRanges();

	GlobleVariable::pmList.clear();
	if (select_line_no.size() == 0 || (select_line_no.at(0).leftColumn()<2 && select_line_no.at(0).leftColumn()>4))
	{
		for (QString i : GlobleVariable::qs_list)
		{
			pminfo pm_info;
			pm_info.qsname = i.section("|", 0, 0);
			pm_info.qsid = i.section("|", 1, 1);
			pm_info.only_up_pack = false;

			if (i.section("|", 2, 2).mid(0, 1) == "1")
			{
				pm_info.status = "ģ��";
				GlobleVariable::pmList.append(pm_info);
			}
			if (i.section("|", 2, 2).mid(2, 1) == "1")
			{
				pm_info.status = "ȫ��";
				if (i.section("|", 2, 2).mid(3, 1) == "1")
					pm_info.only_up_pack = true;
				GlobleVariable::pmList.append(pm_info);
			}
			if (i.section("|", 2, 2).mid(4, 1) == "1")
			{
				pm_info.status = "����";
				if (i.section("|", 2, 2).mid(5, 1) == "1")
					pm_info.only_up_pack = true;
				GlobleVariable::pmList.append(pm_info);
			}
		}
	}
	else
	{
		//GlobleVariable::qs_list[select_line_no.at(0).topRow()];
		pminfo pm_info;
		pm_info.qsname = GlobleVariable::qs_list[select_line_no.at(0).topRow()].section("|", 0, 0);
		pm_info.qsid = GlobleVariable::qs_list[select_line_no.at(0).topRow()].section("|", 1, 1);

		switch (select_line_no.at(0).leftColumn())
		{
		case 2:
			pm_info.status = "ģ��";
			break;
		case 3:
			pm_info.status = "ȫ��";
			if (GlobleVariable::qs_list[select_line_no.at(0).topRow()].section("|", 2, 2).mid(3, 1) == "1")
				pm_info.only_up_pack = true;
			break;
		case 4:
			pm_info.status = "����";
			if (GlobleVariable::qs_list[select_line_no.at(0).topRow()].section("|", 2, 2).mid(5, 1) == "1")
				pm_info.only_up_pack = true;
			break;
		default:
			QMessageBox(QMessageBox::Warning, "����", "���ִ����·��Ӧ���ڣ�����Ĵ���", QMessageBox::Ok);
			break;
		}
		GlobleVariable::pmList.append(pm_info);
	}

	QThread* workthread = new QThread();
	Controller *controller = new Controller();
	controller->moveToThread(workthread);
	connect(workthread, &QThread::started, controller, &Controller::UpServer);
	connect(controller, &Controller::progress_str, ui.label, &QLabel::setText);
	workthread->start();
}

void PackageManage::addver()
{
	//dialog = new QWidget(this);
	//dialog->setModal(false);
	//dialog->show();
	add_ver = new AddVer();
	add_ver->setWindowFlags(Qt::Widget);
	add_ver->show();
}

void PackageManage::addqs()
{
	QsInfoGUI *qs_info_gui = new QsInfoGUI();
	connect(qs_info_gui, SIGNAL(refreshQsList()), this, SLOT(pmgAddQSInfo()));
	qs_info_gui->setWindowFlags(Qt::Widget);
	qs_info_gui->setWindowModality(Qt::ApplicationModal);
	qs_info_gui->show();
}

void PackageManage::delqs()
{
	//�жϵ�ǰѡ���в�ɾ��
	QList<QTableWidgetSelectionRange> select_line_no = ui.tableWidget->selectedRanges();
	int remove_line = select_line_no.at(0).topRow();
	GlobleVariable::qs_list.remove(remove_line);

	infotoini("/Main/qscount", QString::number(GlobleVariable::qs_list.size(), 10));
	for (int i = 0; i < GlobleVariable::qs_list.size(); i++)
	{
		infotoini("/qsinfo/qsinfo_" + QString::number(i, 10), GlobleVariable::qs_list[i]);
	}

	ui.tableWidget->removeRow(remove_line);
}

void PackageManage::pmgAddQSInfo()
{
	//��װ�۰�˳����
	if (GlobleVariable::count-1 == GlobleVariable::qs_list.size())
	{
		ui.tableWidget->setRowCount(GlobleVariable::qs_list.size());
		qSort(GlobleVariable::qs_list.begin(), GlobleVariable::qs_list.end());

		for (int i = 0; i < GlobleVariable::qs_list.size(); i++)
		{
			QsInfo *widget_add_qsinfo = new QsInfo();
			QStringToQsInfo(GlobleVariable::qs_list[i], widget_add_qsinfo);
			
			ui.tableWidget->setItem(i, 0, new QTableWidgetItem(widget_add_qsinfo->qs_name));
			ui.tableWidget->setItem(i, 1, new QTableWidgetItem(widget_add_qsinfo->qs_code));
			ui.tableWidget->setItem(i, 2, new QTableWidgetItem((widget_add_qsinfo->qs_mn_status)));
			//ui.tableWidget->setItem(i, 3, new QTableWidgetItem(widget_add_qsinfo->qs_mn_sec_status));
			ui.tableWidget->setItem(i, 3, new QTableWidgetItem(widget_add_qsinfo->qs_fz_status));
			//ui.tableWidget->setItem(i, 5, new QTableWidgetItem(widget_add_qsinfo->qs_fz_sec_status));
			ui.tableWidget->setItem(i, 4, new QTableWidgetItem(widget_add_qsinfo->qs_sc_status));
			//ui.tableWidget->setItem(i, 7, new QTableWidgetItem(widget_add_qsinfo->qs_sc_sec_status));

			QPushButton *lonypackage = new QPushButton();
			lonypackage->setText("���");
			ui.tableWidget->setCellWidget(i, 5, lonypackage);

			delete widget_add_qsinfo;
		}
	}
	else
	{
		QMessageBox::information(NULL, QStringLiteral("��˳���쳣"), QStringLiteral("��ȷ�����¿�����"), QMessageBox::Ok, 0);
	}
}

void PackageManage::editqs()
{
	QsInfoGUI *qs_info_gui = new QsInfoGUI();
	connect(qs_info_gui, SIGNAL(refreshQsList()), this, SLOT(pmgAddQSInfo()));
	connect(this, SIGNAL(SetQSNo(int)), qs_info_gui, SLOT(SetValue(int)));
	QList<QTableWidgetSelectionRange> select_line_no = ui.tableWidget->selectedRanges();
	if (select_line_no.size() == 0)
	{
		QMessageBox(QMessageBox::Warning, "����", "��ѡ����Ҫ�༭�Ŀͻ���", QMessageBox::Ok);
		return;
	}
	emit SetQSNo(select_line_no.at(0).topRow());
	//ui.tableWidget->selectRow()
	qs_info_gui->setWindowFlags(Qt::Widget);
	qs_info_gui->setWindowModality(Qt::ApplicationModal);
	qs_info_gui->show();
}

void PackageManage::up360()
{
	QStringList qsl;
	qsl << ("open.soft.360.cn/softsubmit.php");
	//QProcess::execute("C:\\Program Files\\Internet Explorer\\iexplore.exe", qsl);
	QProcess::startDetached("C:\\Program Files\\Internet Explorer\\iexplore.exe", qsl);
}

void PackageManage::clearPMDir()
{
	clearDir(QDir(GlobleVariable::m_workdir + "\\��װ��"));
	clearDir(QDir(GlobleVariable::m_workdir + "\\������"));
}
void PackageManage::clearDir(QDir qdir)
{
	foreach(QFileInfo mfi, qdir.entryInfoList())
	{
		if (mfi.fileName() == "." || mfi.fileName() == "..")
			continue;
		if (mfi.isFile())
		{
			qDebug() << "File:\t"<<mfi.filePath();
			QFile::remove(mfi.filePath());
		}
		if (mfi.isDir())
		{
			clearDir(mfi.filePath());
			qDebug() << "Dir:\t" << mfi.filePath();
			qdir.rmpath(mfi.filePath());
		}
	}
}

void PackageManage::runVMP(){
	QProcess::execute(GlobleVariable::VMP_path);
}