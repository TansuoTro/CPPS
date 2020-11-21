#ifndef CPPS_NEWPTR_HEAD_
#define CPPS_NEWPTR_HEAD_

//===================================
//@Author		:	Johnson
//@QQ			:	88481106
//@Email		:	jiang_4177@163.com
//@Date			:	2015/11/18 (yy/mm/dd)
//@Module		:	LIBCPPS
//@Description	:	Cpps����ӿ�
//@website		:	http://cpps.wiki
//==================================


namespace cpps
{
	template <class T>
	struct cpps_class_singleton;
	void cpps_gc_add_gen0(C*c, cpps_cppsclassvar *p);
	//�������ӵ�GC��PTR
	template<class T>
	cpps_cppsclassvar*		newClassPtr(C *c, T ** ret)
	{
		cpps_cppsclassvar *var = cpps_class_singleton<T*>::getSingletonPtr()->getcls()->create(c,true);
		//cpps_regvar* v = new cpps_regvar;
		//v->setValue(var);

		//cpps_gc_add_barrier(c, v);
		//���´�����������ӵ��������Ժ���Ҫ��Ҫ�ɵ�
		cpps_gc_add_gen0(c, var);

		*ret = (T *)var->getclsptr();

		return var;
	}
}

#define cpps_create_class_var(t,c,v,p) t *p = NULL; cpps_value v = newClassPtr<t>(c, &p);

#endif // CPPS_NEWPTR_HEAD_