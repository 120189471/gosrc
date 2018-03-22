#include "QsInfoGUI.h"
#include "Base.h"
#include "PackageManage.h"
#include "ui_PackageManage.h"

#pragma execution_character_set("utf-8")

QsInfoGUI::QsInfoGUI(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//QRegExp rx("^[0-6][0-5][0-5][0-3][0-5]$");
	//QRegExpValidator *pReg = new QRegExpValidator(rx, this);
	//ui.lineEdit_2->setValidator(pReg);
	//bool temp =QObject::connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(pmgAddQSInfo()));
	edit_qs_no = -1;
}

QsInfoGUI::~QsInfoGUI()
{
}

void QsInfoGUI::saveqsinfo()
{
	//在tablewidget里面券商信息行,这步交给信号槽 pmgAddQSInfo()

	QString qs_info;
	qs_info = ui.lineEdit->text() + "|"
		+ ui.lineEdit_2->text() + "|"
		+ QString::number(ui.checkBox_3->isChecked())
		//+ QString::number(ui.checkBox_4->isChecked())
		+ "0"
		+ QString::number(ui.checkBox_5->isChecked())
		+ QString::number(ui.checkBox->isChecked())
		+ QString::number(ui.checkBox_7->isChecked())
		+ QString::number(ui.checkBox_2->isChecked());
	 
	if (edit_qs_no >-1)
		GlobleVariable::qs_list[edit_qs_no] = qs_info;
	else
		GlobleVariable::qs_list.append(qs_info);

	GlobleVariable::count = GlobleVariable::qs_list.size() + 1;
	//添加的的券商信息到配置文件中
	//addQSInfoToIni(qs_list);
	infotoini("/Main/qscount", QString::number(GlobleVariable::qs_list.size(), 10));
	for (int i = 0; i < GlobleVariable::qs_list.size(); i++)
	{
		infotoini("/qsinfo/qsinfo_" + QString::number(i,10), GlobleVariable::qs_list[i]);
	}
	//关闭窗口
	emit refreshQsList();
	this->close();
}

void QsInfoGUI::SetValue(int qs_no)
{
	QsInfo *qs_info = new QsInfo();
	QStringToQsInfo(GlobleVariable::qs_list[qs_no], qs_info);
	ui.lineEdit->setText(qs_info->qs_name);
	ui.lineEdit_2->setText(qs_info->qs_code);
	
	if (qs_info->qs_mn_status == "1")
		ui.checkBox_3->setChecked(Qt::Checked);
	/*if (qs_info->qs_mn_sec_status == "1")
		ui.checkBox_4->setChecked(Qt::Checked);*/
	if (qs_info->qs_fz_status == "1")
		ui.checkBox_5->setChecked(Qt::Checked);
	if (qs_info->qs_fz_sec_status == "1")
		ui.checkBox->setChecked(Qt::Checked);
	if (qs_info->qs_sc_status == "1")
		ui.checkBox_7->setChecked(Qt::Checked);
	if (qs_info->qs_sc_sec_status == "1")
		ui.checkBox_2->setChecked(Qt::Checked);
	edit_qs_no = qs_no;
	delete qs_info;
}