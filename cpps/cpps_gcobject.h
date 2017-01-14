#ifndef CPPS_GCOBJECT_CPPS_HEAD_
#define CPPS_GCOBJECT_CPPS_HEAD_

//===================================
//@Author		:	Johnson
//@Email		:	jiang_4177@163.com
//@Date			:	2015/11/24 (yy/mm/dd)
//@Module		:	CPPS_GCOBJECT
//@Description	:	��������
//@website		:	http://cpps.wiki
//==================================

namespace cpps
{
	struct cpps_gcobject
	{
		cpps_gcobject()
		{
			gclevel = 0;
		}
		virtual void							setGCLevel(char l)
		{
			gclevel = l;
		}
		virtual char							getGCLevel()
		{
			return gclevel;
		}
		char gclevel;//0 ���֣�1 Ԫ�� 2.���㣨��֪����û���ã�
	};
}
#endif // CPPS_GCOBJECT_CPPS_HEAD_