#include "cpps.h"

namespace cpps {
	cpps_value cpps_execute_callfunction(C* c, cpps_function* f, cpps_domain* domain, std::string filename, int32 line, std::string funcname, std::vector<cpps_value>& params);
	cpps_value cpps_async_object::call(C* c)
	{
		return cpps_execute_callfunction(c, f, leftdomain, filename, line, funcname, params);
	}
}
