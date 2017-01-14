#ifndef CPPS_ERROR_CPPS_HEAD_
#define CPPS_ERROR_CPPS_HEAD_

//===================================
//@Author		:	Johnson
//@Email		:	jiang_4177@163.com
//@Date			:	2015/11/23 (yy/mm/dd)
//@Module		:	CPPS_ERROR
//@Description	:	Cpps����
//@website		:	http://cpps.wiki
//==================================
#include <stdarg.h>

enum
{
	cpps_error_noknow	=	0,
	cpps_error_unknow	=	1,
	cpps_error_varnotnumber = 2,//�������������ֿ�ͷ
	cpps_error_varerror = 3, //���������в��ܰ��������ַ���
	cpps_error_paramerror = 4, //���������в��ܰ��������ַ���
	cpps_error_deffuncrror = 5, //���庯������
	cpps_error_assembleerror = 6, //���弯����
	cpps_error_iferror = 7, //if �������
	cpps_error_normalerror = 8, //�������
	cpps_error_classerror = 9, //�������
	cpps_error_forerror = 10,
	cpps_error_whileerror = 11,
	cpps_error_arrayeerror = 12,
};


struct cpps_error
{
	cpps_error(std::string f,int l,int n, const char *format, ...)
	{
		char szString[4096];
		va_list ap;
		va_start(ap, format);
#ifdef _WIN32
		int size = vsprintf_s(szString,4096, format, ap);
#else
		int size = vsprintf(szString, format, ap);
#endif
		va_end(ap);

		erron = n;
		file = f;
		line = l;
		s = szString;
	}
	int erron;
	std::string file;
	int line;
	std::string s;
};
#endif // CPPS_ERROR_CPPS_HEAD_