

#ifndef CPPS_CSTATE_CPPS_HEAD_
#define CPPS_CSTATE_CPPS_HEAD_

//===================================
//@Author		:	Johnson
//@QQ			:	88481106
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
		std::unordered_set<cpps_cppsclassvar *>* getGen0(int tid = 0);
		std::unordered_set<cpps_cppsclassvar *>* getGen1(int tid = 0);
		void setGen0size(size_t s, int tid = 0);
		size_t getGen0size(int tid = 0);
		void setGen1size(size_t s, int tid = 0);
		size_t getGen1size(int tid = 0);
		void setLastgensize(size_t s, int tid = 0);
		size_t getLastgensize(int tid = 0);
		C();
		void																		push(Node *_o);
		void																		push_stack(cpps_stack* stack);
		void																		pop_stack();
		void																		resume();						 //��Ҫ���� �ڽӵ�catch��ʱ��Ҫ����resume() ���������ڴ��쳣����ʱ���������취�������
		void																		debugopen();
		void																		debugclose();
		std::vector<cpps_stack*>*													getcallstack();

		std::unordered_set<cpps_regvar*>* getBarrierList(int tid = GetCurrentThreadId());
		Node* o;
		cpps_domain*						_G;	//���ڵ�
		std::unordered_map<int,std::vector<cpps_stack*>*>							_callstack; //��ջ
		std::unordered_map<int, std::unordered_set<cpps_regvar*>*>					barrierList; //�ֽ�List
		std::unordered_map<int, std::unordered_set<cpps_cppsclassvar *>*>			gen0; //�ֽ�List
		std::unordered_map<int, std::unordered_set<cpps_cppsclassvar *>*>			gen1; //�ֽ�List
		std::unordered_map<int, size_t>												gen0size;//��������ǰռ�ڴ��С���ֽڣ�
		std::unordered_map<int, size_t>												gen1size;//��������ǰռ�ڴ��С���ֽڣ�
		std::unordered_map<int, size_t>												lastgensize;
		std::string																	(*func)(std::string &);
		std::unordered_map<std::string, HMODULE>									modulelist;
		bool																		debug;
		cpps_lock																	stacklock;
		//cpps_lock							gclock;
	};
}
#endif // CPPS_CSTATE_CPPS_HEAD_