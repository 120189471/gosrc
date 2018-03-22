#ifndef __BASE_H__
#define __BASE_H__

#include <iostream>
#include <string>
using namespace std;

#include <QtWidgets/QMainWindow>
#include <QFile>
#include <QTextCodec>
#include <QDebug>
#include <iomanip>

#pragma execution_character_set("utf-8")	//中文编码，据说已经失效，但在5.6版本还有效

struct FileInfo
{
	QString month_path;
	QString mid_path;
	QString file_name;
};
struct pminfo
{
	QString qsname;
	QString qsid;
	QString status;
	bool only_up_pack=false;				//独立安装标志，默认为false
};

class GlobleVariable
{
public:
	static QString m_workdir;						//工作目录
	static QVector<QString> ver_string;			//版本列表
	static QVector<QString> qs_list;				//券商列表
	static QFile m_cfg_file;
	static QString m_cfg_name;		//配置文件名称
	static int count;
	static QString status;							//客户端版本状态，6位，分别为模拟，模拟sec，仿真，仿真sec，生产，生产sec
	static QString rar_path;
	static QString NSIS_path;
	static QString VMP_path;
	static QString version;
	static QVector<QString> monthor_file;
	static QVector<FileInfo> monthor_file_2;
	static QVector<FileInfo> simulation_env_file;
	static QVector<FileInfo> true_env_file;
	static QVector<FileInfo> produce_env_file;
	static QString release_path;
	static QVector<pminfo> pmList;
	static bool updata_ini;							//升级配置文件 QlUpdate.ini是否放在升级包中，默认false，不更新
};

struct QsInfo
{
	QString qs_name;							//券商名称
	QString qs_code;						//券商编码
	QString qs_name_abbr;					//名字缩写
	QString qs_mn_status;					//模拟状态
	QString qs_mn_sec_status;				//模拟二次开发版本状态
	QString qs_fz_status;
	QString qs_fz_sec_status;
	QString qs_sc_status;
	QString qs_sc_sec_status;
};

/*
static QString g_workdir;						//工作目录
static QVector<QString> ver_string;			//版本列表
static QVector<QsInfo> qs_list;				//券商列表
static QFile g_cfg_file;
*/

void infotoini(QString, QString);
void QStringToQsInfo(QString, QsInfo*);

void FirstLetter(int, char& );
void GetFirstLetter(char*, char*, int);

static char convert(wchar_t );
static bool In(wchar_t , wchar_t , wchar_t );

string strToChar(string );

unsigned short do_crc_table(unsigned char* , int );

#endif