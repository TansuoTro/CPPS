#ifndef CPPS_DEF_CPPS_HEAD_
#define CPPS_DEF_CPPS_HEAD_

//===================================
//@Author		:	Johnson
//@Email		:	jiang_4177@163.com
//@Date			:	2015/11/24 (yy/mm/dd)
//@Module		:	CPPS_DEF
//@Description	:	�궨��
//@website		:	http://cpps.wiki
//==================================

#define CPPS_VER		"1.0 Beta"
#define CPPS_NAME		"CPPS"

#define CPPS_GEN1_CHECKSIZE			1024 * 5  // 512 M
#define CPPS_GEN0_CHECKSIZE			CPPS_GEN1_CHECKSIZE / 8 * 3
#define CPPS_GEN0_CHECKCOUNT		10
#define CPPS_BARRIER_CHECKCOUNT		10

#define CPPS_TNIL		0
#define CPPS_TINTEGER	1	
#define CPPS_TNUMBER	2
#define CPPS_TBOOLEAN	3
#define CPPS_TSTRING	4
#define	CPPS_TUSERDATA	5
#define CPPS_TFUNCTION	6
#define CPPS_TDOMAIN	7	//��ʱ�ڲ��ã���
#define CPPS_TREGVAR	8	//�������ã�ָ��)����
#define CPPS_TCLASS		9	//������
#define CPPS_TCLASSVAR  10  //��Ķ���

#define CPPS_SINGLERET		0
#define CPPS_MUNITRET		1



#define CPPS_ONIL				0 //�� Լ����NULL
#define CPPS_ODOFUNCTION		1 //ִ�к���
#define CPPS_ONUMPARAM			2 //���ֲ���
#define CPPS_OSTRPARAM			3 //�ַ�������
#define CPPS_OSTR				4 //�ַ���
#define CPPS_ROOT				5 //���ڵ�
#define CPPS_ORETLIST			6 //����ֵ�б�
#define CPPS_OPARAMLIST			7 //�����б�
#define CPPS_ODEFVAR			8 //�������
#define CPPS_VARNAME			9 //��������
#define CPPS_ODEFVAR_VAR		10	//����ȷʵΪ��������
#define CPPS_ODEFVAR_FUNCTION	11	//����Ϊ����
#define CPPS_OVARPARAM			12 //��������
#define CPPS_FUNCNAME			13 //��������
#define CPPS_ONUMBER			14 //����(��������
#define CPPS_OINTEGER			15 //���֣�������
#define CPPS_ODEFVAR_FUNC		16 //���庯��
#define CPPS_ODEFVAR_NIL		17 // NIL
#define CPPS_OBOOLPARAM			18 //�ַ�������
#define CPPS_OBOOL				19 //�ַ�������
#define CPPS_OASSEMBLE			20 //ִ�м�
#define CPPS_OIF				21	//ִ��if else
#define CPPS_ORETURN			22	//ִ��if else
#define CPPS_OBRACKET			23	//����
#define CPPS_OFOR				24	//forѭ��
#define CPPS_QUOTEVARNAME		25 //���ñ�������
#define CPPS_OEXPRESSION		26 //���ʽ
#define CPPS_OGETOBJECT			27	//��ȡ�Ӷ���
#define CPPS_CHILDVARNAME		28	//�Ӷ�������
#define	CPPS_OWHILE				29	//whileѭ��
#define	CPPS_OCLASS				30	//class��
#define CPPS_ONEWVAR			31	//��������
#define CPPS_QUOTEGETOBJECT		32  //���ñ�������
#define	CPPS_ODOFILE			33	//dofile
#define	CPPS_ODOSTRING			34	//dostring
#define	CPPS_OBREAK				35	//break
#define	CPPS_OCONTINUE			36	//continue
#define CPPS_OGETCHIILD			37	//ִ�� [ ] ����
#define CPPS_QUOTEGETCHIILD		38  //���ñ�������
#define	CPPS_OINCLUDE			39	//include
#define CPPS_VARNAME_LAMBDA		40	//lambda������
#define CPPS_OARRAY				41	//����

#define CPPS_NOERROR			0	//��������û�д���


#define CPPS_NOT_DEFASSEMBLE	1 //�����Զ��弯
#define CPPS_NOT_DEFFUNCTION	2 //�����Զ��庯��
#define CPPS_NOT_USEBUILTIN		4	//������ʹ�ùؼ���
#define CPPS_NOT_DEFVAR			8 //�����Զ������
#define CPPS_NOT_DONTDELETEEND	16 //����Ҫ�Ƴ�;
#define CPPS_NOT_DEFCLASS		32 //��Ҫ������

enum
{
	cpps_domain_type_root = 1, //��
	cpps_domain_type_ass,		//��
	cpps_domain_type_func,     //����
	cpps_domain_type_if,		//if
	cpps_domain_type_for,		//for
	cpps_domain_type_while,		//while
	cpps_domain_type_switch,	//switch
	cpps_domain_type_exec,		//ִ������ʱ��
	cpps_domain_type_class,		//�����
	cpps_domain_type_classvar,		//�����
	//cpps_domain_type_

};

#ifndef _WIN32
typedef long long __int64;
#endif

#define cpps_time_leap(year) (((year%4==0)&&(year%100!=0))||((year%4==0)&&(year%400==0))) 


#define cpps_try try {

#define _CPPS_TRY try {

#define cpps_catch } catch (cpps_error e)\
{\
	printf("����: %d : %s file:%s line:%d \n", e.erron, e.s.c_str(), e.file.c_str(), e.line); \
	\
}\
	catch (const char* s)\
{\
	printf("����: %s \n", s); \
}
#define _CPPS_CATCH } catch (cpps_error e)\
{\
	printf("����: %d : %s file:%s line:%d \n�����ջ��Ϣ��\n", e.erron, e.s.c_str(), e.file.c_str(), e.line); \
	std::vector<cpps_stack*> &stacklist = c->getcallstack(); \
for (std::vector<cpps_stack*>::reverse_iterator it = stacklist.rbegin(); it != stacklist.rend(); ++it)\
{\
	cpps::cpps_stack *stack = *it; \
	std::cout << " " << stack->f.c_str() << "	��" << stack->l << "��	������" << stack->func.c_str() << std::endl; \
}\
	\
}\
	catch (const char* s)\
{\
	printf("����: %s \n�����ջ��Ϣ��\n", s); \
	std::vector<cpps_stack*> &stacklist = c->getcallstack(); \
for (std::vector<cpps_stack*>::reverse_iterator it = stacklist.rbegin(); it != stacklist.rend(); ++it)\
{\
	cpps::cpps_stack *stack = *it; \
	std::cout << " " << stack->f.c_str() << "	��" << stack->l << "��	������" << stack->func.c_str() << std::endl; \
}\
	\
}


typedef double cpps_number;
typedef __int64 cpps_integer;
typedef unsigned char byte;

//long ,unsigned long,float ,double

namespace cpps
{
	typedef char				int8;
	typedef unsigned char		usint8;
	typedef short				int16;
	typedef unsigned short		usint16;
	typedef	int					int32;
	typedef	unsigned int		usint32;
	typedef long				long32;
	typedef unsigned long		uslong32;
	typedef	long long			int64;
	typedef	unsigned long long	usint64;
}

//һЩlinux����Ҫ��ͷ�ļ�
#ifndef _WIN32
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/mman.h>

#ifndef FALSE  
	#define FALSE   0
#endif
#ifndef TRUE  
	#define TRUE    1
#endif
#ifndef NULL  
	#define NULL    0
#endif
#else

#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN	
#include <windows.h>
#include <time.h>

#endif


#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <assert.h>
#include <sstream>
#include <unordered_set>
#include <unordered_map>
#include <direct.h>

//////////////////////////////////////////////////////////////////////////


//�ýű���vs����ÿ�
typedef  void var;
void println(std::string asd);
void printfln(std::string asd);
void sleep(int time);
typedef void math;
void random(int min, int max);
void gettime();
void gettickcount();

#endif // CPPS_DEF_CPPS_HEAD_