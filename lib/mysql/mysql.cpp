﻿// libdemo.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"


#include <cpps.h>
#include <iostream>
#include <string>
#include <fstream>
#include "cpps_mysql.h"
#include "cpps_mysql_record.h"
#include "cpps_mysql_result.h"
using namespace cpps;
using namespace std;

cpps_value cpps_mysql_connect(cpps::C *c,cpps::object option)
{
	cpps_create_class_var(cpps_mysql, c, cpps_mysql_var, cpps_mysql_ptr);
	if (!cpps_mysql_ptr->connect(c, option)) return nil;
	return cpps_mysql_var;
}
#ifdef _WIN32
extern "C" _declspec(dllexport) void __stdcall cpps_attach(cpps::C *c)
#else
extern "C" void  cpps_attach(cpps::C* c)
#endif
{

	cpps::cpps_init_cpps_class(c);
   
	module(c, "mysql")[
		def_inside("connect", cpps_mysql_connect),
		_class<cpps_mysql>("mysql")
		.def("close",&cpps_mysql::close)
		.def("call",&cpps_mysql::call)
		.def("execute",&cpps_mysql::execute)
		.def("error",&cpps_mysql::error)
		.def("isconnect",&cpps_mysql::isconnect)
		.def("clear",&cpps_mysql::clear)
		.def("affected_rows",&cpps_mysql::affected_rows),
		_class<cpps_mysql_record>("mysql_record")
		.def("fields",&cpps_mysql_record::fields)
		.def("get",&cpps_mysql_record::get),
		_class< cpps_mysql_result>("mysql_result")
		.def("records",&cpps_mysql_result::records)
	];
   
}
#ifdef _WIN32
extern "C" _declspec(dllexport) void __stdcall cpps_detach(cpps::C *c)
#else
extern "C" void  cpps_detach(cpps::C * c)
#endif
{
}

#ifdef LINUX


extern "C" const CPPS_ST_API  LIBAPI = {
   cpps_attach,
   cpps_detach,
};

#endif