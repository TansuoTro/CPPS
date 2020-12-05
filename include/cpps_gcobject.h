#ifndef CPPS_GCOBJECT_CPPS_HEAD_
#define CPPS_GCOBJECT_CPPS_HEAD_

//===================================
//@Author		:	Johnson
//@QQ			:	88481106
//@Email		:	88481106@qq.com
//@Date			:	2015/11/24 (yy/mm/dd)
//@Module		:	CPPS_GCOBJECT
//@Description	:	垃圾回收
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
		virtual ~cpps_gcobject()
		{
			
		}
		virtual void							setgcLevel(char l)
		{
			gclevel = l;
		}
		virtual char							getgcLevel()
		{
			return gclevel;
		}
		char gclevel;//0 新手，1 元老 2.永恒（不知道有没有用）
	};
}
#endif // CPPS_GCOBJECT_CPPS_HEAD_