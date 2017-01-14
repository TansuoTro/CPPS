#ifndef CPPS_VALUE_CPPS_HEAD_
#define CPPS_VALUE_CPPS_HEAD_

//===================================
//@Author		:	Johnson
//@Email		:	jiang_4177@163.com
//@Date			:	2015/11/24 (yy/mm/dd)
//@Module		:	CPPS_VALUE
//@Description	:	cppsֵ
//@website		:	http://cpps.wiki
//==================================

class cpps_regvar;
namespace cpps
{
	struct cpps_function;
	struct cpps_domain;
	struct cpps_cppsclass;
	struct cpps_cppsclassvar;
	struct cpps_value
	{
		cpps_value()
		{
			tt = CPPS_TNIL;
		}
		
		cpps_value(cpps_number n)
		{
			tt = CPPS_TNUMBER;
			value.number = n;
		}
		cpps_value(cpps_integer i)
		{
			tt = CPPS_TINTEGER;
			value.integer = i;
		}
		cpps_value(bool b)
		{
			tt = CPPS_TBOOLEAN;
			value.b = b;
		}
		cpps_value(cpps_function* f)
		{
			tt = CPPS_TFUNCTION;
			value.func = f;
			parentLambdaVar = NULL;
		}

		cpps_value(cpps_domain* d)
		{
			tt = CPPS_TDOMAIN;
			value.domain = d;
		}
		cpps_value(cpps_cppsclass* d)
		{
			tt = CPPS_TCLASS;
			value.domain = (cpps_domain*)(d);
		}
		cpps_value(cpps_cppsclassvar* d)
		{
			tt = CPPS_TCLASSVAR;
			value.domain = (cpps_domain*)(d);
		}
// 		cpps_value(cpps_regvar* v)
// 		{
// 			tt = CPPS_TREGVAR;
// 			value.var = v;
// 		}
		cpps_value(cpps_value* v)
		{
			tt = CPPS_TREGVAR;
			value.value = v;
		}
		cpps_value(const char* d)
		{
			tt = CPPS_TSTRING;
			str = d;
		}
		cpps_value(std::string s)
		{
			tt = CPPS_TSTRING;
			str = s;
		}
		~cpps_value()
		{

		}
		//Ϊ�˿��Ե�map��key ��Ҫʵ�� < > == 3������
		bool				operator < (const cpps_value &right) const
		{
			if (tt == right.tt)
			{
				switch (tt)
				{
				case CPPS_TNUMBER: return value.number < right.value.number;
				case CPPS_TINTEGER: return value.integer < right.value.integer;
				case CPPS_TSTRING:  return str < right.str;
				default:
					throw("<   ... �����Ե�key�ã�");
				}
			}
			return tt < right.tt;
		}

		bool				operator >(const cpps_value &right) const
		{
			if (tt == right.tt)
			{
				switch (tt)
				{
				case CPPS_TNUMBER: return value.number > right.value.number;
				case CPPS_TINTEGER: return value.integer > right.value.integer;
				case CPPS_TSTRING:  return str > right.str;
				default:
					throw(">   ... �����Ե�key�ã�");
				}
			}
			return tt > right.tt;
		}

		bool				operator == (const cpps_value &right) const
		{
			if (tt == right.tt)
			{
				switch (tt)
				{
				case CPPS_TNUMBER: return value.number == right.value.number;
				case CPPS_TINTEGER: return value.integer == right.value.integer;
				case CPPS_TSTRING:  return str == right.str;
				default:
					throw("==   ... �����Ե�key�ã�");
				}
			}
			return false;
		}
		
		bool				isDomain()
		{
			return tt == CPPS_TDOMAIN || tt == CPPS_TCLASS || tt == CPPS_TCLASSVAR;
		}

		struct hash
		{	
			size_t operator()(const cpps_value& _Keyval) const
			{	
				switch (_Keyval.tt)
				{
				case CPPS_TNUMBER: return std::hash<cpps_number>()(_Keyval.value.number);
				case CPPS_TINTEGER: return std::hash<cpps_integer>()(_Keyval.value.integer);
				case CPPS_TSTRING:  return std::hash<std::string>()(_Keyval.str);
				default:
					throw("==   ... �����Ե�hash�ã�");
				}
				return _Keyval.tt;
			}
		};

		union Value
		{
			cpps_number			number;		// double float 
			cpps_integer		integer;	// double float 
			int32				b;			// bool
			void*				p;			// �û��Զ�������
			cpps_function*		func;		// func
			cpps_domain *		domain;		// domain
			cpps_regvar *		var;		// ����ָ��
			cpps_value *		value;		// ֵ����
		};
		std::string				str;		//�ַ�������
		Value					value;		//ֵ��
		int32					tt;			//����
		cpps_domain*			parentLambdaVar; //lambda����

	};

#define cpps_integer2number(i) (cpps_number)(i)
#define cpps_number2integer(n) (cpps_integer)(n)

	cpps_number	cpps_to_number(cpps_value obj);
	cpps_integer cpps_to_integer(cpps_value obj);
	std::string cpps_to_string(cpps_value obj);

	static cpps_value		nil;
}


#endif // CPPS_VALUE_CPPS_HEAD_