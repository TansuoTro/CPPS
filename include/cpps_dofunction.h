#ifndef CPPS_DOFUNCTION_CPPS_HEAD_
#define CPPS_DOFUNCTION_CPPS_HEAD_

//===================================
//@Author		:	Johnson
//@QQ			:	88481106
//@Email		:	88481106@qq.com
//@Date			:	2015/12/16 (yy/mm/dd)
//@Module		:	CPPS_DOFUNCTION
//@Description	:	C++调用Cpps函数处理
//@website		:	http://cpps.wiki
//==================================


namespace cpps
{
	void					cpps_gc_check_step(C * c);
	object					dofunction(C *c, object func);
	object					doclassfunction(C *c, cpps_domain* leftdomain, object func);
}

#define CPPS_DOFUNCTION_ITER_C 1
#include "cpps_dofunction.h"
#undef CPPS_DOFUNCTION_ITER_C

#define CPPS_DOFUNCTION_ITER_C 2
#include "cpps_dofunction.h"
#undef CPPS_DOFUNCTION_ITER_C

#define CPPS_DOFUNCTION_ITER_C 3
#include "cpps_dofunction.h"
#undef CPPS_DOFUNCTION_ITER_C

#define CPPS_DOFUNCTION_ITER_C 4
#include "cpps_dofunction.h"
#undef CPPS_DOFUNCTION_ITER_C

#define CPPS_DOFUNCTION_ITER_C 5
#include "cpps_dofunction.h"
#undef CPPS_DOFUNCTION_ITER_C


#define CPPS_DOFUNCTION_ITER_C 6
#include "cpps_dofunction.h"
#undef CPPS_DOFUNCTION_ITER_C


#define CPPS_DOFUNCTION_ITER_C 7
#include "cpps_dofunction.h"
#undef CPPS_DOFUNCTION_ITER_C


#define CPPS_DOFUNCTION_ITER_C 8
#include "cpps_dofunction.h"
#undef CPPS_DOFUNCTION_ITER_C


#define CPPS_DOFUNCTION_ITER_C 9
#include "cpps_dofunction.h"
#undef CPPS_DOFUNCTION_ITER_C


#define CPPS_DOFUNCTION_ITER_C 10
#include "cpps_dofunction.h"
#undef CPPS_DOFUNCTION_ITER_C


#define CPPS_DOFUNCTION_ITER_C 11
#include "cpps_dofunction.h"
#undef CPPS_DOFUNCTION_ITER_C


#endif // CPPS_DOFUNCTION_CPPS_HEAD_


#ifdef  CPPS_DOFUNCTION_ITER_C

namespace cpps
{
	template<class R>
	struct cpps_converter;
	template< CPPS_PP_ENUM_PARAMS(CPPS_DOFUNCTION_ITER_C, class A) >
	object					dofunction(C *c, object func, CPPS_PP_ENUM_VARS_PARAMS(CPPS_DOFUNCTION_ITER_C, A, p))
	{
		cpps_value ret;
		if (func.value.tt == CPPS_TLAMBDAFUNCTION) {
			cpps_cppsclassvar* cppsclassvar = (cpps_cppsclassvar*)func.value.value.domain;
			cpps_lambda_function* pfunc = (cpps_lambda_function*)cppsclassvar->getclsptr();
			func.value = pfunc;
			func.value.tt = CPPS_TFUNCTION;
		}
		if (func.value.tt == CPPS_TFUNCTION)
		{
			cpps_function *f = func.value.value.func;
			if (f)
			{
				std::vector<cpps_value> paramlist;
				CPPS_PP_ENUM_VARS_PARAMS_PUSHBACK(CPPS_DOFUNCTION_ITER_C, paramlist, A, p, c);

				cpps_domain *execdomain2 =  c->_G;
				cpps_domain* execdomain = c->domain_alloc();
				execdomain->init(execdomain2, cpps_domain_type_func);
				execdomain->setexecdomain(execdomain2);

				for (size_t i = 0; i < paramlist.size(); i++)
				{
					cpps_value &value = paramlist[i];

					cpps_regvar *v = new cpps_regvar;
					v->setval(value);
					std::stringstream strStream;
					strStream << "p" << i;
					v->setvarname(strStream.str());
					execdomain->regvar(c, v);

				}

				/*cpps_domain *execdomain = c->_G;
				if (func.value.parentLambdaVar)
					execdomain = func.value.parentLambdaVar;
					*/

				cpps_stack* stack = c->stack_alloc();
				stack->init("", 0, f->funcname.c_str());
				c->push_stack(stack);

				f->callfunction(c, &ret, execdomain2, &paramlist, NULL,NULL);


				c->pop_stack();
				c->stack_free( stack );

				execdomain->destory(c);
				c->domain_free(execdomain);

				//检测gc
				//if (!c->getcallstack() || c->getcallstack()->size() == 0)
				/*{
					cpps_gc_check_step(c);
				}*/
			}
		}
		return ret;
	}
	template< CPPS_PP_ENUM_PARAMS(CPPS_DOFUNCTION_ITER_C, class A) >
	object					doclassfunction(C *c, cpps_domain* leftdomain, object func, CPPS_PP_ENUM_VARS_PARAMS(CPPS_DOFUNCTION_ITER_C, A, p))
	{
		cpps_value ret;

		if (func.value.tt == CPPS_TLAMBDAFUNCTION) {
			cpps_cppsclassvar* cppsclassvar = (cpps_cppsclassvar*)func.value.value.domain;
			cpps_lambda_function* pfunc = (cpps_lambda_function*)cppsclassvar->getclsptr();
			func.value = pfunc;
			func.value.tt = CPPS_TFUNCTION;
		}
		if (func.value.tt == CPPS_TFUNCTION)
		{
			cpps_function *f = func.value.value.func;
			if (f)
			{
				std::vector<cpps_value> paramlist;
				CPPS_PP_ENUM_VARS_PARAMS_PUSHBACK(CPPS_DOFUNCTION_ITER_C, paramlist, A, p, c);

				cpps_domain *execdomain2 = leftdomain;
				cpps_domain* execdomain = c->domain_alloc();
				execdomain->init(execdomain2, cpps_domain_type_func);
				execdomain->setexecdomain(execdomain2);

				for (size_t i = 0; i < paramlist.size(); i++)
				{
					cpps_value &value = paramlist[i];

					cpps_regvar *v = new cpps_regvar;
					v->setval(value);
					std::stringstream strStream;
					strStream << "p" << i;
					v->setvarname(strStream.str());
					execdomain->regvar(c, v);

				}

				/*cpps_domain *execdomain = c->_G;
				if (func.value.parentLambdaVar)
					execdomain = func.value.parentLambdaVar;
					*/

				cpps_stack* stack = c->stack_alloc();
				stack->init("", 0, f->funcname.c_str());
				c->push_stack(stack);

				f->callfunction(c, &ret, execdomain2, &paramlist, NULL, NULL);


				c->pop_stack();
				c->stack_free(stack);

				execdomain->destory(c);
				c->domain_free(execdomain);

				//检测gc
				//if (!c->getcallstack() || c->getcallstack()->size() == 0)
				/*{
					cpps_gc_check_step(c);
				}*/
			}
		}
		return ret;
	}
}

#endif