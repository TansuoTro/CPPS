#include "cpps.h"

namespace cpps
{
	void cpps_reglock(C *c)
	{
		module(c)[
			_class<cpps_lock>("threadlock")
				.def("lock", &cpps_lock::lock)
				.def("unlock", &cpps_lock::unlock)
		];
	}
}