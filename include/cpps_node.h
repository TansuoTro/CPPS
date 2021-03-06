
#ifndef CPPS_OBJ_CPPS_HEAD_
#define CPPS_OBJ_CPPS_HEAD_

//===================================
//@Author		:	Johnson
//@QQ			:	88481106
//@Email		:	88481106@qq.com
//@Date			:	2015/11/20 (yy/mm/dd)
//@Module		:	CPPS_NODE
//@Description	:	Cpps节点
//@website		:	http://cpps.wiki
//==================================


namespace cpps
{
	struct C;
	struct cpps_node_domain;
	enum node_var_type
	{
		node_var_type_var,
		node_var_type_constvar,
		node_var_type_asyncvar,
	};
	struct node
	{
		node() {
			type = 0;
			parent = NULL;
			symbol = NULL;
			domain = NULL;
			line = 0;
			varsize = -1;
			offset = -1;
			offsettype = -1;
			size = -1;
			varlist = NULL;
			value.integer = 0;
			closure = false;
		}
		node(std::string f)
		{
			type = 0;
			filename = f;
			parent = NULL; 
			symbol = NULL;
			domain = NULL;
			line = 1;
			varsize = -1;
			offset = -1;
			offsettype = -1;
			size = -1;
			varlist = NULL;
			value.integer = 0;
			closure = false;
		}
		node(node *n,std::string f,int32 ln)
		{
			type = 0;
			parent = n;
			symbol = NULL;
			filename = f;
			n->add(this);
			domain = NULL;
			line = ln;
			varsize = -1;
			offset = -1;
			offsettype = -1;
			size = -1;
			varlist = NULL;
			value.integer = 0;
			closure = false;
		}
		node(std::string f, int32 ln)
		{
			type = 0;
			line = 0;
			symbol = NULL;
			parent = NULL;
			domain = NULL;
			filename = f;
			line = ln;
			varsize = -1;
			offset = -1;
			offsettype = -1;
			size = -1;
			varlist = NULL;
			value.integer = 0;
			closure = false;
		}
		void release()
		{
			delete this;
		}
		void add(node *o)
		{
			o->setparent(this);
			l.push_back(o);
		}

		void clone(node * v)
		{
			s = v->s;
			type = v->type;
			for (auto n : v->l)
			{
				if (n == NULL){
					node* cpyn = new node();
					cpyn->clone(n);
					l.push_back(cpyn);
				}
				else {
					l.push_back(n);//占位
				}
			}
			filename = v->filename;
			symbol = v->symbol;
			line = v->line;
			parent = v->parent;
			varsize = v->varsize;
			offset = v->offset;
			offsettype = v->offsettype;
			size = v->size;
			varlist = v->varlist;
			value = v->value;
			closure = v->closure;
		}

		void setparent(node* p)
		{
			parent = p;
		}

		void addtoleft(node *p)
		{
			if (l.size() < 1)
			{
				l.resize(1);
			}
			if (symbol && symbol->getparamleftlimit())
			{
				if (p->type != CPPS_VARNAME && p->type != CPPS_OGETOBJECT && p->type != CPPS_OGETCHIILD && p->type != CPPS_OOFFSET)
				{
					throw(cpps_error(p->filename, p->line, cpps_error_paramerror, " The left side of %s must be a variable.",s.c_str()));
				}
				if (p->type == CPPS_VARNAME)
					p->type = CPPS_QUOTEVARNAME;
				else if (p->type == CPPS_OGETOBJECT)
					p->type = CPPS_QUOTEGETOBJECT;
				else if (p->type == CPPS_OGETCHIILD)
					p->type = CPPS_QUOTEGETCHIILD;
				else if (p->type == CPPS_OOFFSET)
					p->type = CPPS_QUOTEOFFSET;

			}
			if (symbol && symbol->getparamrightlimit() 
				&& symbol->getparamnum() == 1)
			{
				if (p->type != CPPS_VARNAME && p->type != CPPS_OGETOBJECT && p->type != CPPS_OGETCHIILD && p->type != CPPS_OOFFSET)
				{
					throw(cpps_error(p->filename, p->line, cpps_error_paramerror, "The right side of %s must be a variable.", s.c_str()));
				}
				if (p->type == CPPS_VARNAME)
					p->type = CPPS_QUOTEVARNAME;
				else if (p->type == CPPS_OGETOBJECT)
					p->type = CPPS_QUOTEGETOBJECT;
				else if (p->type == CPPS_OGETCHIILD)
					p->type = CPPS_QUOTEGETCHIILD;
				else if (p->type == CPPS_OOFFSET)
					p->type = CPPS_QUOTEOFFSET;
			}
			l[0] = p;
			p->setparent(this);
		}

		node* getleft()
		{
			if (l.size() >= 1)
			{
				return l[0];
			}
			return NULL;
		}

		void addtoright(node *p)
		{
			if (l.size() < 2)
			{
				l.resize(2);
			}
			if (symbol && symbol->getparamrightlimit()
				&& symbol->getparamnum() >=2)
			{
				if (p->type != CPPS_VARNAME && p->type != CPPS_OGETOBJECT && p->type != CPPS_OGETCHIILD && p->type != CPPS_OOFFSET)
				{
					throw(cpps_error(p->filename, p->line, cpps_error_paramerror, " The left side of %s must be a variable", s.c_str()));
				}
				if (p->type == CPPS_VARNAME)
					p->type = CPPS_QUOTEVARNAME;
				else if (p->type == CPPS_OGETOBJECT)
					p->type = CPPS_QUOTEGETOBJECT;
				else if (p->type == CPPS_OGETCHIILD)
					p->type = CPPS_QUOTEGETCHIILD;
				else if (p->type == CPPS_OOFFSET)
					p->type = CPPS_QUOTEOFFSET;
			}
			l[1] = p;
			p->setparent(this);
		}


		node* getright()
		{
			if (l.size() >= 2)
			{
				return l[1];
			}
			return NULL;
		}

		void setdomain(cpps_node_domain* d)
		{
			domain = d;
		}


		std::string s;
		std::vector<node*> l;
		int32 type;
		std::string filename;
		cpps_symbol* symbol;
		node *parent;
		cpps_node_domain* domain;
		int32 line;
		bool closure;

		//解释转化
		union Value
		{
			cpps_number			number;		// double float 
			cpps_integer		integer;	// int
			int32				b;			// bool
			cpps_cppsclassvar	*str;		//string
		};
		Value					value;		//值。

		//解释层动态计算内存地址.=========
		int8 varsize;	//类变量计数 (只包含变量) 前提是类
		int16 offset;	//自身偏移
		int8 offsettype; //偏移类型 0 global 1 left 2 self
		usint16 size;	//子节点数量 ( 只包含类 名空间 函数 , 非类情况下包含变量) 65535个节点还不够吗?

		std::unordered_map<std::string, node*>		*varlist; //为了运行提速,牺牲解释速度.
		void regnode(std::string& s, node* n)
		{
			if (varlist == NULL) //需要在添加
			{
				varlist = new std::unordered_map<std::string, node*>();
			}
			varlist->insert(std::unordered_map<std::string, node*>::value_type(s, n));
		}
		void unregnode(std::string& s)
		{
			if (varlist != NULL) //需要在添加
			{
				varlist->erase(s);
			}
		}
		node* getnode(std::string &s ,bool b = false)
		{
			if (varlist != NULL) //需要在添加
			{
				std::unordered_map<std::string, node*>::iterator it = varlist->find(s);
				if (it != varlist->end())
				{
					return it->second;
				}
			}
			if ((type != CPPS_ODEFVAR_LAMBDA_FUNC || b == true)&& parent != NULL)
			{
				return parent->getnode(s,b);
			}
			return NULL;
		}

	};









}
#endif // CPPS_OBJ_CPPS_HEAD_
