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
	void cpps_call_parent_class_default_constructor(C* c, Node* n, cpps_cppsclass* parent_cppsclass, cpps_domain* domain, cpps_domain* leftdomain);
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
	inline cpps_cppsclassvar* newcppsclasvar(C* c, cpps::cpps_cppsclass* cppsclass)
	{
		cpps_cppsclassvar* cppsclassvar = cppsclass->create(c);
		//�����������ı�����������
		if (cppsclass->o)
			cpps_step_all(c, CPPS_SINGLERET, cppsclassvar, cppsclass->o->getright());

		//���´�����������ӵ��������Ժ���Ҫ��Ҫ�ɵ�
		cpps_gc_add_gen0(c, cppsclassvar);

		cpps_regvar* v = new cpps_regvar();
		v->setVarName("this");
		v->setValue(cpps_value(cppsclassvar)); //���б��copy��ȥ
		v->setIsConst(true);
		cppsclassvar->regVar(NULL, v);

		//ִ��0�������캯��
		cpps_domain* leftdomain = NULL;
		cpps_regvar* var = cppsclassvar->getVar("constructor", leftdomain);
		if (var && var->getValue().tt == CPPS_TFUNCTION)
		{
			Node n("",0);
			leftdomain = cppsclassvar;
			for (size_t i = 0; i < cppsclass->parentClassList().size(); ++i)
			{
				cpps_cppsclass* parent_cppsclass = cppsclass->parentClassList()[i];
				cpps_call_parent_class_default_constructor(c, &n, parent_cppsclass, c->_G, leftdomain);
			}

			cpps_function* f = var->getValue().value.func;
			if (f->getparamcount() == 0)
			{
				doclassfunction(c, cppsclassvar, var->getValue());
			}
		}

		

		return cppsclassvar;
	}
}

#define cpps_create_class_var(t,c,v,p) t *p = NULL; cpps_value v = newClassPtr<t>(c, &p);

#endif // CPPS_NEWPTR_HEAD_