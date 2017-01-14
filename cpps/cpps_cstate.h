

#ifndef CPPS_CSTATE_CPPS_HEAD_
#define CPPS_CSTATE_CPPS_HEAD_

//===================================
//@Author		:	Johnson
//@Email		:	jiang_4177@163.com
//@Date			:	2015/11/20 (yy/mm/dd)
//@Module		:	CPPS_CSTATE
//@Description	:	CppsState
//@website		:	http://cpps.wiki
//==================================
namespace cpps
{
	struct cpps_regfunction;
	struct cpps_regvar;
	struct cpps_reg;
	struct Node;
	struct cpps_domain;
	struct cpps_value;
	struct cpps_cppsclassvar;
	struct cpps_stack
	{
		cpps_stack(std::string f, int32 l,std::string func)
		:f(f), l(l), func(func){}

		std::vector<cpps_value> *createparams();
		cpps_value *create_cpps_value();
		std::string f;
		std::string func;
		int32			l;
	};

	struct C
	{
		C();
		void	push(Node *_o);
		void	push_stack(cpps_stack* stack);
		void	pop_stack();
		void	debugopen();
		void	debugclose();
		std::vector<cpps_stack*>&	getcallstack();

		Node* o;
		cpps_domain*						_G;	//���ڵ�
		std::vector<cpps_stack*>			_callstack; //��ջ
		std::unordered_set<cpps_regvar*>	barrierList; //�ֽ�List
		std::unordered_set<cpps_cppsclassvar *>			gen0; //�ֽ�List
		std::unordered_set<cpps_cppsclassvar *>			gen1; //�ֽ�List
		size_t								gen0size;//��������ǰռ�ڴ��С���ֽڣ�
		size_t								gen1size;//��������ǰռ�ڴ��С���ֽڣ�
		size_t								lastgensize;
		std::string							(*func)(std::string &);
		bool								debug;
		bool								isCheckGen1;
	};
}
#endif // CPPS_CSTATE_CPPS_HEAD_