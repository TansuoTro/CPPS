#ifndef CPPS_MODULE_CPPS_HEAD_
#define CPPS_MODULE_CPPS_HEAD_

//===================================
//@Author		:	Johnson
//@QQ			:	88481106
//@Email		:	jiang_4177@163.com
//@Date			:	2015/11/20 (yy/mm/dd)
//@Module		:	CPPS_MODULE
//@Description	:	Cppע�ᵽCpps�ӿ�
//@website		:	http://cpps.wiki
//==================================


namespace cpps
{
	struct cpps_reg_class
	{
		cpps_reg* f;
	};

	struct RegxModule
	{

		RegxModule(cpps_reg_class c)
			:f(c.f)
		{
			f->isneedC = false;
		}
		RegxModule( cpps_regfunction* f,bool b )
			:f(f)
		{
			f->isneedC = b;
		}

		RegxModule(cpps_reggvar* f, bool b)
			:f(f)
		{
			f->isneedC = b;
		}
		RegxModule 	operator ,(RegxModule c)
		{
			if (!f->next)
			{
				f->next = c.f;
			}
			else
			{
				cpps_reg* next = f->next;
				while (next->next)
					next = next->next;
			
				next->next = c.f;
			}
			return *this;
		}
		cpps_reg* f;
	};

	template< class C>
	struct _class : public cpps_reg_class
	{
		_class(std::string name)
		{
			_cls = new cpps_class<C>(name,NULL, cpps_domain_type_class);
			f = new cpps_regclass_template<C>(name, _cls);
			cpps_class_singleton<C*>::getSingletonPtr()->setsls(_cls);
		}
		template<class F>
		_class<C>& 	def(std::string func, F _f)
		{
			cpps_reg* r = make_regfunction(func, _f);
			r->isneedC = false;
			_cls->regFunc( r );
			return *this;
		}

		template<class F>
		_class<C>&  defvar(C *c, std::string name, F v)
		{
			cpps_reg* r = make_regvar(name, cpps_cpp_to_cpps_converter<F>::apply(c, v));
			r->isneedC = false;
			_cls->regFunc(r);
			return *this;
		}

		template<class F>
		_class<C>& 	def_inside(std::string func, F _f)
		{
			cpps_reg* r = make_regfunction(func, _f);
			r->isneedC = true;
			_cls->regFunc(r);
			return *this;
		}

		RegxModule 	operator ,(RegxModule c)
		{
			RegxModule(*this).operator,(c);
			return *this;
		}
		cpps_class<C> *_cls;
	};

	template<class F>
	RegxModule def(std::string func, F f)
	{
		return RegxModule(make_regfunction(func, f),false);
	}


	template<class F>
	RegxModule defvar(C *c,std::string name, F v)
	{
		return RegxModule(make_regvar(name, cpps_cpp_to_cpps_converter<F>::apply(c,v)), false);
	}




	template<class F>
	RegxModule def_inside(std::string func, F f)
	{
		return RegxModule(make_regfunction(func, f), true);
	}
	


	struct cpps_module
	{
		cpps_module(C* c,std::string _domain) //Ĭ��ע���_G
		{
			cState = c;
			domain = cState->_G;//Ĭ���Ǹ��ڵ�
			if (!_domain.empty())//������������� �Ǿ����Լ���һ��������
			{
				cpps_domain* leftdomain = NULL;

				cpps_regvar * v = domain->getVar(_domain,leftdomain);
				if (!v)
				{
					cpps_domain *temp_domain = new cpps_domain(NULL, cpps_domain_type_root,"root");//�������ڵ���


					v = new cpps_regvar();//_G Ϊ���ڵ�
					v->setVarName(_domain);
					v->setValue(cpps_value(temp_domain)); //���б��copy��ȥ
					domain->regVar(v); //���Լ�ע���_G..
				}
				domain = v->getValue().value.domain;
			}
		}

		void	operator [](RegxModule m)
		{
			domain->regFunc(m.f);
		}

	public:
		C					*cState;
		cpps_domain			*domain;	//���ڵ�
	};


	static cpps_module module(C *c, std::string _domain = "")
	{
		return cpps_module(c, _domain);
	}

}

#endif // CPPS_MODULE_CPPS_HEAD_