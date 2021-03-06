#ifndef CPPS_MODULE_CPPS_HEAD_
#define CPPS_MODULE_CPPS_HEAD_

//===================================
//@Author		:	Johnson
//@QQ			:	88481106
//@Email		:	88481106@qq.com
//@Date			:	2015/11/20 (yy/mm/dd)
//@Module		:	CPPS_MODULE
//@Description	:	Cpp注册到Cpps接口
//@website		:	http://cpps.wiki
//==================================


namespace cpps
{
	template<class R>
	cpps_regfunction* make_regfunction(std::string func, R(*f)(const char* fmt, ...), bool isasync = false);
	struct cpps_reg_class
	{
		cpps_reg* f;
	};

	struct regxmodule
	{

		regxmodule(cpps_reg_class c)
			:f(c.f)
		{
			f->isneedC = false;
		}
		regxmodule( cpps_regfunction* f,bool b )
			:f(f)
		{
			f->isneedC = b;
		}

		regxmodule(cpps_reggvar* f, bool b)
			:f(f)
		{
			f->isneedC = b;
		}
		regxmodule 	operator ,(regxmodule c)
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
			cpps_class_singleton<C*>::instance()->setsls(_cls);
		}
		template<class F>
		_class<C>& 	def(std::string func, F _f, bool isasync = false)
		{
			cpps_reg* r = make_regfunction(func, _f,isasync);
			r->isneedC = false;
			_cls->regfunc( r );
			return *this;
		}

		template<class F>
		_class<C>&  defvar(C *c, std::string name, F v)
		{
			cpps_reg* r = make_regvar(name, cpps_cpp_to_cpps_converter<F>::apply(c, v));
			r->isneedC = false;
			_cls->regfunc(r);
			return *this;
		}

		template<class F>
		_class<C>& 	def_inside(std::string func, F _f, bool isasync = false)
		{
			cpps_reg* r = make_regfunction(func, _f,isasync);
			r->isneedC = true;
			_cls->regfunc(r);
			return *this;
		}

		regxmodule 	operator ,(regxmodule c)
		{
			regxmodule(*this).operator,(c);
			return *this;
		}
		cpps_class<C> *_cls;
	};

	template<class F>
	regxmodule def(std::string func, F f, bool isasync = false)
	{
		return regxmodule(make_regfunction(func, f, isasync),false);
	}


	template<class F>
	regxmodule defvar(C *c,std::string name, F v)
	{
		return regxmodule(make_regvar(name, cpps_cpp_to_cpps_converter<F>::apply(c,v)), false);
	}




	template<class F>
	regxmodule def_inside(std::string func, F f, bool isasync = false)
	{
		return regxmodule(make_regfunction(func, f,isasync), true);
	}
	


	struct cpps_module
	{
		cpps_module(C* c,std::string _domain) //默认注册给_G
		{
			cState = c;
			domain = cState->_G;//默认是根节点
			if (!_domain.empty())//如果定义名字了 那就是自己的一个。。。
			{
				cpps_domain* leftdomain = NULL;

				cpps_regvar * v = domain->getvar(_domain,leftdomain);
				if (!v)
				{
					cpps_domain *temp_domain = new cpps_domain(NULL, cpps_domain_type_root,"root");//创建根节点域


					v = new cpps_regvar();//_G 为根节点
					v->setvarname(_domain);
					v->setval(cpps_value(temp_domain)); //域列表会copy进去
					domain->regvar(NULL,v); //将自己注册成_G..
				}
				domain = v->getval().value.domain;
			}
		}

		void	operator [](regxmodule m)
		{
			domain->regfunc(m.f);
		}

	public:
		C					*cState;
		cpps_domain			*domain;	//根节点
	};


	static cpps_module module(C *c, std::string _domain = "")
	{
		return cpps_module(c, _domain);
	}

}

#endif // CPPS_MODULE_CPPS_HEAD_