#include "Base.h"
#include "qsettings.h"

QString				GlobleVariable::m_workdir;						//工作目录 QVector<QString> ver_string;			//版本列表
QVector<QString>	GlobleVariable::qs_list;				//券商列表
QFile				GlobleVariable::m_cfg_file;
QString				GlobleVariable::m_cfg_name = "PackageManage.ini";		//配置文件名称
int					GlobleVariable::count;
QString				GlobleVariable::status;							//客户端版本状态，6位，分别为模拟，模拟sec，仿真，仿真sec，生产，生产sec
QString				GlobleVariable::rar_path;
QString				GlobleVariable::NSIS_path;
QString				GlobleVariable::VMP_path;
QString				GlobleVariable::version = "";
QVector<QString>	GlobleVariable::monthor_file;					//母版文件列表
QVector<FileInfo>	GlobleVariable::monthor_file_2;					//母版文件列表
QVector<FileInfo>	GlobleVariable::simulation_env_file;			//模拟环境文件列表
QVector<FileInfo>	GlobleVariable::true_env_file;					//全真环境文件列表
QVector<FileInfo>	GlobleVariable::produce_env_file;				//生产环境文件列表
QString				GlobleVariable::release_path;
QVector<pminfo>		GlobleVariable::pmList;
bool				GlobleVariable::updata_ini = false;

//添加ini文件，因为有指针需要释放，所以将单独列出方法
void infotoini(QString key, QString value)
{
	QSettings *g_cfg = new QSettings(GlobleVariable::m_cfg_name, QSettings::IniFormat);
	//配置文件中文显示
	g_cfg->setIniCodec(QTextCodec::codecForName("utf-8"));
	g_cfg->setValue(key, value);
	delete g_cfg;
}

//将券商信息展开
void QStringToQsInfo(QString qs_list_x, QsInfo *qsinfo)
{
	//char *QSstatus;
	//QByteArray qbytearr;
	QStringList strlist = qs_list_x.split("|");
	qsinfo->qs_name = strlist[0];
	qsinfo->qs_code = strlist[1];
	//qbytearr = strlist[2].toUtf8();
	//QSstatus = qbytearr.data();

	string s = string(((const char*)(qsinfo->qs_name).toLocal8Bit()));
	qsinfo->qs_name_abbr = QString(QString::fromLocal8Bit(strToChar(s).c_str()));

	qsinfo->qs_mn_status = strlist[2].mid(0, 1);
	qsinfo->qs_mn_sec_status = strlist[2].mid(1, 1);
	qsinfo->qs_fz_status = strlist[2].mid(2, 1);
	qsinfo->qs_fz_sec_status = strlist[2].mid(3, 1);
	qsinfo->qs_sc_status = strlist[2].mid(4, 1);
	qsinfo->qs_sc_sec_status = strlist[2].mid(5, 1);
}

void GetFirstLetter(char* strName, char* strFirstLetter, int nLen)
{
	int ucHigh, ucLow;
	int nCode;
	char strRet;
	memset(strFirstLetter, 0, sizeof(nLen));
	int len = 0;
	int nameLen = (int)strlen(strName);
	for (int i = 0; i < nameLen; i += 2)
	{
		ucHigh = (int)(strName[i + 0] & 0xFF);
		ucLow = (int)(strName[i + 1] & 0xFF);
		if (ucHigh < 0xa1 || ucLow < 0xa1)
		{
			continue;
		}
		else
		{
			nCode = (ucHigh - 0xa0) * 100 + ucLow - 0xa0;
		}
		FirstLetter(nCode, strRet);
		strFirstLetter[len] = strRet;
		len++;
	}
	strFirstLetter[len] = '\0';
}
void FirstLetter(int nCode, char& strLetter)
{
	if (nCode >= 1601 && nCode < 1637) strLetter = 'A';
	if (nCode >= 1637 && nCode < 1833) strLetter = 'B';
	if (nCode >= 1833 && nCode < 2078) strLetter = 'C';
	if (nCode >= 2078 && nCode < 2274) strLetter = 'D';
	if (nCode >= 2274 && nCode < 2302) strLetter = 'E';
	if (nCode >= 2302 && nCode < 2433) strLetter = 'F';
	if (nCode >= 2433 && nCode < 2594) strLetter = 'G';
	if (nCode >= 2594 && nCode < 2787) strLetter = 'H';
	if (nCode >= 2787 && nCode < 3106) strLetter = 'J';
	if (nCode >= 3106 && nCode < 3212) strLetter = 'K';
	if (nCode >= 3212 && nCode < 3472) strLetter = 'L';
	if (nCode >= 3472 && nCode < 3635) strLetter = 'M';
	if (nCode >= 3635 && nCode < 3722) strLetter = 'N';
	if (nCode >= 3722 && nCode < 3730) strLetter = 'O';
	if (nCode >= 3730 && nCode < 3858) strLetter = 'P';
	if (nCode >= 3858 && nCode < 4027) strLetter = 'Q';
	if (nCode >= 4027 && nCode < 4086) strLetter = 'R';
	if (nCode >= 4086 && nCode < 4390) strLetter = 'S';
	if (nCode >= 4390 && nCode < 4558) strLetter = 'T';
	if (nCode >= 4558 && nCode < 4684) strLetter = 'W';
	if (nCode >= 4684 && nCode < 4925) strLetter = 'X';
	if (nCode >= 4925 && nCode < 5249) strLetter = 'Y';
	if (nCode >= 5249 && nCode < 5590) strLetter = 'Z';
}

string strToChar(string sChinese)
{
	//string 	sChinese = "我是中国人"; // 输入的字符串

	char chr[3];
	wchar_t wchr = 0;

	char* buff = new char[sChinese.length() / 2];
	memset(buff, 0x00, sizeof(char)*sChinese.length() / 2 + 1);

	for (int i = 0, j = 0; i < (sChinese.length() / 2); ++i)
	{
		memset(chr, 0x00, sizeof(chr));
		chr[0] = sChinese[j++];
		chr[1] = sChinese[j++];
		chr[2] = '\0';

		// 单个字符的编码 如：'我' = 0xced2
		wchr = 0;
		wchr = (chr[0] & 0xff) << 8;
		wchr |= (chr[1] & 0xff);

		buff[i] = convert(wchr);
	}

	cout << "pin yin = [" << buff << "]" << endl;

	return buff;
}

char convert(wchar_t n)
{
	if (In(0xB0A1, 0xB0C4, n)) return 'a';
	if (In(0XB0C5, 0XB2C0, n)) return 'b';
	if (In(0xB2C1, 0xB4ED, n)) return 'c';
	if (In(0xB4EE, 0xB6E9, n)) return 'd';
	if (In(0xB6EA, 0xB7A1, n)) return 'e';
	if (In(0xB7A2, 0xB8c0, n)) return 'f';
	if (In(0xB8C1, 0xB9FD, n)) return 'g';
	if (In(0xB9FE, 0xBBF6, n)) return 'h';
	if (In(0xBBF7, 0xBFA5, n)) return 'j';
	if (In(0xBFA6, 0xC0AB, n)) return 'k';
	if (In(0xC0AC, 0xC2E7, n)) return 'l';
	if (In(0xC2E8, 0xC4C2, n)) return 'm';
	if (In(0xC4C3, 0xC5B5, n)) return 'n';
	if (In(0xC5B6, 0xC5BD, n)) return 'o';
	if (In(0xC5BE, 0xC6D9, n)) return 'p';
	if (In(0xC6DA, 0xC8BA, n)) return 'q';
	if (In(0xC8BB, 0xC8F5, n)) return 'r';
	if (In(0xC8F6, 0xCBF0, n)) return 's';
	if (In(0xCBFA, 0xCDD9, n)) return 't';
	if (In(0xCDDA, 0xCEF3, n)) return 'w';
	if (In(0xCEF4, 0xD188, n)) return 'x';
	if (In(0xD1B9, 0xD4D0, n)) return 'y';
	if (In(0xD4D1, 0xD7F9, n)) return 'z';
	return '\0';
}

bool In(wchar_t start, wchar_t end, wchar_t code)
{
	if (code >= start && code <= end)
	{
		return true;
	}
	return false;
}

unsigned int crc_ta[256] = {               /* CRC余式表 */
	0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7,
	0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef,
	0x1231, 0x0210, 0x3273, 0x2252, 0x52b5, 0x4294, 0x72f7, 0x62d6,
	0x9339, 0x8318, 0xb37b, 0xa35a, 0xd3bd, 0xc39c, 0xf3ff, 0xe3de,
	0x2462, 0x3443, 0x0420, 0x1401, 0x64e6, 0x74c7, 0x44a4, 0x5485,
	0xa56a, 0xb54b, 0x8528, 0x9509, 0xe5ee, 0xf5cf, 0xc5ac, 0xd58d,
	0x3653, 0x2672, 0x1611, 0x0630, 0x76d7, 0x66f6, 0x5695, 0x46b4,
	0xb75b, 0xa77a, 0x9719, 0x8738, 0xf7df, 0xe7fe, 0xd79d, 0xc7bc,
	0x48c4, 0x58e5, 0x6886, 0x78a7, 0x0840, 0x1861, 0x2802, 0x3823,
	0xc9cc, 0xd9ed, 0xe98e, 0xf9af, 0x8948, 0x9969, 0xa90a, 0xb92b,
	0x5af5, 0x4ad4, 0x7ab7, 0x6a96, 0x1a71, 0x0a50, 0x3a33, 0x2a12,
	0xdbfd, 0xcbdc, 0xfbbf, 0xeb9e, 0x9b79, 0x8b58, 0xbb3b, 0xab1a,
	0x6ca6, 0x7c87, 0x4ce4, 0x5cc5, 0x2c22, 0x3c03, 0x0c60, 0x1c41,
	0xedae, 0xfd8f, 0xcdec, 0xddcd, 0xad2a, 0xbd0b, 0x8d68, 0x9d49,
	0x7e97, 0x6eb6, 0x5ed5, 0x4ef4, 0x3e13, 0x2e32, 0x1e51, 0x0e70,
	0xff9f, 0xefbe, 0xdfdd, 0xcffc, 0xbf1b, 0xaf3a, 0x9f59, 0x8f78,
	0x9188, 0x81a9, 0xb1ca, 0xa1eb, 0xd10c, 0xc12d, 0xf14e, 0xe16f,
	0x1080, 0x00a1, 0x30c2, 0x20e3, 0x5004, 0x4025, 0x7046, 0x6067,
	0x83b9, 0x9398, 0xa3fb, 0xb3da, 0xc33d, 0xd31c, 0xe37f, 0xf35e,
	0x02b1, 0x1290, 0x22f3, 0x32d2, 0x4235, 0x5214, 0x6277, 0x7256,
	0xb5ea, 0xa5cb, 0x95a8, 0x8589, 0xf56e, 0xe54f, 0xd52c, 0xc50d,
	0x34e2, 0x24c3, 0x14a0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
	0xa7db, 0xb7fa, 0x8799, 0x97b8, 0xe75f, 0xf77e, 0xc71d, 0xd73c,
	0x26d3, 0x36f2, 0x0691, 0x16b0, 0x6657, 0x7676, 0x4615, 0x5634,
	0xd94c, 0xc96d, 0xf90e, 0xe92f, 0x99c8, 0x89e9, 0xb98a, 0xa9ab,
	0x5844, 0x4865, 0x7806, 0x6827, 0x18c0, 0x08e1, 0x3882, 0x28a3,
	0xcb7d, 0xdb5c, 0xeb3f, 0xfb1e, 0x8bf9, 0x9bd8, 0xabbb, 0xbb9a,
	0x4a75, 0x5a54, 0x6a37, 0x7a16, 0x0af1, 0x1ad0, 0x2ab3, 0x3a92,
	0xfd2e, 0xed0f, 0xdd6c, 0xcd4d, 0xbdaa, 0xad8b, 0x9de8, 0x8dc9,
	0x7c26, 0x6c07, 0x5c64, 0x4c45, 0x3ca2, 0x2c83, 0x1ce0, 0x0cc1,
	0xef1f, 0xff3e, 0xcf5d, 0xdf7c, 0xaf9b, 0xbfba, 0x8fd9, 0x9ff8,
	0x6e17, 0x7e36, 0x4e55, 0x5e74, 0x2e93, 0x3eb2, 0x0ed1, 0x1ef0
};
unsigned short do_crc_table(unsigned char *ptr, int len)
{
	unsigned short int crc;
	unsigned char da;
	crc = 0;
	while (len-- != 0)
	{
		da = (unsigned short)crc >> 8;    /* 以8位二进制数的形式暂存CRC的高8位 */
		crc <<= 8;              /* 左移8位，相当于CRC的低8位乘以  */
		crc ^= crc_ta[da^*ptr];   /* 高8位和当前字节相加后再查表求CRC ，再加上以前的CRC */
		ptr++;
	}
	return(crc);
}
