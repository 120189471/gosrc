#include "Controller.h"
#include "MD5.h"

Controller::Controller()
{
}

Controller::~Controller()
{
}

QString Controller::package(QsInfo* qsinfo, QString status, QString sec_status)
{
	emit progress_str("�������� " + qsinfo->qs_name + " _ " + status + "�� �ͻ���...");
	QVector<QString> out_script_file;
	MergeDir(GlobleVariable::monthor_file, qsinfo, status, &out_script_file);

	QString run_ver = GlobleVariable::version;
	QString Qs_scrpit_file = GlobleVariable::m_workdir + "\\Rtdscript\\" + qsinfo->qs_name + "_" + status;

	//if (sec_status == "1")
	//{
	//	run_ver += "S";
	//	Qs_scrpit_file += "S";
	//	out_script_file.append(GlobleVariable::sec_file);
	//}

	QFile file(Qs_scrpit_file);
	file.open(QIODevice::WriteOnly | QIODevice::Truncate);
	WriteScript2(&file, status, qsinfo, out_script_file, sec_status);
	file.close();

	nsis(Qs_scrpit_file);

	return qsinfo->qs_name + "_QWin��Ȩ���Խ���ϵͳ_" + status + "_" + run_ver;
}

void Controller::AddPath(QVector<QString>* files, QString file_path)
{
	for (int i = 0; i < files->length(); i++)
	{
		if ((*files)[i].right(1) == "\\")
			continue;
		(*files)[i] = file_path + (*files)[i];
	}
}

//ȯ��Ŀ¼���list
//��׼Ŀ¼��ȯ�̶���Ŀ¼�����Ŀ¼
void Controller::MergeDir(QVector<QString> mothor_dir_file, QsInfo* qsinfo, QString status, QVector<QString> * out_script_file)
{
	QString qs_path = GlobleVariable::m_workdir + "\\�����ļ�" + "\\" + status + "\\[" + qsinfo->qs_code + "]" + qsinfo->qs_name;
	QString standard_path = GlobleVariable::m_workdir + "\\��׼�ļ�\\binR_Internet";
	QVector<QString> qs_only_file;

	FindFile(qs_path, &qs_only_file, NULL);

	bool order_status = false;
	bool quote_status = false;
	//��ȫĿ¼

	for (int i = 0; i < qs_only_file.size(); i++)
	{
		if (qs_only_file[i].right(1) == "\\")
			continue;
		qs_only_file[i] = qs_path + qs_only_file[i];
	}

	//for (int i = 0; i < mothor_dir_file.size(); i++)
	//{
	//	if (mothor_dir_file[i].right(1) == "\\")
	//		continue;
	//	mothor_dir_file[i] = standard_path + mothor_dir_file[i];
	//}
	*out_script_file = mothor_dir_file;

	//�ж�OrderModuleĿ¼
	for (int i = 0; i < qs_only_file.size(); i++)
	{
		//ɾ��OrderModule  in out_script_file
		int insert_no = 0;
		if (qs_only_file[i] == qs_path + "\\OrderModule\\SSTTrade.dll")
		{
			order_status = true;
			for (int j = 0; j < out_script_file->size(); j++)
			{
				/*QString qs = (*out_script_file)[j];
				bool b = out_script_file[j].startsWith("\\QuoteModule\\");
				if ((*out_script_file)[j].mid(standard_path.size(), 12) == "\\OrderModule"
				|| (*out_script_file)[j].startsWith("\\OrderModule\\"))*/
				if ((*out_script_file)[j].contains("OrderModule"))
				{
					insert_no = j;
					out_script_file->remove(j);
					j--;
				}
			}

			for (int k = 0; k < qs_only_file.size(); k++)
			{
				/*if (qs_only_file[k].mid(qs_path.size(), 12) == "\\OrderModule" ||
				qs_only_file[k].startsWith("\\OrderModule\\"))*/
				if (qs_only_file[k].contains("OrderModule"))
				{
					out_script_file->insert(insert_no++, qs_only_file[k]);
				}
			}
			break;
		}
	}

	//�ж�QuoteModuleĿ¼
	for (int i = 0; i < qs_only_file.size(); i++)
	{
		int insert_no = 0;
		if (qs_only_file[i] == qs_path + "\\QuoteModule\\QuoteClientApi.ini")
		{
			quote_status = true;
			for (int j = 0; j < out_script_file->size(); j++)
			{
				/*if ((*out_script_file)[j].mid(standard_path.size(), 12) == "\\QuoteModule"
				|| (*out_script_file)[j].startsWith("\\QuoteModule\\"))*/
				if ((*out_script_file)[j].contains("QuoteModule", Qt::CaseSensitive))
				{
					insert_no = j;
					out_script_file->remove(j);
					j--;
				}
			}

			out_script_file->insert(insert_no++, "\\QuoteModule\\");
			out_script_file->insert(insert_no++, standard_path + "\\QuoteModule\\QuoteClientApi.dll");
			out_script_file->insert(insert_no++, qs_path + "\\QuoteModule\\QuoteClientApi.ini");

			QSettings  market_list_ini(qs_path + "\\QuoteModule\\QuoteClientApi.ini", QSettings::IniFormat);
			QStringList groupList = market_list_ini.childGroups();
			foreach(QString group, groupList)
			{
				if (group != "ServerName")
				{
					QString market = market_list_ini.value(group + "/keyfile").toString().section("/", 1, 1);

					out_script_file->insert(insert_no++, "\\QuoteModule\\" + market + "\\");
					out_script_file->insert(insert_no++, standard_path + "\\QuoteModule\\" + market + "\\tran2nd" + market + ".dll");

					if (QFile(qs_path + "\\QuoteModule\\" + market + "\\tran2nd" + market + ".ini").exists())
					{
						out_script_file->insert(insert_no++, qs_path + "\\QuoteModule\\" + market + "\\tran2nd" + market + ".ini");
					}
					else
					{
						out_script_file->insert(insert_no++, standard_path + "\\QuoteModule\\" + market + "\\tran2nd" + market + ".ini");
					}
				}
			}
		}
	}

	/*
	//�ϲ���ͬ���ļ���Ŀ¼
	for (int i = 0; i < qs_only_file.size(); i++)
	{
	if (qs_only_file[i].right(1) == "\\")
	continue;
	for (int j = 0; j < out_script_file.size(); j++)
	{
	if (out_script_file[j].right(1) == "\\")
	continue;
	if (qs_only_file[i].section('\\', -1) == out_script_file[j].section('\\', -1))
	{
	out_script_file[j] = qs_only_file[i];
	}
	}
	}

	//�ϲ�qs_only���治ͬ���ļ���Ŀ¼
	for (int i = 0; i < qs_only_file.size(); i++)
	{
	bool b = false;
	if (qs_only_file[i].right(1) != "\\")
	{

	QString tempfile = qs_only_file[i].mid(qs_path.size());
	int file_size = -(qs_only_file[i].mid(qs_path.size()).size());
	for (int j = 0; j < out_script_file.size(); j++)
	{
	QString temfiles2 = out_script_file[j].right(file_size);
	if (tempfile == out_script_file[j].right(file_size))
	{
	b = true;
	break;
	}
	}
	}
	else
	{
	for (int j = 0; j < out_script_file.size(); j++)
	{
	if (qs_only_file[i] == out_script_file[j])
	{
	b = true;
	break;
	}
	}
	}

	if (b == false)
	{
	out_script_file.append(qs_only_file[i]);
	b = true;
	}
	}
	*/
	//�ϲ���ͬ
	QVector<QString> temp_path;
	for (int i = 0; i < qs_only_file.size(); i++)
	{
		/*if ((order_status == true && qs_only_file[i].mid(qs_path.size(), 12) == "\\OrderModule") ||
		(order_status == true && qs_only_file[i].startsWith("\\OrderModule\\")) ||
		((quote_status == true) && qs_only_file[i].mid(qs_path.size(), 12) == "\\QuoteModule") ||
		((quote_status == true) && qs_only_file[i].startsWith("\\QuoteModule\\"))
		)*/
		if (order_status && qs_only_file[i].contains("OrderModule") ||
			quote_status && qs_only_file[i].contains("QuoteModule"))
			continue;

		//fileflg&dirflg if this flg is true,the file or dir isn't in the mon_script,it's blone the qs only,
		//so add this tring in out_script,
		bool fileflg = false;
		bool dirflg = false;
		int file_insert_no = 0;

		if (qs_only_file[i].right(1) == "\\")
		{
			for (int j = 0; j < out_script_file->size(); j++)
			{
				if ((*out_script_file)[j].right(1) != "\\")
					continue;
				if (qs_only_file[i] == (*out_script_file)[j])
				{
					dirflg = false;
					break;
				}
				else
				{
					dirflg = true;
				}
			}
			if (dirflg)
			{
				for (int k = 0; k < qs_only_file.size(); k++)
				{
					if ((qs_only_file[k].right(1) == "\\"&&qs_only_file[k].mid(0, qs_only_file[i].size()) == qs_only_file[i]) ||
						qs_only_file[k].mid(qs_path.size(), qs_only_file[i].size()) == qs_only_file[i])
					{
						out_script_file->append(qs_only_file[k]);
					}
				}
			}
		}
		else
		{
			for (int j = 0; j < out_script_file->size(); j++)
			{
				if (qs_only_file[i].mid(qs_path.size()) == (*out_script_file)[j].mid(standard_path.size()))
				{
					(*out_script_file)[j] = qs_only_file[i];
					fileflg = false;
					break;
				}
				else
				{
					fileflg = true;
				}
			}

			if (fileflg)
			{
				/*for (int k = 0; k < out_script_file.size(); k++)
				{
				if (qs_only_file[i].mid(qs_path.size())>out_script_file[k].mid(standard_path.size()))
				{
				out_script_file.insert(k, qs_only_file[i]);
				break;
				}
				else
				{
				QMessageBox::information(NULL, "Title", "Content", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
				}*/
				int k = 1;

				while (qs_only_file[i].mid(qs_path.size()).section("\\", k, k) != qs_only_file[i].section("\\", -1))
				{
					k++;
				}
				if (k == 1)
				{
					out_script_file->insert(0, qs_only_file[i]);
				}
				else
				{
					for (int m = 0; m < out_script_file->size(); m++)
					{
						if ((*out_script_file)[m].right(1) != "\\")
							continue;
						else
						{
							if (qs_only_file[i].section("\\", -2, -2) == (*out_script_file)[m].section("\\", -2, -2))
							{
								out_script_file->insert(m + 1, qs_only_file[i]);
								break;
							}
						}
					}
				}
			}
		}
	}
}


void Controller::onepackage()
{
	MD5 md5;
	//run_qs_list = GlobleVariable::qs_list;
	//WriteScript();

	/*
	FindFile(GlobleVariable::m_workdir + "\\��׼�ļ�\\binR_Internet", &GlobleVariable::monthor_file, "\\");
	AddPath(&GlobleVariable::monthor_file, GlobleVariable::m_workdir + "\\��׼�ļ�\\binR_Internet");
	*/

	//WriteScript(GlobleVariable::qs_list);
	//workthread->start();

	//������� qsinfo->name,qsinfo->id,status(mn\qz\sc)
	QVector<FileInfo>* qs_file_list;
	int progress_no = 0;
	for (auto i : GlobleVariable::pmList)
	{
		QString stats_e;
		emit progress(progress_no++ *100 / GlobleVariable::pmList.size()/2+5);
		emit progress_str("�������� "+i.qsname+"_"+i.status+"�� �ͻ��� ��...");
		
		qs_file_list = new QVector<FileInfo>();
		FindFile_2(GlobleVariable::m_workdir + "\\�����ļ�\\" + i.status + "\\[" + i.qsid + "]" + i.qsname,
			qs_file_list,
			"");
		if (i.status == "ģ��")
		{
			*qs_file_list = MergeDir_2(&(GlobleVariable::simulation_env_file), qs_file_list);
			stats_e = "sstupdate_mn";
		}
		else if (i.status == "ȫ��")
		{

			*qs_file_list = MergeDir_2(&(GlobleVariable::true_env_file), qs_file_list);
			stats_e = "sstupdate_qz";

			if (i.qsname == "����֤ȯ")
			{
				i.status = "����";
			}

		}
		else if (i.status == "����")
		{
			*qs_file_list = MergeDir_2(&(GlobleVariable::produce_env_file), qs_file_list);
			stats_e = "sstupdate_sc";
		}
		else
			QMessageBox(QMessageBox::Warning, "����", "���ִ����·��Ӧ���ڣ�����Ĵ���", QMessageBox::Ok);

		QFile file(GlobleVariable::m_workdir + "\\Rtdscript\\" + i.qsname + "_" + i.status);
		file.open(QIODevice::WriteOnly | QIODevice::Truncate);
		WriteScript_2(i, &file, qs_file_list);
		file.close();
		nsis(GlobleVariable::m_workdir + "\\Rtdscript\\" + i.qsname + "_" + i.status);
		

		if (i.qsname == "")
		{
			MD5Info(GlobleVariable::m_workdir + "\\��װ��\\", "QWin��Ȩ���Խ���ϵͳ_" + i.status + "_" + GlobleVariable::version);
			rar(GlobleVariable::m_workdir + "\\��װ��\\", "QWin��Ȩ���Խ���ϵͳ_" + i.status + "_" + GlobleVariable::version, ".exe");
		}
		else
		{
			MD5Info(GlobleVariable::m_workdir + "\\��װ��\\", i.qsname + "_QWin��Ȩ���Խ���ϵͳ_" + i.status + "_" + GlobleVariable::version);
			rar(GlobleVariable::m_workdir + "\\��װ��\\", i.qsname + "_QWin��Ȩ���Խ���ϵͳ_" + i.status + "_" + GlobleVariable::version, ".exe");
		}

		//�����������ļ�
		QString copy_tangert_path = GlobleVariable::m_workdir+ "\\������\\" + stats_e + "\\" + i.qsid+ "\\ALLVERSION";

		string temp_s = string(((const char*)(i.qsname).toLocal8Bit()));
		QString qs_name_abbr = QString(QString::fromLocal8Bit(strToChar(temp_s).c_str()));
		
		if ( i.only_up_pack )
		{
			copy_tangert_path = GlobleVariable::m_workdir
				+ "\\������\\" + stats_e+"_" + qs_name_abbr
				+ "\\" + i.qsid
				+ "\\ALLVERSION";
			stats_e = stats_e + "_" + qs_name_abbr;
		}

		QDir *qdir = new QDir(copy_tangert_path);
		if (!qdir->exists())
		{
			bool b = qdir->mkpath(copy_tangert_path);
		}
		
		QFile updata_ini_file(copy_tangert_path + "\\update.ini");
		
		updata_ini_file.open(QIODevice::WriteOnly | QIODevice::Truncate);
		QTextStream out(&updata_ini_file);
		out << "[BaseConfig]\n"
			<< "updatefilecount = " + QString::number(qs_file_list->size()-1,10) + "\n\n";
		int num = 0;
		for (auto updata_file : *qs_file_list)
		{
			if (updata_file.file_name == "\\vcredist_x86.exe")
				continue;
			if (!GlobleVariable::updata_ini && updata_file.file_name == "\\QyUpdate.ini")
				continue;
			
			/*
			qsrand(time(NULL));
			QByteArray bytes = (QString::number(qrand(),10)+updata_file.file_name).toLatin1();
			unsigned short us= do_crc_table((unsigned char*)bytes.data(), bytes.size());
			QString crc16 = QString::number(us, 16).toUpper();
			while (crc16.size() < 4)
				crc16 = "0" + crc16;
			
			QString up_file = "\\K" + crc16 + "_" + updata_file.file_name.section("\\", 1);
			qDebug() << up_file;
			*/
			QString copy_srce = updata_file.month_path + updata_file.mid_path + updata_file.file_name;
			QString copy_tangert = copy_tangert_path + updata_file.file_name;
			QFile::copy(copy_srce, copy_tangert);
			
			out << "[Update_" + QString::number(num++, 10) + "]\n"
				<< "filename = " + updata_file.file_name.section("\\", 1) + "\n"
				<< "srvpath = D:\\" + stats_e + "\\" + i.qsid + "\\ALLVERSION" + updata_file.file_name +"\n"
				<< "clientpath = $" + updata_file.mid_path + updata_file.file_name + "\n"
				<< "descript =\n"
				<< "clienttype = 10\n"
				<< "deparementcode = 0\n"
				<< "forceupdate = False\n"
				<< "executeenable = False\n"
				<< "groupid = 0\n"
				<< "allowsynchroupdate = False\n"
				<< "citycode = 255\n\n";
		}

		/*
		QString upinfo_file=GlobleVariable::m_workdir + "\\��׼�ļ�\\����˵��\\" + GlobleVariable::version + "\\WhatsNew.mht";
		QString to_upinfo_file=copy_tangert_path + "\\WhatsNew.mht";
		QFile::copy(upinfo_file, to_upinfo_file);
		
		out << "[Update_" + QString::number(num++, 10) + "]\n"
			<< "filename = WhatsNew.mht\n"
			<< "srvpath = D:\\" + stats_e + "\\" + i.qsid + "\\ALLVERSION\\WhatsNew.mht\n"
			<< "clientpath = $\\WhatsNew.mht\n"
			<< "descript =\n"
			<< "clienttype = 10\n"
			<< "deparementcode = 0\n"
			<< "forceupdate = False\n"
			<< "executeenable = False\n"
			<< "groupid = 0\n"
			<< "allowsynchroupdate = False\n"
			<< "citycode = 255\n\n";
		*/

		updata_ini_file.close();

		if (i.only_up_pack)
		{
			QFile::remove(GlobleVariable::m_workdir + "\\������\\"+ stats_e +".rar");
			rar(GlobleVariable::m_workdir + "\\������\\", stats_e, "");
		}
		emit progress(progress_no / GlobleVariable::pmList.size() * 100 + 5);
	}
	/*
	QFile::remove(GlobleVariable::m_workdir + "\\������\\" + "sstupdate_mn.rar");
	QFile::remove(GlobleVariable::m_workdir + "\\������\\" + "sstupdate_fz.rar");
	QFile::remove(GlobleVariable::m_workdir + "\\������\\" + "sstupdate_sc.rar");
	*/

	rar(GlobleVariable::m_workdir + "\\������\\", "sstupdate_mn", "");
	rar(GlobleVariable::m_workdir + "\\������\\", "sstupdate_qz", "");
	rar(GlobleVariable::m_workdir + "\\������\\", "sstupdate_sc", "");
	emit progress(100);
	emit progress_str("��װ��������ɣ���ȷ��");
	emit button_status(true);
}

void Controller::WriteScript()
{
	//���ɽű��ļ�
	//����ȯ�̸���
	QVector<QString> file_list;
	int rql = run_qs_list.size();

	for (size_t i = 0; i < run_qs_list.size(); i++)
	{
		QsInfo *qsinfo = new QsInfo();
		QStringToQsInfo(run_qs_list[i], qsinfo);
		if (qsinfo->qs_mn_status == "1")
		{
			QString status = "ģ��";
			file_list.append(package(qsinfo, status, NULL));
		}
		//if (qsinfo->qs_mn_sec_status == "1")
		//{
		//	QString status = "ģ��";
		//	file_list.append(package(qsinfo, status, "1"));
		//}

		if (qsinfo->qs_fz_status == "1")
		{
			QString status = "ȫ��";
			file_list.append(package(qsinfo, status, NULL));
		}

		//if (qsinfo->qs_fz_sec_status == "1")
		//{
		//	QString status = "ȫ��";
		//	file_list.append(package(qsinfo, status, "1"));
		//}

		if (qsinfo->qs_sc_status == "1")
		{
			QString status = "����";
			file_list.append(package(qsinfo, status, NULL));
		}

		//if (qsinfo->qs_sc_sec_status == "1")
		//{
		//	QString status = "����";
		//	file_list.append(package(qsinfo, status, "1"));
		//}
		emit progress((i + 1) * 85 / rql + 5);
	}

	emit progress(95);
	for (int i = 0; i < file_list.size(); i++)
	{
		//rar(file_list[i]);
		if (i % 3 == 0)
			emit progress_str("��װ��ѹ����.");
		else if (i % 3 == 1)
			emit progress_str("��װ��ѹ����..");
		else
			emit progress_str("��װ��ѹ����...");
	}
	emit progress(100);
	emit progress_str("��װ���������");
	emit button_status(true);

}

//������ д���ļ����ͻ��˰汾���ͣ�ȯ������д��ĸ�������

void Controller::WriteScript2(QFile* file, QString status, QsInfo *qs, QVector<QString> monthor_file_s, QString sec_status)
{
	//QString sec_statuss = NULL;
	//if (sec_status == "1")
	//	sec_statuss = "S";

	QString status_E;
	QString file_name = "QWin��Ȩ���Խ���ϵͳ��" + status + "��";
	if (status == "ȫ��")
		status_E = "True";
	else if (status == "ģ��")
		status_E = "Simulation";
	else
	{
		status_E = "";
		file_name = "QWin��Ȩ���Խ���ϵͳ";
	}

	//������������֤ȯ��Ҫ�������滻��ȫ��

	QString install_ico = GlobleVariable::m_workdir + "\\�����ļ�\\" + status + "\\" + "[" + qs->qs_code + "]" + qs->qs_name + "\\Res\\MockDemo.ico";
	if (!QFile(install_ico).exists())
		install_ico = "..\\��׼�ļ�\\stupico\\MockDemo.ico";

	QTextStream out(file);
	out << "!include \"MUI.nsh\"\n"
		<< "!include \"FileFunc.nsh\"\n"
		<< "!insertmacro DriveSpace\n\n"
		<< "!define PRODUCT_VERSION \"" + GlobleVariable::version + "\"\n"
		<< QStringLiteral("!define PRODUCT_NAME \"QWin��Ȩ���Խ���ϵͳ\"\n")
		<< "!define PRODUCT_QSNAME \"" + qs->qs_name + "\"\n"
		<< "!define PRODUCT_QSCODE \"" + qs->qs_code + "\"\n"
		<< "!define PRODUCT_STATUS \"" + status + "\"\n"
		<< "!define PRODUCT_STATUS_E \"" + status_E + "\"\n"
		<< "!define PRODUCT_DIR_REGKEY \"Software\\QWin\\QWinClient\"\n"
		<< "!define PRODUCT_UNINST_KEY \"Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\${PRODUCT_NAME}_${PRODUCT_QSCODE}_${PRODUCT_STATUS_E}\"\n"
		<< QStringLiteral("!define PRODUCT_COMPANY \"�Ϻ�Ǯ����Ϣ�Ƽ����޹�˾\"\n")
		<< "!define PRODUCT_FULLNAME \"" + file_name + "\"\n"
		<< "SetCompressor lzma\n"
		<< "!define MUI_ABORTWARNING\n"
		<< "!define MUI_ICON \"" + install_ico + "\"\n"
		<< QStringLiteral("!define MUI_UNICON \"..\\��׼�ļ�\\ico\\modern-uninstall.ico\"\n")
		<< QStringLiteral("!define MUI_WELCOMEFINISHPAGE_BITMAP \"..\\��׼�ļ�\\stupico\\setup.bmp\"\n\n")
		<< QStringLiteral("!define MUI_LICENSEPAGE_TEXT_TOP \"��������û�ʹ�����ȨЭ��\"\n")
		<< QStringLiteral("!define MUI_LICENSEPAGE_TEXT_BOTTOM \"������Ѿ���ϸ�Ķ������Э�飬��� �ҽ���(I) > ������װ��\"\n")
		<< QStringLiteral("!define MUI_LICENSEPAGE_BUTTON \"�ҽ���(&I) >\"\n\n")
		<< "!insertmacro MUI_PAGE_WELCOME\n"
		<< QStringLiteral("!insertmacro MUI_PAGE_LICENSE \"..\\��׼�ļ�\\Exequatur.txt\"\n")
		<< "!insertmacro MUI_PAGE_DIRECTORY\n"
		<< "!insertmacro MUI_PAGE_INSTFILES\n"
		<< "!define MUI_FINISHPAGE_RUN \"$INSTDIR\\QYMain.exe\"\n"
		<< "!insertmacro MUI_PAGE_FINISH\n"
		<< "!insertmacro MUI_UNPAGE_INSTFILES\n"
		<< "!insertmacro MUI_LANGUAGE \"SimpChinese\"\n"
		<< "!insertmacro MUI_RESERVEFILE_INSTALLOPTIONS\n"
		<< "!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN\n"
		<< "!insertmacro MUI_DESCRIPTION_TEXT ${SEC01} \"${PRODUCT_FULLNAME}\"\n"
		<< "!insertmacro MUI_FUNCTION_DESCRIPTION_END\n\n"
		<< "Name \"${PRODUCT_FULLNAME}\"\n"
		<< "OutFile \"" + GlobleVariable::m_workdir + QStringLiteral("\\��װ��\\${PRODUCT_QSNAME}_${PRODUCT_NAME}_${PRODUCT_STATUS}_${PRODUCT_VERSION}.exe\"\n\n")
		<< "VIProductVersion \"${PRODUCT_VERSION}\"\n"
		<< "VIAddVersionKey \"ProductName\" \"${PRODUCT_NAME}\"\n"
		<< "VIAddVersionKey \"Comments\" \"\"\n"
		<< "VIAddVersionKey \"CompanyName\" \"${PRODUCT_COMPANY}\"\n"
		<< "VIAddVersionKey \"LegalTrademarks\" \"\"\n"
		<< "VIAddVersionKey \"LegalCopyright\" \"${PRODUCT_COMPANY}\"\n"
		<< "VIAddVersionKey \"FileDescription\" \"${PRODUCT_NAME}\"\n"
		<< "VIAddVersionKey \"FileVersion\" \"${PRODUCT_VERSION}\"\n\n"
		<< "InstallDir \"$PROGRAMFILES\\${PRODUCT_FULLNAME}\"\n"
		<< "InstallDirRegKey HKLM \"Software\\QWin\\QWinClient\\${PRODUCT_QSCODE}\\\" \"${PRODUCT_STATUS_E}Path\"\n"
		<< "BrandingText \"${PRODUCT_COMPANY}\"\n"
		<< "ShowInstDetails show\n"
		<< "ShowUnInstDetails show\n\n"
		<< "Section \"${PRODUCT_FULLNAME}\" SEC01\n"
		<< "\tSetOutPath \"$INSTDIR\"\n"
		<< "\tSetOverwrite try\n"
		<< "\tSetOutPath \"$INSTDIR\"\n";

	for (int i = 0; i < monthor_file_s.size(); i++)
	{
		if (monthor_file_s[i].right(1) == "\\")
			out << "\tSetOutPath \"$INSTDIR" + monthor_file_s[i] << "\"\n";
		else
			out << "\tFile \"" << monthor_file_s[i] << "\"\n";
	}
	out << "\tCreateDirectory \"$SMPROGRAMS\\${PRODUCT_FULLNAME}\"\n"
		<< "\tCreateShortCut \"$SMPROGRAMS\\${PRODUCT_FULLNAME}\\${PRODUCT_FULLNAME}.lnk\" \"$INSTDIR\\QYMain.exe\" \"\" \"$INSTDIR\\Res\\MockDemo.ico\"\n"
		<< "\tCreateShortCut \"$DESKTOP\\${PRODUCT_FULLNAME}.lnk\" \"$INSTDIR\\QYMain.exe\" \"\" \"$INSTDIR\\Res\\MockDemo.ico\"\n"
		<< "\tExecWait \"regsvr32 /s $INSTDIR\\QlRtd\\QlRtd.dll\"\n"
		<< "\tExecWait \"regsvr32 /s $INSTDIR\\QlRtd\\QlRtd64.dll\"\n"
		<< "SectionEnd\n\n"
		<< "Section -AdditionalIcons\n"
		<< "\tSetOutPath $INSTDIR\n"
		<< "\tCreateShortCut \"$SMPROGRAMS\\${PRODUCT_FULLNAME}\\Uninstall.lnk\" \"$INSTDIR\\uninst.exe\"\n"
		<< "SectionEnd\n\n"
		<< "Section -Post\n"
		<< "\tWriteUninstaller \"$INSTDIR\\uninst.exe\"\n"
		<< "\tWriteRegStr HKLM \"${PRODUCT_DIR_REGKEY}\" \"\" \"$INSTDIR\\QYMain.exe\"\n"
		<< "\tWriteRegStr HKLM \"Software\\QWin\\QWinClient\\${PRODUCT_QSCODE}\\\" \"${PRODUCT_STATUS_E}Path\" \"$INSTDIR\"\n"
		<< "\tSetRegView 64\n"
		<< "\tWriteRegStr HKLM \"Software\\QWin\\QWinClient\" \"\" \"$INSTDIR\\QYMain.exe\"\n"
		<< "\tSetRegView 32\n"
		<< "\tWriteRegStr HKLM \"${PRODUCT_UNINST_KEY}\" \"DisplayName\" \"${PRODUCT_NAME}\"\n"
		<< "\tWriteRegStr HKLM \"${PRODUCT_UNINST_KEY}\" \"UninstallString\" \"$INSTDIR\\uninst.exe\"\n"
		<< "\tWriteRegStr HKLM \"${PRODUCT_UNINST_KEY}\" \"DisplayIcon\" \"$INSTDIR\\QYMain.exe\"\n"
		<< "\tWriteRegStr HKLM \"${PRODUCT_UNINST_KEY}\" \"DisplayVersion\" \"${PRODUCT_VERSION}\"\n"
		<< "\t${GetSize} \"$INSTDIR\" \"/S=0K\" $0 $1 $2\n"
		<< "\tIntFmt $0 \"0x%08X\" $0\n"
		<< "\tWriteRegDWORD HKLM \"${PRODUCT_UNINST_KEY}\" \"EstimatedSize\" $0\n"
		<< "\tWriteRegStr HKLM \"${PRODUCT_UNINST_KEY}\" \"Publisher\" \"${PRODUCT_COMPANY}\"\n"
		<< "SectionEnd\n\n"
		<< "Section\n"
		<< "\tCall CheckVCRedist\n"
		<< "SectionEnd\n\n"
		<< "Section Uninstall\n"
		<< "\tExecWait \"regsvr32 /s /u $INSTDIR\\QlRtd\\QlRtd.dll\"\n"
		<< "\tExecWait \"regsvr32 /s /u $INSTDIR\\QlRtd\\QlRtd64.dll\"\n"
		<< "\tDelete \"$SMPROGRAMS\\${PRODUCT_FULLNAME}\\Uninstall.lnk\"\n"
		<< "\tDelete \"$DESKTOP\\${PRODUCT_FULLNAME}.lnk\"\n"
		<< "\tDelete \"$SMPROGRAMS\\${PRODUCT_FULLNAME}\\${PRODUCT_FULLNAME}.lnk\"\n"
		<< "\tRMDir \"$SMPROGRAMS\\${PRODUCT_FULLNAME}\"\n"
		<< "\tRMDir /r \"$INSTDIR\"\n"
		<< "\tDeleteRegKey HKLM \"Software\\QWin\"\n"
		<< "\tDeleteRegKey HKLM \"${PRODUCT_UNINST_KEY}\"\n\n"
		<< "\tSetRegView 64\n"
		<< "\tDeleteRegKey HKLM \"Software\\QWin\"\n"
		<< "\tSetRegView 32\n"
		<< "\tSetAutoClose true\n"
		<< "SectionEnd\n\n"
		<< "Function .onInit\n"
		<< "\t${DriveSpace} \"D:\\\" \" /D=F /S=M\" $R0\n"
		<< "\t${If} $R0 = null\n"
		<< "\t\tStrCpy $R1 \"C:\\${PRODUCT_FULLNAME}\"\n"
		<< "\t${Else}\n"
		<< "\t\tStrCpy $R1 \"D:\\${PRODUCT_FULLNAME}\"\n"
		<< "\t${EndIf}\n"
		<< "\tStrCpy $INSTDIR \"$R1\"\n"
		<< "FunctionEnd\n\n"
		<< "Function InstallX86\n"
		<< "\tPush $R0\n"
		<< "\tClearErrors\n"
		<< "\tReadRegDword $R0 HKLM \"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\{9A25302D-30C0-39D9-BD6F-21E6EC160475}\" \"Version\"\n"
		<< "\tIfErrors 0 VSRedistInstalled\n"
		<< "\tClearErrors\n"
		<< "\tReadRegDword $R0 HKLM \"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\{9BE518E6-ECC6-35A9-88E4-87755C07200F}\" \"Version\"\n"
		<< "\tIfErrors 0 VSRedistInstalled\n"
		<< "\tClearErrors\n"
		<< "\tReadRegDword $R0 HKLM \"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\{86CE1746-9EFF-3C9C-8755-81EA8903AC34}\" \"Version\"\n"
		<< "\tIfErrors 0 VSRedistInstalled\n"
		<< QStringLiteral("\tMessageBox MB_ICONQUESTION|MB_YESNO \"${PRODUCT_FULLNAME} ��Ҫ��װVC++ 2008 Redistributable, �Ƿ�װ? \" IDNO VSRedistInstalled\n")
		<< "\tExecWait \"$INSTDIR\\vcredist_x86.exe /q\"\n"
		<< "\tStrCpy $R0 \"-1\"\n"
		<< "\tVSRedistInstalled:\n"
		<< "\tExch $R0\n"
		<< "FunctionEnd\n\n"
		<< "Function CheckVCRedist\n"
		<< "\tCall InstallX86\n"
		<< "\tDelete \"$INSTDIR\\vcredist_x86.exe\"\n"
		<< "FunctionEnd\n\n"
		<< "Function un.onUninstSuccess\n"
		<< "\tHideWindow\n"
		<< QStringLiteral("\tMessageBox MB_ICONINFORMATION|MB_OK \"${PRODUCT_FULLNAME} �ѳɹ��ش���ļ�����Ƴ���\"\n")
		<< "FunctionEnd\n\n"
		<< "Function un.onInit\n"
		<< QStringLiteral("\tMessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 \"��ȷʵҪ��ȫ�Ƴ� ${PRODUCT_FULLNAME} ���估���е������\" IDYES +2\n")
		<< "\tAbort\n"
		<< "FunctionEnd\n\n";
}
//������ ���ļ���·�����ļ���Ϣд����ַ������ͻ������ͣ�ģ�⣬���棬����;ȯ�����ƣ���ʽ��nameͷ����_code_name

void Controller::FindFile_old(QString path, QVector<QString> *p_file_string, QString status_dir, QString qsfile)
{
	QDir mothon_ver_dir(path);
	//���ɸ�Ŀ¼�ļ�

	foreach(QFileInfo mfi, mothon_ver_dir.entryInfoList())
	{
		QString tempfile = GlobleVariable::m_workdir + "\\�����ļ�" + qsfile + "\\" + status_dir + mfi.fileName();

		//QString temp1 = mfi.filePath();
		//QString temp2 = mfi.fileName();

		QString relative_path = mfi.filePath().mid(GlobleVariable::m_workdir.size(), mfi.filePath().size() - GlobleVariable::m_workdir.size() - 1);

		//�ļ�����
		if (mfi.isFile())
		{
			//�жϸ��ļ��Ƿ��Ƕ���
			if (QFile(tempfile).exists())
			{
				p_file_string->append("\tFile \"" + tempfile + "\"\n");
			}
			else
			{
				p_file_string->append("\tFile \"" + mfi.path() + "\\" + mfi.fileName() + "\"\n");
			}
		}
	}
	//Ŀ¼����
	foreach(QFileInfo mfi, mothon_ver_dir.entryInfoList())
	{
		QString tempfile = GlobleVariable::m_workdir + QStringLiteral("\\�����ļ�\\") + qsfile + "\\" + status_dir + "\\" + mfi.fileName();

		if (mfi.fileName() == "." || mfi.fileName() == "..")
			continue;

		if (mfi.isDir())
		{
			//�ж�ί��Ŀ¼
			//ί�и���Ŀ¼
			//�ж�Ŀ¼��ssttrade�ļ������Ŀ¼
			if (mfi.fileName() == "OrderModule"&& QFile(tempfile + "\\SSTTrade.dll").exists())
			{
				p_file_string->append("SetOutPath \"$INSTDIR\\OrderModule\n");
				FindFile_old(tempfile, p_file_string, NULL, NULL);
			}
			else if (mfi.fileName() == "QuoteModule")
			{
				//��Ҫ����
				p_file_string->append("SetOutPath \"$INSTDIR\\QuoteModule\n");
				FindFile_old(tempfile, p_file_string, NULL, NULL);
			}
			else
			{			
				p_file_string->append("SetOutPath \"$INSTDIR\\" + status_dir + mfi.fileName() + "\"\n");
				FindFile_old(mfi.absoluteFilePath(), p_file_string, status_dir + mfi.fileName() + "\\", qsfile);
			}
		}
	}
}

void Controller::FindFile(QString path, QVector<QString>* p_file_string, QString son_path)
{
	QDir mothon_ver_dir(path);

	foreach(QFileInfo mfi, mothon_ver_dir.entryInfoList())
	{
		//��ȡ���·��
		//�ļ�����
		if (mfi.isFile())
		{
			if (son_path == NULL)
			{
				p_file_string->append(son_path + "\\" + mfi.fileName());
			}
			else
			{
				p_file_string->append(son_path + mfi.fileName());
			}
		}
	}
	foreach(QFileInfo mfi, mothon_ver_dir.entryInfoList())
	{
		QString relative_path = "\\" + mfi.filePath().mid(GlobleVariable::m_workdir.size() + 20, mfi.filePath().size() - GlobleVariable::m_workdir.size() - 1) + "\\";
		relative_path.replace("/", "\\");
		if (mfi.fileName() == "." || mfi.fileName() == "..")
			continue;
		if (mfi.isDir())
		{
			p_file_string->append(relative_path);
			FindFile(mfi.absoluteFilePath(), p_file_string, relative_path);
		}
	}
}

//�����ⲿ����
//�����ű��ļ��б�
void Controller::nsis(QString args)
{
	QProcess qp;
	QStringList qsl;
	qsl << args;
	//QProcess::start�޷�ִ�У�Ӧ�������
	//qp.start(GlobleVariable::NSIS_path, qsl);
	//QProcess::startDetached(GlobleVariable::NSIS_path, qsl);
	QProcess::execute(GlobleVariable::NSIS_path, qsl);
}

void Controller::rar(QString path ,QString file_name,QString file_type)
{
	QStringList qsl, qsl2;

	qsl2 << ("a")
		<< (path + "\\" + file_name + ".rar")
		<< ("-df")
		<< ("-ep1")
		<< (path + "\\�ļ�˵��.txt");
	if (file_type == ".exe")
	{
		//QProcess::startDetached(GlobleVariable::rar_path, qsl2);
		QProcess::execute(GlobleVariable::rar_path, qsl2);
	}

	//(""%s\\rar.exe" a "%s.rar" -m5 -r -df -ep "%s.exe""
	qsl << ("a");
	//qsl << (GlobleVariable::m_workdir + "\\��װ��\\" + "QWin��Ȩ���Խ���ϵͳ�����棩(170)" + ".rar");
	qsl << (path + "\\" + file_name + ".rar");
	qsl << ("-m5");
	qsl << ("-r");
	qsl << ("-df");
	qsl << ("-ep1");
	qsl << (path + "\\" + file_name + file_type);

	QProcess::execute(GlobleVariable::rar_path, qsl);
	//QProcess::execute(GlobleVariable::rar_path, qsl);

}

void Controller::MD5Info(QString path,QString file)
{
	QString file_name(path + "\\" + file + ".exe");
	QFile install_file(file_name);
	QFileInfo install_file_info(file_name);
	
	install_file.open(QIODevice::ReadOnly);
	QByteArray ba = QCryptographicHash::hash(install_file.readAll(), QCryptographicHash::Md5);
	install_file.close();
	QString md5str = ba.toHex().constData();
	
	QFile md5_file(path+"\\�ļ�˵��.txt");
	
	if (md5_file.exists())
	{
		md5_file.remove();
	}

	md5_file.open(QIODevice::WriteOnly | QIODevice::Truncate);
	QTextStream out(&md5_file);
	
	out << file + ".exe\r\n"
		<< "Size: " + tr("%1").arg(install_file_info.size())+" bytes \r\n"
		<< "Modified: " + install_file_info.created().toString("yyyy��MM��dd�գ�HH:mm:ss") + "\r\n"
		<< "MD5: " + md5str.toUpper();

	md5_file.close();
}

void Controller::UpServer()
{
	//GlobleVariable::pmList
	emit progress_str("�ͻ����ϴ���������...");
	//qsinfo->qs_name + "_QWin��Ȩ���Խ���ϵͳ_" + status + "_" + run_ver
	for (auto i :GlobleVariable::pmList)
	{
		string s = string(((const char*)(i.qsname).toLocal8Bit()));
		QString qs_name_abbr = QString(QString::fromLocal8Bit(strToChar(s).c_str()));
		QString out_file_path = GlobleVariable::release_path
			+ "\\" + qs_name_abbr + "_" + i.qsid + "_" + i.qsname
			+ "\\" + i.status ;
		QString out_file = out_file_path + "\\" + i.qsname + "_QWin��Ȩ���Խ���ϵͳ_" + i.status + "_" + GlobleVariable::version + ".rar";
		QString filename(GlobleVariable::m_workdir 
			+ "\\��װ��\\" 
			+ i.qsname + "_QWin��Ȩ���Խ���ϵͳ_" + i.status + "_" + GlobleVariable::version + ".rar");

		if (i.qsname == "")
		{
			filename = GlobleVariable::m_workdir 
				+ "\\��װ��\\" 
				+ "QWin��Ȩ���Խ���ϵͳ_" + i.status + "_" + GlobleVariable::version + ".rar";
			out_file_path = GlobleVariable::release_path
				+ "\\" + i.qsid + "_" + i.status;
			out_file = out_file_path+ "\\""QWin��Ȩ���Խ���ϵͳ_" + i.status + "_" + GlobleVariable::version + ".rar";
		}

		filename.replace("\\", "/");
		out_file_path.replace("\\", "/");
		QDir *qdir = new QDir(out_file_path);
		QFile *up_file = new QFile(out_file);
		QFile *local_file = new QFile(filename);
		
		if (local_file->exists())
		{
			up_file->remove();
		}
		
		if (!qdir->exists())
		{
			bool b = qdir->mkpath(out_file_path);
		}

		QFile::copy(filename, out_file);
		
		/*QsInfo *qsinfo = new QsInfo;
		QStringToQsInfo(GlobleVariable::qs_list[i], qsinfo);
		
		if (qsinfo->qs_mn_status == "1")
		{
			QString status = "ģ��";
			QString file_name = GlobleVariable::m_workdir + "\\��װ��\\" + qsinfo->qs_name + "_QWin��Ȩ���Խ���ϵͳ_" + status + "_" + run_ver + ".rar";
			file_name.replace("\\", "/");
			QString out_file_path = GlobleVariable::release_path + qsinfo->qs_name_abbr + "_" + qsinfo->qs_code + "_" + qsinfo->qs_name + "\\" + status;
			out_file_path.replace("\\", "/");

			bool b = QFile::copy(GlobleVariable::m_workdir + "\\��װ��\\" + file_name,
				GlobleVariable::release_path + "\\" + qsinfo->qs_name_abbr + "_" + qsinfo->qs_code + "_" + qsinfo->qs_name + "\\" + status);
		}*/
	}
	emit progress_str("�ͻ����ϴ�������...���");
}

void Controller::FindFile_2(QString path, QVector<FileInfo>* p_file_string, QString son_path)
{
	QDir mothon_ver_dir(path + son_path);
	FileInfo *file_info;

	foreach(QFileInfo mfi, mothon_ver_dir.entryInfoList())
	{
		//��ȡ���·��
		//�ļ�����
		if (mfi.isFile())
		{
			file_info = new FileInfo();
			file_info->month_path = path;
			file_info->mid_path = son_path;
			file_info->file_name = "\\" + mfi.fileName();
			p_file_string->append(*file_info);
		}
	}
	foreach(QFileInfo mfi, mothon_ver_dir.entryInfoList())
	{
		if (mfi.fileName() == "." || mfi.fileName() == "..")
			continue;
		if (mfi.isDir())
			FindFile_2(path, p_file_string, son_path + "\\" + mfi.fileName());
	}
}

//������ȯ���б�
void Controller::WriteScript_2(pminfo pm_info, QFile* file, QVector<FileInfo>* file_list)
{
	//д�ű�
	//���
	//ѹ������

	QString status_E = "";
	QString file_name = "QWin��Ȩ���Խ���ϵͳ��" + pm_info.status + "��";
	QString exequatur_txt = "..\\��׼�ļ�\\Exequatur.txt";
	if (pm_info.status == "ȫ��" || pm_info.status == "����")
		status_E = "True";
	else if (pm_info.status == "ģ��")
		status_E = "Simulation";
	else
		file_name = "QWin��Ȩ���Խ���ϵͳ";

	QString install_ico = GlobleVariable::m_workdir + "\\�����ļ�\\" + pm_info.status + "\\" + "[" + pm_info.qsid + "]" + pm_info.qsname + "\\Res\\MockDemo.ico";
	
	if (pm_info.qsname == "����֤ȯ")
	{
		exequatur_txt = "..\\�����ļ�\\ȫ��\\[" + pm_info.qsid + "]" + pm_info.qsname + "\\Exequatur.txt";
		install_ico = GlobleVariable::m_workdir + "\\�����ļ�\\ȫ��\\[" + pm_info.qsid + "]" + pm_info.qsname + "\\Res\\MockDemo.ico";
		if (pm_info.status=="����")
		{
			install_ico = GlobleVariable::m_workdir + "\\�����ļ�\\����\\[" + pm_info.qsid + "]" + pm_info.qsname + "\\Res\\MockDemo.ico";
		}
	}

	if (!QFile(install_ico).exists())
	{
		install_ico = "..\\��׼�ļ�\\stupico\\MockDemo.ico";
	}


	QString out_file_name = "${PRODUCT_QSNAME}_${PRODUCT_NAME}_${PRODUCT_STATUS}_${PRODUCT_VERSION}.exe";
	if (pm_info.qsname == "")
	{
		out_file_name = "${PRODUCT_NAME}_${PRODUCT_STATUS}_${PRODUCT_VERSION}.exe";
	}

	QTextStream out(file);
	out << "!include \"MUI.nsh\"\n"
		<< "!include \"FileFunc.nsh\"\n"
		<< "!insertmacro DriveSpace\n\n"
		<< "!define PRODUCT_VERSION \"" + GlobleVariable::version + "\"\n"
		<< QStringLiteral("!define PRODUCT_NAME \"QWin��Ȩ���Խ���ϵͳ\"\n")
		<< "!define PRODUCT_QSNAME \"" + pm_info.qsname + "\"\n"
		<< "!define PRODUCT_QSCODE \"" + pm_info.qsid + "\"\n"
		<< "!define PRODUCT_STATUS \"" + pm_info.status + "\"\n"
		<< "!define PRODUCT_STATUS_E \"" + status_E + "\"\n"
		<< "!define PRODUCT_DIR_REGKEY \"Software\\QWin\\QWinClient\"\n"
		<< "!define PRODUCT_UNINST_KEY \"Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\${PRODUCT_NAME}_${PRODUCT_QSCODE}_${PRODUCT_STATUS_E}\"\n"
		<< QStringLiteral("!define PRODUCT_COMPANY \"�Ϻ�Ǯ����Ϣ�Ƽ����޹�˾\"\n")
		<< "!define PRODUCT_FULLNAME \"" + file_name + "\"\n"
		<< "SetCompressor lzma\n"
		<< "!define MUI_ABORTWARNING\n"
		<< "!define MUI_ICON \"" + install_ico + "\"\n"
		<< QStringLiteral("!define MUI_UNICON \"..\\��׼�ļ�\\ico\\modern-uninstall.ico\"\n")
		<< QStringLiteral("!define MUI_WELCOMEFINISHPAGE_BITMAP \"..\\��׼�ļ�\\stupico\\setup.bmp\"\n\n")
		<< QStringLiteral("!define MUI_LICENSEPAGE_TEXT_TOP \"��������û�ʹ�����ȨЭ��\"\n")
		<< QStringLiteral("!define MUI_LICENSEPAGE_TEXT_BOTTOM \"������Ѿ���ϸ�Ķ������Э�飬��� �ҽ���(I) > ������װ��\"\n")
		<< QStringLiteral("!define MUI_LICENSEPAGE_BUTTON \"�ҽ���(&I) >\"\n\n")
		<< "!insertmacro MUI_PAGE_WELCOME\n"
		<< "!insertmacro MUI_PAGE_LICENSE \"" + exequatur_txt + "\"\n"
		<< "!insertmacro MUI_PAGE_DIRECTORY\n"
		<< "!insertmacro MUI_PAGE_INSTFILES\n"
		<< "!define MUI_FINISHPAGE_RUN \"$INSTDIR\\QYMain.exe\"\n"
		<< "!insertmacro MUI_PAGE_FINISH\n"
		<< "!insertmacro MUI_UNPAGE_INSTFILES\n"
		<< "!insertmacro MUI_LANGUAGE \"SimpChinese\"\n"
		<< "!insertmacro MUI_RESERVEFILE_INSTALLOPTIONS\n"
		<< "!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN\n"
		<< "!insertmacro MUI_DESCRIPTION_TEXT ${SEC01} \"${PRODUCT_FULLNAME}\"\n"
		<< "!insertmacro MUI_FUNCTION_DESCRIPTION_END\n\n"
		<< "Name \"${PRODUCT_FULLNAME}\"\n"
		<< "OutFile \"" + GlobleVariable::m_workdir + QStringLiteral("\\��װ��\\") + out_file_name + "\"\n\n"
		<< "VIProductVersion \"${PRODUCT_VERSION}\"\n"
		<< "VIAddVersionKey \"ProductName\" \"${PRODUCT_NAME}\"\n"
		<< "VIAddVersionKey \"Comments\" \"\"\n"
		<< "VIAddVersionKey \"CompanyName\" \"${PRODUCT_COMPANY}\"\n"
		<< "VIAddVersionKey \"LegalTrademarks\" \"\"\n"
		<< "VIAddVersionKey \"LegalCopyright\" \"${PRODUCT_COMPANY}\"\n"
		<< "VIAddVersionKey \"FileDescription\" \"${PRODUCT_NAME}\"\n"
		<< "VIAddVersionKey \"FileVersion\" \"${PRODUCT_VERSION}\"\n\n"
		<< "InstallDir \"$PROGRAMFILES\\${PRODUCT_FULLNAME}\"\n"
		<< "InstallDirRegKey HKLM \"Software\\QWin\\QWinClient\\${PRODUCT_QSCODE}\\\" \"${PRODUCT_STATUS_E}Path\"\n"
		<< "BrandingText \"${PRODUCT_COMPANY}\"\n"
		<< "ShowInstDetails show\n"
		<< "ShowUnInstDetails show\n\n"
		<< "Section \"${PRODUCT_FULLNAME}\" SEC01\n"
		<< "\tSetOutPath \"$INSTDIR\"\n"
		<< "\tSetOverwrite try\n"
		<< "\tSetOutPath \"$INSTDIR\"\n";

	//for (int i = 0; i < file_list.size(); i++)
	//{
	//	if (monthor_file_s[i].right(1) == "\\")
	//		out << "\tSetOutPath \"$INSTDIR" + monthor_file_s[i] << "\"\n";
	//	else
	//		out << "\tFile \"" << monthor_file_s[i] << "\"\n";
	//}

	QString mid_path;
	mid_path = "";
	for (auto i : *file_list)
	{
		if (i.mid_path != mid_path)
		{
			out << "\tSetOutPath \"$INSTDIR" + i.mid_path << "\"\n";
			mid_path = i.mid_path;
		}
		out << "\tFile \"" << i.month_path + i.mid_path + i.file_name << "\"\n";
	}
	out << "\tCreateDirectory \"$SMPROGRAMS\\${PRODUCT_FULLNAME}\"\n"
		<< "\tCreateShortCut \"$SMPROGRAMS\\${PRODUCT_FULLNAME}\\${PRODUCT_FULLNAME}.lnk\" \"$INSTDIR\\QYMain.exe\" \"\" \"$INSTDIR\\Res\\MockDemo.ico\"\n"
		<< "\tCreateShortCut \"$DESKTOP\\${PRODUCT_FULLNAME}.lnk\" \"$INSTDIR\\QYMain.exe\" \"\" \"$INSTDIR\\Res\\MockDemo.ico\"\n"
		<< "\tExecWait \"regsvr32 /s $INSTDIR\\QlRtd\\QlRtd.dll\"\n"
		<< "\tExecWait \"regsvr32 /s $INSTDIR\\QlRtd\\QlRtd64.dll\"\n"
		<< "SectionEnd\n\n"
		<< "Section -AdditionalIcons\n"
		<< "\tSetOutPath $INSTDIR\n"
		<< "\tCreateShortCut \"$SMPROGRAMS\\${PRODUCT_FULLNAME}\\Uninstall.lnk\" \"$INSTDIR\\uninst.exe\"\n"
		<< "SectionEnd\n\n"
		<< "Section -Post\n"
		<< "\tWriteUninstaller \"$INSTDIR\\uninst.exe\"\n"
		<< "\tWriteRegStr HKLM \"${PRODUCT_DIR_REGKEY}\" \"\" \"$INSTDIR\\QYMain.exe\"\n"
		<< "\tWriteRegStr HKLM \"Software\\QWin\\QWinClient\\${PRODUCT_QSCODE}\\\" \"${PRODUCT_STATUS_E}Path\" \"$INSTDIR\"\n"
		<< "\tSetRegView 64\n"
		<< "\tWriteRegStr HKLM \"Software\\QWin\\QWinClient\" \"\" \"$INSTDIR\\QYMain.exe\"\n"
		<< "\tSetRegView 32\n"
		<< "\tWriteRegStr HKLM \"${PRODUCT_UNINST_KEY}\" \"DisplayName\" \"${PRODUCT_NAME}\"\n"
		<< "\tWriteRegStr HKLM \"${PRODUCT_UNINST_KEY}\" \"UninstallString\" \"$INSTDIR\\uninst.exe\"\n"
		<< "\tWriteRegStr HKLM \"${PRODUCT_UNINST_KEY}\" \"DisplayIcon\" \"$INSTDIR\\QYMain.exe\"\n"
		<< "\tWriteRegStr HKLM \"${PRODUCT_UNINST_KEY}\" \"DisplayVersion\" \"${PRODUCT_VERSION}\"\n"
		<< "\t${GetSize} \"$INSTDIR\" \"/S=0K\" $0 $1 $2\n"
		<< "\tIntFmt $0 \"0x%08X\" $0\n"
		<< "\tWriteRegDWORD HKLM \"${PRODUCT_UNINST_KEY}\" \"EstimatedSize\" $0\n"
		<< "\tWriteRegStr HKLM \"${PRODUCT_UNINST_KEY}\" \"Publisher\" \"${PRODUCT_COMPANY}\"\n"
		<< "SectionEnd\n\n"
		<< "Section\n"
		<< "\tCall CheckVCRedist\n"
		<< "SectionEnd\n\n"
		<< "Section Uninstall\n"
		<< "\tExecWait \"regsvr32 /s /u $INSTDIR\\QlRtd\\QlRtd.dll\"\n"
		<< "\tExecWait \"regsvr32 /s /u $INSTDIR\\QlRtd\\QlRtd64.dll\"\n"
		<< "\tDelete \"$SMPROGRAMS\\${PRODUCT_FULLNAME}\\Uninstall.lnk\"\n"
		<< "\tDelete \"$DESKTOP\\${PRODUCT_FULLNAME}.lnk\"\n"
		<< "\tDelete \"$SMPROGRAMS\\${PRODUCT_FULLNAME}\\${PRODUCT_FULLNAME}.lnk\"\n"
		<< "\tRMDir \"$SMPROGRAMS\\${PRODUCT_FULLNAME}\"\n"
		<< "\tRMDir /r \"$INSTDIR\"\n"
		<< "\tDeleteRegKey HKLM \"Software\\QWin\"\n"
		<< "\tDeleteRegKey HKLM \"${PRODUCT_UNINST_KEY}\"\n\n"
		<< "\tSetRegView 64\n"
		<< "\tDeleteRegKey HKLM \"Software\\QWin\"\n"
		<< "\tSetRegView 32\n"
		<< "\tSetAutoClose true\n"
		<< "SectionEnd\n\n"
		<< "Function .onInit\n"
		<< "\t${DriveSpace} \"D:\\\" \" /D=F /S=M\" $R0\n"
		<< "\t${If} $R0 = null\n"
		<< "\t\tStrCpy $R1 \"C:\\${PRODUCT_FULLNAME}\"\n"
		<< "\t${Else}\n"
		<< "\t\tStrCpy $R1 \"D:\\${PRODUCT_FULLNAME}\"\n"
		<< "\t${EndIf}\n"
		<< "\tStrCpy $INSTDIR \"$R1\"\n"
		<< "FunctionEnd\n\n"
		<< "Function InstallX86\n"
		<< "\tPush $R0\n"
		<< "\tClearErrors\n"
		<< "\tReadRegDword $R0 HKLM \"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\{9A25302D-30C0-39D9-BD6F-21E6EC160475}\" \"Version\"\n"
		<< "\tIfErrors 0 VSRedistInstalled\n"
		<< "\tClearErrors\n"
		<< "\tReadRegDword $R0 HKLM \"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\{9BE518E6-ECC6-35A9-88E4-87755C07200F}\" \"Version\"\n"
		<< "\tIfErrors 0 VSRedistInstalled\n"
		<< "\tClearErrors\n"
		<< "\tReadRegDword $R0 HKLM \"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\{86CE1746-9EFF-3C9C-8755-81EA8903AC34}\" \"Version\"\n"
		<< "\tIfErrors 0 VSRedistInstalled\n"
		<< QStringLiteral("\tMessageBox MB_ICONQUESTION|MB_YESNO \"${PRODUCT_FULLNAME} ��Ҫ��װVC++ 2008 Redistributable, �Ƿ�װ? \" IDNO VSRedistInstalled\n")
		<< "\tExecWait \"$INSTDIR\\vcredist_x86.exe /q\"\n"
		<< "\tStrCpy $R0 \"-1\"\n"
		<< "\tVSRedistInstalled:\n"
		<< "\tExch $R0\n"
		<< "FunctionEnd\n\n"
		<< "Function CheckVCRedist\n"
		<< "\tCall InstallX86\n"
		<< "\tDelete \"$INSTDIR\\vcredist_x86.exe\"\n"
		<< "FunctionEnd\n\n"
		<< "Function un.onUninstSuccess\n"
		<< "\tHideWindow\n"
		<< QStringLiteral("\tMessageBox MB_ICONINFORMATION|MB_OK \"${PRODUCT_FULLNAME} �ѳɹ��ش���ļ�����Ƴ���\"\n")
		<< "FunctionEnd\n\n"
		<< "Function un.onInit\n"
		<< QStringLiteral("\tMessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 \"��ȷʵҪ��ȫ�Ƴ� ${PRODUCT_FULLNAME} ���估���е������\" IDYES +2\n")
		<< "\tAbort\n"
		<< "FunctionEnd\n\n";

}

bool caseInsensitiveLessThan(FileInfo &fi1, FileInfo &fi2)
{
	if (fi1.mid_path == fi2.mid_path)
		return fi1.file_name < fi2.file_name;
	return fi1.mid_path < fi2.mid_path;
}

QVector<FileInfo> Controller::MergeDir_2(QVector<FileInfo> *fst_file_list, QVector<FileInfo> *sec_file_list)
{
	QVector<FileInfo> out_file;
	out_file = *sec_file_list;

	//�ϲ�2��Ŀ¼
	for (auto i : *fst_file_list)
	{
		bool file_exist = false;
		for (auto j : out_file)
		{
			if ((i.mid_path + i.file_name) == (j.mid_path + j.file_name))
			{
				j = i;
				file_exist = true;
				break;
			}
		}
		if (!file_exist)
		{
			out_file.append(i);
		}
	}

	//�ж�Ŀ¼���Ƿ���SSTTrade.ini
	for (auto i : *sec_file_list)
	{
		if (i.file_name == "\\SSTTrade.ini")
		{
			for (int j = 0; j < out_file.size(); j++)
			{
				//�����ļ�
				//if (out_file[j].file_name == "\\OrderModule\\SSTTrade.dll")
				//	continue;

				if (out_file[j]	.mid_path.startsWith("\\OrderModule"))
				{
					out_file.remove(j--);
				}
			}

			for (auto j : *sec_file_list)
			{
				if (j.mid_path.startsWith("\\OrderModule"))
				{
					out_file.append(j);
				}
			}
			break;
		}
	}
	//�ж��ļ��е�QuoteClientApi.ini
	for (auto i : *sec_file_list)
	{
		if (i.file_name == "\\QuoteClientApi.ini")
		{

			for (int j = 0; j < out_file.size(); j++)
			{
				//�����ļ�
				//if (out_file[j].file_name == "\\OrderModule\\SSTTrade.dll")
				//	continue;

				if (out_file[j].mid_path.startsWith("\\QuoteModule"))
				{
					out_file.remove(j--);
				}
			}

			for (auto i : *sec_file_list)
			{
				if (i.mid_path.startsWith("\\QuoteModule"))
				{
					out_file.append(i);
				}
			}

			FileInfo fitemp;
			fitemp.month_path = (*fst_file_list)[0].month_path;
			fitemp.mid_path = "\\QuoteModule";
			fitemp.file_name = "\\QuoteClientApi.dll" ;
			out_file.append(fitemp);

			QSettings  market_list_ini(i.month_path + "\\QuoteModule\\QuoteClientApi.ini", QSettings::IniFormat);
			QStringList groupList = market_list_ini.childGroups();
			foreach(QString group, groupList)
			{
				if (group != "ServerName")
				{
					fitemp.month_path = (*fst_file_list)[0].month_path;
					fitemp.mid_path = "\\QuoteModule\\" + market_list_ini.value(group + "/keyfile").toString().section("/", 1, 1);
					fitemp.file_name = "\\" + market_list_ini.value(group + "/keyfile").toString().section("/", -1);

					out_file.append(fitemp);
				}
			}
			break;
		}
	}

	qSort(out_file.begin(), out_file.end(), caseInsensitiveLessThan);
	//qSort(out_file.begin(), out_file.end(), caseInsensitiveLessThan);

	return out_file;
}

void Controller::init()
{
	emit progress_str("�����ʼ����...");
	FindFile_2(GlobleVariable::m_workdir + "\\��׼�ļ�\\binR_Internet", &GlobleVariable::monthor_file_2, "");
	FindFile_2(GlobleVariable::m_workdir + "\\��׼�ļ�\\ģ��", &GlobleVariable::simulation_env_file, "");
	FindFile_2(GlobleVariable::m_workdir + "\\��׼�ļ�\\ȫ��", &GlobleVariable::true_env_file, "");
	FindFile_2(GlobleVariable::m_workdir + "\\��׼�ļ�\\����", &GlobleVariable::produce_env_file, "");
	GlobleVariable::simulation_env_file = MergeDir_2(&GlobleVariable::monthor_file_2, &GlobleVariable::simulation_env_file);
	GlobleVariable::true_env_file = MergeDir_2(&GlobleVariable::monthor_file_2, &GlobleVariable::true_env_file);
	GlobleVariable::produce_env_file = MergeDir_2(&GlobleVariable::monthor_file_2, &GlobleVariable::produce_env_file);
	emit progress_str("");

	/*����Ϊ��������
	QFile f("D:\\monthor_file.txt"),f2("D:\\simulation_env_file.txt");
	f.open(QIODevice::WriteOnly | QIODevice::Text);
	f2.open(QIODevice::WriteOnly | QIODevice::Text);
	QTextStream txtOutput(&f),txtOutput2(&f2);
	for (FileInfo i : GlobleVariable::monthor_file_2)
	{
	txtOutput << i.month_path << "\t" <<i.mid_path<<"\t"<< i.file_name << "\n";
	}
	for (FileInfo i : mn1)
	{
	txtOutput2 << i.month_path << "\t" <<i.mid_path<<"\t"<< i.file_name << "\n";
	}
	f.close();
	f2.close();

	����Ϊ��������
	*/
}

void Controller::UPPackage()
{
	QVector<FileInfo>* qs_file_list;
	int progress_no = 0;
	for (auto i : GlobleVariable::pmList)
	{
		QString stats_e;
		emit progress_str("���ڴ������Ŀ¼�����Ժ�...");

		qs_file_list = new QVector<FileInfo>();
		FindFile_2(GlobleVariable::m_workdir + "\\�����ļ�\\" + i.status + "\\[" + i.qsid + "]" + i.qsname,
			qs_file_list,
			"");
		if (i.status == "ģ��")
		{
			*qs_file_list = MergeDir_2(&(GlobleVariable::simulation_env_file), qs_file_list);
			stats_e = "sstupdate_mn";
		}
		else if (i.status == "ȫ��")
		{

			*qs_file_list = MergeDir_2(&(GlobleVariable::true_env_file), qs_file_list);
			stats_e = "sstupdate_qz";

			if (i.qsname == "����֤ȯ")
			{
				i.status = "����";
			}
		}
		else if (i.status == "����")
		{
			*qs_file_list = MergeDir_2(&(GlobleVariable::produce_env_file), qs_file_list);
			stats_e = "sstupdate_sc";
		}
		else
			QMessageBox(QMessageBox::Warning, "����", "���ִ����·��Ӧ���ڣ�����Ĵ���", QMessageBox::Ok);
				
		//�����������ļ�
		QString copy_target_path = GlobleVariable::m_workdir + "\\������\\" + stats_e + "\\" + i.qsid + "\\ALLVERSION";

		string temp_s = string(((const char*)(i.qsname).toLocal8Bit()));
		QString qs_name_abbr = QString(QString::fromLocal8Bit(strToChar(temp_s).c_str()));

		if (i.only_up_pack)
		{
			copy_target_path = GlobleVariable::m_workdir
				+ "\\������\\" + stats_e + "_" + qs_name_abbr
				+ "\\" + i.qsid
				+ "\\ALLVERSION";
			stats_e = stats_e + "_" + qs_name_abbr;
		}

		QDir *qdir = new QDir(copy_target_path);
		if (!qdir->exists())
		{
			bool b = qdir->mkpath(copy_target_path);
		}

		QFile updata_ini_file(copy_target_path + "\\update.ini");

		updata_ini_file.open(QIODevice::WriteOnly | QIODevice::Truncate);
		QTextStream out(&updata_ini_file);
		out << "[BaseConfig]\n"
			<< "updatefilecount = " + QString::number(qs_file_list->size()-1, 10) + "\n\n";
		int num = 0;
		for (auto updata_file : *qs_file_list)
		{
			if (updata_file.file_name == "\\vcredist_x86.exe")
				continue;
			if (!GlobleVariable::updata_ini && updata_file.file_name == "\\QyUpdate.ini")
				continue;

			QString copy_srce = updata_file.month_path + updata_file.mid_path + updata_file.file_name;
			QString copy_tangert = copy_target_path + updata_file.file_name;
			QFile::copy(copy_srce, copy_tangert);

			out << "[Update_" + QString::number(num++, 10) + "]\n"
				<< "filename = " + updata_file.file_name.section("\\", 1) + "\n"
				<< "srvpath = D:\\" + stats_e + "\\" + i.qsid + "\\ALLVERSION" + updata_file.file_name + "\n"
				<< "clientpath = $" + updata_file.mid_path + updata_file.file_name + "\n"
				<< "descript =\n"
				<< "clienttype = 10\n"
				<< "deparementcode = 0\n"
				<< "forceupdate = False\n"
				<< "executeenable = False\n"
				<< "groupid = 0\n"
				<< "allowsynchroupdate = False\n"
				<< "citycode = 255\n\n";
		}
		
		/*
		QString upinfo_file = GlobleVariable::m_workdir + "\\��׼�ļ�\\����˵��\\" + GlobleVariable::version + "\\WhatsNew.mht";
		QString to_upinfo_file = copy_target_path + "\\WhatsNew.mht";
		QFile::copy(upinfo_file, to_upinfo_file);

		out << "[Update_" + QString::number(num++, 10) + "]\n"
			<< "filename = WhatsNew.mht\n"
			<< "srvpath = D:\\" + stats_e + "\\" + i.qsid + "\\ALLVERSION\\WhatsNew.mht\n"
			<< "clientpath = $\\WhatsNew.mht\n"
			<< "descript =\n"
			<< "clienttype = 10\n"
			<< "deparementcode = 0\n"
			<< "forceupdate = False\n"
			<< "executeenable = False\n"
			<< "groupid = 0\n"
			<< "allowsynchroupdate = False\n"
			<< "citycode = 255\n\n";

		*/

		updata_ini_file.close();

		if (i.only_up_pack)
		{
			QFile::remove(GlobleVariable::m_workdir + "\\������\\" + stats_e + ".rar");
			rar(GlobleVariable::m_workdir + "\\������\\", stats_e, "");
		}
		emit progress(progress_no / GlobleVariable::pmList.size() * 100 + 5);
	}

	rar(GlobleVariable::m_workdir + "\\������\\", "sstupdate_mn", "");
	rar(GlobleVariable::m_workdir + "\\������\\", "sstupdate_qz", "");
	rar(GlobleVariable::m_workdir + "\\������\\", "sstupdate_sc", "");
	emit progress(100);
	emit progress_str("��װ��������ɣ���ȷ��");
	emit button_status(true);
}

void Controller::DisplayPath()
{

}