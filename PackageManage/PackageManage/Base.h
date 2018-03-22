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

#pragma execution_character_set("utf-8")	//���ı��룬��˵�Ѿ�ʧЧ������5.6�汾����Ч

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
	bool only_up_pack=false;				//������װ��־��Ĭ��Ϊfalse
};

class GlobleVariable
{
public:
	static QString m_workdir;						//����Ŀ¼
	static QVector<QString> ver_string;			//�汾�б�
	static QVector<QString> qs_list;				//ȯ���б�
	static QFile m_cfg_file;
	static QString m_cfg_name;		//�����ļ�����
	static int count;
	static QString status;							//�ͻ��˰汾״̬��6λ���ֱ�Ϊģ�⣬ģ��sec�����棬����sec������������sec
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
	static bool updata_ini;							//���������ļ� QlUpdate.ini�Ƿ�����������У�Ĭ��false��������
};

struct QsInfo
{
	QString qs_name;							//ȯ������
	QString qs_code;						//ȯ�̱���
	QString qs_name_abbr;					//������д
	QString qs_mn_status;					//ģ��״̬
	QString qs_mn_sec_status;				//ģ����ο����汾״̬
	QString qs_fz_status;
	QString qs_fz_sec_status;
	QString qs_sc_status;
	QString qs_sc_sec_status;
};

/*
static QString g_workdir;						//����Ŀ¼
static QVector<QString> ver_string;			//�汾�б�
static QVector<QsInfo> qs_list;				//ȯ���б�
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