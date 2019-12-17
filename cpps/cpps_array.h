#ifndef CPPS_ARRAY_CPPS_HEAD_
#define CPPS_ARRAY_CPPS_HEAD_

//===================================
//@Author		:	Johnson
//@QQ			:	88481106
//@Email		:	jiang_4177@163.com
//@Date			:	2015/12/24 (yy/mm/dd)
//@Module		:	CPPS_ARRAY
//@Description	:	vectorע����
//@website		:	http://cpps.wiki
//==================================


namespace cpps
{
	struct cpps_vector
	{
		cpps_vector()
		{
			_begin = _vec.begin();
		}
		void			push_back(cpps_value v)
		{
			_vec.push_back(v);
		}
		void			pop_back()
		{
			_vec.pop_back();
		}
		void			push_front(cpps_value v)
		{
			_vec.insert(_vec.begin(),v);
		}
		void			pop_front()
		{
			_vec.erase(_vec.begin());
		}
		void			insert(cpps_integer idx, cpps_value v)
		{
			_vec.insert(_vec.begin() + idx, v);
		}
		cpps_value		at(cpps_integer idx)
		{
			if (idx < 0 || idx >= size())
			{
				throw(cpps_error("0", 0, 0, "vector Խ���ˣ�"));
				return cpps::nil;
			}
			return _vec.at((size_t)idx);
		}
		cpps_value&		cpps_at(cpps_integer idx)
		{
			if (idx < 0 || idx >= size())
			{
				throw(cpps_error("0", 0, 0, "vector Խ���ˣ�"));
				return cpps::nil;
			}
			return _vec[(usint32)idx];
		}
		void			erase(cpps_integer idx)
		{
			_vec.erase(_vec.begin() + idx);
		}
		void			pop()
		{
			_begin = _vec.erase(_begin);
		}
		void			begin()
		{
			_begin = _vec.begin();
		}
		bool			end()
		{
			return _begin != _vec.end();
		}
		void			next()
		{
			if (_begin != _vec.end())
				++_begin;
		}
		cpps_value			it()
		{
			cpps_value ret;
			if (_begin != _vec.end())
			{
				ret = *_begin;
			}
			return ret;
		}
		void			clear()
		{
			_vec.clear();
		}
		cpps_integer	size()
		{
			return (cpps_integer)_vec.size();
		}

		void			resize(cpps_integer s)
		{
			_vec.resize((size_t)s);
		}
		std::vector<cpps_value>&	realvector()
		{
			return _vec;
		}
	private:
		std::vector<cpps_value>				_vec;
		std::vector<cpps_value>::iterator	_begin;

	};
	void	cpps_regarray(C *c);
}

#endif // CPPS_ARRAY_CPPS_HEAD_