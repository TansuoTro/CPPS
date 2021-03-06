#include "cpps.h"

namespace cpps
{
	void cpps_base_printf(object b);

	void cpps_gc_add_barrier(C*c, cpps_regvar *v)
	{
		c->getbarrierlist()->insert(v);
	}

	void cpps_gc_remove_barrier(C*c, cpps_regvar *v)
	{
			c->getbarrierlist()->erase(v);
	}

	void cpps_gc_add_gen0(C*c, cpps_cppsclassvar *p)
	{
		c->setgen0size(c->getgen0size() + p->size());
		//新增到新生代
		c->getgen0()->insert(p);
	}
	void cpps_gc_add_gen1(C*c, cpps_cppsclassvar *p)
	{
		c->setgen1size(c->getgen1size() + p->size());
		//新增到老生代
		c->getgen1()->insert(p);
	}
	void cpps_gc_check_gen_value(C*c, cpps_value &v, bool checkchild, std::unordered_set<cpps_cppsclassvar *> *oldgen, std::unordered_set<cpps_cppsclassvar *> *newgen, size_t &size, std::unordered_set<cpps_cppsclassvar *> &isCheck);

	void cpps_gc_check_child(cpps_value &v, C* c, bool checkchild, std::unordered_set<cpps_cppsclassvar *> * oldgen, std::unordered_set<cpps_cppsclassvar *> * newgen, size_t &size, std::unordered_set<cpps_cppsclassvar *> &isCheck)
	{
		for (std::unordered_map<std::string, cpps_regvar*>::iterator it = v.value.domain->varList.begin(); it != v.value.domain->varList.end(); ++it)
		{
			cpps_regvar *var = it->second;
			if (var->getval().tt == CPPS_TCLASSVAR|| var->getval().tt == CPPS_TSTRING)
			{
				cpps_gc_check_gen_value(c, var->getval(), checkchild, oldgen, newgen,size, isCheck);
			}
		}
	}
	//
	void cpps_gc_check_gen_value(C*c, cpps_value &v, bool checkchild, std::unordered_set<cpps_cppsclassvar *> *oldgen, std::unordered_set<cpps_cppsclassvar *> *newgen, size_t &size, std::unordered_set<cpps_cppsclassvar *> &isCheck)
	{
		if (v.tt == CPPS_TCLASSVAR)
		{
			if (isCheck.find((cpps_cppsclassvar*)v.value.domain) != isCheck.end()) return;//已经check过
			isCheck.insert((cpps_cppsclassvar*)v.value.domain);

			if (v.value.domain->getdomainname() == "vector")
			{
				cpps_cppsclassvar *pClsVar = (cpps_cppsclassvar *)v.value.domain;
				cpps_vector *pVector = (cpps_vector*)pClsVar->getclsptr();
				std::vector<cpps_value>& realvector = pVector->realvector();//2019-12-14 防止外部正在调用begin 导致数据错乱
				for (std::vector<cpps_value>::iterator it = realvector.begin(); it != realvector.end(); ++it)
				{
					cpps_value value = *it;
					cpps_gc_check_gen_value(c, value, checkchild, oldgen, newgen, size, isCheck);
				}
				std::unordered_set<cpps_cppsclassvar *>::iterator it = oldgen->find(pClsVar);
				if (it != oldgen->end())
				{
					oldgen->erase(it);
					newgen->insert(pClsVar);
					size += pClsVar->size();
					pClsVar->setgcLevel(1);//设置成老生代 哪怕也是老生代了 也设置一下
				}

			}
			else if (v.value.domain->getdomainname() == "map" )
			{
				cpps_cppsclassvar *pClsVar = (cpps_cppsclassvar *)v.value.domain;
				cpps_map *pMap = (cpps_map*)pClsVar->getclsptr();
				std::map<cpps_value, cpps_value>& realmap = pMap->realmap();
				for (std::map<cpps_value, cpps_value>::iterator it = realmap.begin(); it != realmap.end(); ++it)
				{
					cpps_value value0 = it->first;
					cpps_value value1 = it->second;

					cpps_gc_check_gen_value(c, value0, checkchild, oldgen, newgen, size, isCheck);
					cpps_gc_check_gen_value(c, value1, checkchild, oldgen, newgen, size, isCheck);

				}
				std::unordered_set<cpps_cppsclassvar *>::iterator it = oldgen->find(pClsVar);
				if (it != oldgen->end())
				{
					oldgen->erase(it);
					newgen->insert(pClsVar);
					size += pClsVar->size();
					pClsVar->setgcLevel(1);//设置成老生代 哪怕也是老生代了 也设置一下
				}
			}
			else if (v.value.domain->getdomainname() == "unordered_map")
			{
				cpps_cppsclassvar *pClsVar = (cpps_cppsclassvar *)v.value.domain;
				cpps_unordered_map *pMap = (cpps_unordered_map*)pClsVar->getclsptr();
				std::unordered_map<cpps_value, cpps_value, cpps_value::hash>& realmap = pMap->realmap();
				for (std::unordered_map<cpps_value, cpps_value, cpps_value::hash>::iterator it = realmap.begin(); it != realmap.end(); ++it)
				{
					cpps_value value0 = it->first;
					cpps_value value1 = it->second;

					cpps_gc_check_gen_value(c, value0, checkchild, oldgen, newgen, size, isCheck);
					cpps_gc_check_gen_value(c, value1, checkchild, oldgen, newgen, size, isCheck);

				}
				std::unordered_set<cpps_cppsclassvar *>::iterator it = oldgen->find(pClsVar);
				if (it != oldgen->end())
				{
					oldgen->erase(it);
					newgen->insert(pClsVar);
					size += pClsVar->size();
					pClsVar->setgcLevel(1);//设置成老生代 哪怕也是老生代了 也设置一下
				}
			}
			else if (v.tt == CPPS_TCLASSVAR)
			{
				cpps_cppsclassvar *pClsVar = (cpps_cppsclassvar *)v.value.domain;
				std::unordered_set<cpps_cppsclassvar *>::iterator it = oldgen->find(pClsVar);
				if (it != oldgen->end())
				{
					oldgen->erase(it);
					newgen->insert(pClsVar);
					size += pClsVar->size();
					pClsVar->setgcLevel(1);//设置成老生代 哪怕也是老生代了 也设置一下
					
				}
				if (checkchild )
				{
					cpps_gc_check_child(v, c, checkchild, oldgen, newgen, size, isCheck);
				}
			}
		}
		else if(v.tt == CPPS_TSTRING)
		{
			cpps_cppsclassvar *pClsVar = static_cast<cpps_cppsclassvar *>(v.value.domain);
			std::unordered_set<cpps_cppsclassvar *>::iterator it = oldgen->find(pClsVar);
			if (it != oldgen->end())
			{
				oldgen->erase(it);
				newgen->insert(pClsVar);
				size += pClsVar->size();
				pClsVar->setgcLevel(1);//设置成老生代 哪怕也是老生代了 也设置一下
			}
		}
	}
	//检测新生代
	void cpps_gc_check_gen0(C *c)
	{

		std::unordered_set<cpps_cppsclassvar *> isCheck;
	
		cpps_value value = c->_G;
		size_t tmp = c->getgen1size();
		cpps_gc_check_child(value, c, true, c->getgen0(), c->getgen1(), tmp, isCheck);
		c->setgen1size(tmp);


		std::unordered_set<cpps_cppsclassvar *> tempoldgen;
		size_t tempoldgensize = 0;

		for (std::unordered_set<cpps_regvar*>::iterator it = c->getbarrierlist()->begin();
			it != c->getbarrierlist()->end(); ++it)
		{
			cpps_regvar *v = *it;
			cpps_gc_check_gen_value(c, v->getval(), true, c->getgen0(), &tempoldgen, tempoldgensize, isCheck);
		}



		//释放gen0里面的内存
		for (std::unordered_set<cpps_cppsclassvar *>::iterator it = c->getgen0()->begin();
			it != c->getgen0()->end(); ++it)
		{
			cpps_cppsclassvar * pClsVar = *it;
			pClsVar->destory(c);
			delete pClsVar;
		}
		c->getgen0()->clear();
		*(c->getgen0()) = tempoldgen;
		c->setgen0size(tempoldgensize);

	}

	//检测老生代  这样检测估计后面就卡死了。  还得想办法优化！！！
	void cpps_gc_check_gen1(C *c)
	{

		std::unordered_set<cpps_cppsclassvar *> newgen;
		size_t newgensize = 0;
		std::unordered_set<cpps_cppsclassvar *> isCheck1;
		std::unordered_set<cpps_cppsclassvar *> isCheck;
		cpps_value value = c->_G;
		cpps_gc_check_child(value, c, true, c->getgen0(), &newgen, newgensize, isCheck);
		cpps_gc_check_child(value, c, true, c->getgen1(), &newgen, newgensize, isCheck1);



		std::unordered_set<cpps_cppsclassvar *> tempoldgen;
		size_t tempoldgensize = 0;

		//先把新生代的检测了
		for (std::unordered_set<cpps_regvar*>::iterator it = c->getbarrierlist()->begin();
			it != c->getbarrierlist()->end(); ++it)
		{
			cpps_regvar *v = *it;
			cpps_gc_check_gen_value(c, v->getval(), true, c->getgen0(), &tempoldgen, tempoldgensize, isCheck);
			cpps_gc_check_gen_value(c, v->getval(), true, c->getgen1(), &tempoldgen, tempoldgensize, isCheck1);
		}




		//释放gen0里面的内存
		for (std::unordered_set<cpps_cppsclassvar *>::iterator it = c->getgen0()->begin();
			it != c->getgen0()->end(); ++it)
		{
			cpps_cppsclassvar * pClsVar = *it;
			pClsVar->destory(c);
			delete pClsVar;
		}
		c->getgen0()->clear();
		*(c->getgen0()) = tempoldgen;
		c->setgen0size(tempoldgensize);


		//释放gen1里面的内存
		for (std::unordered_set<cpps_cppsclassvar *>::iterator it = c->getgen1()->begin();
			it != c->getgen1()->end(); ++it)
		{
			cpps_cppsclassvar * pClsVar = *it;
			pClsVar->destory(c);
			delete pClsVar;
		}
		c->getgen1()->clear();
		*(c->getgen1()) = newgen;
		c->setgen1size(newgensize);
		c->setlastgensize(c->getgen1size());



	}
	void		gc_cleanup(C *c )
	{
		//清理当前线程的
		for (std::unordered_set<cpps_cppsclassvar *>::iterator it = c->getgen0()->begin();
			it != c->getgen0()->end(); ++it)
		{
			cpps_cppsclassvar * pClsVar = *it;
			pClsVar->destory(c);
			delete pClsVar;
		}
		c->getgen0()->clear();
		c->setgen0size(0);

		//释放gen1里面的内存
		for (std::unordered_set<cpps_cppsclassvar *>::iterator it = c->getgen1()->begin();
			it != c->getgen1()->end(); ++it)
		{
			cpps_cppsclassvar * pClsVar = *it;
			pClsVar->destory(c);
			delete pClsVar;
		}

		c->getgen1()->clear();
		c->setgen1size(0);
		c->setlastgensize(0);
		c->getbarrierlist()->clear();



	}
	std::string gcinfo(C *c)
	{
		//c->gclock.lock();
		std::string ret = "";
#ifdef WIN32

		char buffer[1024];
		sprintf(buffer,"gen0 memory %I64d b\n", c->getgen0size());
		ret += buffer;
		sprintf(buffer, "gen1 memory %I64d b\n", c->getgen1size());	//测试 200字节进行清理年轻代
		ret += buffer;
		sprintf(buffer, "current memory %I64d b\n", c->getgen0size() + c->getgen1size());
		ret += buffer;
		sprintf(buffer, "c->barrierList.size(): %I64d \n", c->getbarrierlist()->size());
		ret += buffer;
		sprintf(buffer, "c->gen1.size(): %I64d \n", c->getgen1()->size());
		ret += buffer;
		sprintf(buffer, "c->gen0.size(): %I64d \n", c->getgen0()->size());
		ret += buffer;

		for (std::unordered_set<cpps_cppsclassvar *>::iterator it = c->getgen1()->begin(); it != c->getgen1()->end(); it++)
		{
			auto v = *it;
			if (v->domainname == "String")
			{
				std::string *tmpStr = (std::string *)v->getclsptr();
				printf("%s\r\n", tmpStr->c_str());
			}
		}
#endif
		return ret;
	}
	void cpps_reggc(C *c)
	{
		module(c,"GC")[
			def_inside("Collect", cpps_gc_check_gen0),
			def_inside("CollectAll", cpps_gc_check_gen1),
			def_inside("gcinfo", gcinfo)
		];
	}

}
