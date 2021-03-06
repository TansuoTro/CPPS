#include "cpps.h"

using namespace std;

namespace cpps
{
	bool cpps_io_file_exists(std::string path);
	void cpps_load_filebuffer(const char* path, std::string& fileSrc);
	std::string getfilenamenotext(std::string str);
	std::string cpps_rebuild_filepath(std::string path);
	void cpps_base_printf(object b)
	{
		if (type(b) == CPPS_TNUMBER)
		{
			double s = object_cast<double>(b);
			cout << s;
		}
		else if (type(b) == CPPS_TINTEGER)
		{
			int64 s = object_cast<int64>(b);
			cout << s;
		}
		else if (type(b) == CPPS_TSTRING)
		{
			std::string s = object_cast<std::string>(b);
			cout << s.c_str();
		}
		else if (type(b) == CPPS_TBOOLEAN)
		{
			bool bl = object_cast<bool>(b);
			cout << (bl ? "true" : "false");
		}
		else if (type(b) == CPPS_TNIL)
		{
			cout << "nil";
		}
		else if (type(b) == CPPS_TCLASSVAR)
		{
			if (b.value.value.domain->domainname == "vector")
			{
				cout << "[";
				cpps_vector *v = cpps_converter<cpps_vector*>::apply(b.value);
				if (v)
				{
					for (v->begin(); v->end(); v->next())
					{
						cpps_base_printf(v->it());
						cout << ",";
					}
				}
				cout << "]";
			}
			else if (b.value.value.domain->domainname == "map")
			{
				cout << "{";
				cpps_map *v = cpps_converter<cpps_map*>::apply(b.value);
				if (v)
				{
					for (v->begin(); v->end(); v->next())
					{
						cpps_base_printf(v->key());
						cout << ":";
						cpps_base_printf(v->it());
						cout << ",";
					}
				}
				cout << "}";
			}
			else if (b.value.value.domain->domainname == "unordered_map")
			{
				cout << "{";
				cpps_unordered_map *v = cpps_converter<cpps_unordered_map*>::apply(b.value);
				if (v)
				{
					for (v->begin(); v->end(); v->next())
					{
						cpps_base_printf(v->key());
						cout << ":";
						cpps_base_printf(v->it());
						cout << ",";
					}
				}
				cout << "}";
			}
			
		}
		else
		{
			cout << "暂时不支持 '" << type_s(b).c_str() << "' 类型的输出.";
		}
	}
	void cpps_base_printfln(object b)
	{
		if (type(b) == CPPS_TNUMBER)
		{
			double s = object_cast<double>(b);
			cout << s << endl;
		}
		else if (type(b) == CPPS_TINTEGER)
		{
			int64 s = object_cast<int64>(b);
			cout << s << endl;
		}
		else if (type(b) == CPPS_TSTRING)
		{
			std::string s = object_cast<std::string>(b);
			cout << s.c_str() << endl;
		}
		else if (type(b) == CPPS_TBOOLEAN)
		{
			bool bl = object_cast<bool>(b);
			cout << (bl ? "true" : "false") << endl;
		}
		else if (type(b) == CPPS_TNIL)
		{
			cout << "nil" << endl;
		}
		else if (type(b) == CPPS_TCLASSVAR)
		{
			
			if (b.value.value.domain->domainname == "vector")
			{
				cout << "[";
				cpps_vector *v = cpps_converter<cpps_vector*>::apply(b.value);
				if (v)
				{
					for (v->begin(); v->end(); v->next())
					{
						cpps_base_printf(v->it());
						cout << ",";
					}
				}
				cout << "]";
			}
			else if (b.value.value.domain->domainname == "map")
			{
				cout << "{";
				cpps_map *v = cpps_converter<cpps_map*>::apply(b.value);
				if (v)
				{
					for (v->begin(); v->end(); v->next())
					{
						cpps_base_printf(v->key());
						cout << ":";
						cpps_base_printf(v->it());
						cout << ",";
					}
				}
				cout << "}";
			}
			else if (b.value.value.domain->domainname == "unordered_map")
			{
				cout << "{";
				cpps_unordered_map *v = cpps_converter<cpps_unordered_map*>::apply(b.value);
				if (v)
				{
					for (v->begin(); v->end(); v->next())
					{
						cpps_base_printf(v->key());
						cout << ":";
						cpps_base_printf(v->it());
						cout << ",";
					}
				}
				cout << "}";
			}
			cout << endl;
		}
		else
		{
			cout << "暂时不支持 '" << type_s(b).c_str() << "' 类型的输出." << endl;
		}
	}

	void cpps_base_sleep(cpps_integer msec)
	{
#ifdef _WIN32
		Sleep((usint32)msec);
#else
		usleep((int32)(msec * 1000));
#endif
	}

	cpps_number cpps_base_tonumber(cpps_value v)
	{
		return cpps_to_number(v);
	}
	cpps_integer cpps_base_tointeger(cpps_value v)
	{
		return cpps_to_integer(v);
	}
	std::string cpps_base_tostring(cpps_value v)
	{
		return cpps_to_string(v);
	}
	bool cpps_base_isstring(cpps_value v)
	{
		return v.tt == CPPS_TSTRING;
	}
	bool cpps_base_isint(cpps_value v)
	{
		return v.tt == CPPS_TINTEGER;
	}
	bool cpps_base_isbool(cpps_value v)
	{
		return v.tt == CPPS_TBOOLEAN;
	}
	bool cpps_base_isnumber(cpps_value v)
	{
		return v.tt == CPPS_TNUMBER;
	}
	bool cpps_base_isnull(cpps_value v)
	{
		return v.tt == CPPS_TNIL;
	}
	bool cpps_base_isfunction(cpps_value v)
	{
		return v.tt == CPPS_TFUNCTION || v.tt == CPPS_TLAMBDAFUNCTION;
	}
	cpps_integer cpps_base_objtype(cpps_value v)
	{
		return v.tt;
	}
	void cpps_base_system(std::string v)
	{
		system(v.c_str());
	}
	void cpps_base_setconsoletitle(std::string title)
	{
#ifdef WIN32
		SetConsoleTitleA(title.c_str());
#endif
	}
	
	void cpps_assert(bool b)
	{
		assert(b);
	}
	bool cpps_decodecpps(std::string file, std::string outfile)
	{
		FILE *pfile = fopen(file.c_str(), "rb+");
		if (pfile)
		{
			long cur = ftell(pfile);
			fseek(pfile, 0, SEEK_END);
			cpps_integer size = ftell(pfile);
			fseek(pfile, cur, SEEK_SET);

			char *pBuffer = new char[size + 1];
			memset(pBuffer, 0, size + 1);
			fread(pBuffer, size, 1, pfile);
			fclose(pfile);
			std::string fileSrc = pBuffer;
			if (fileSrc.substr(0, 11) == "cpps_encode")
			{
				std::string decode;
				for (size_t i = 11; i < fileSrc.size(); i++)
				{
					decode.append(1, fileSrc[i] - CPPS_ENCODE_CPPS_KEY);
				}
				fileSrc = decode;
			}

			FILE *poutfile = fopen(outfile.c_str(), "wb+");
			if (poutfile)
			{
				fwrite(fileSrc.c_str(), fileSrc.size(), 1, poutfile);
				fclose(poutfile);
			}

			delete[] pBuffer;
			return true;
		}
		return false;

	}
	bool cpps_encodecpps(std::string file,std::string outfile)
	{
		FILE *pfile = fopen(file.c_str(), "rb+");
		if(pfile)
		{
			long cur = ftell(pfile);
			fseek(pfile, 0, SEEK_END);
			cpps_integer size = ftell(pfile);
			fseek(pfile, cur, SEEK_SET);

			char *pBuffer = new char[size + 1];
			fread(pBuffer, size, 1, pfile);
			fclose(pfile);

			std::string outbuffer = "cpps_encode";
			for (cpps_integer i = 0; i < size; i++)
			{
				outbuffer.append(1,pBuffer[i] + CPPS_ENCODE_CPPS_KEY);
			}
			FILE *poutfile = fopen(outfile.c_str(), "wb+");
			if (poutfile)
			{
				fwrite(outbuffer.c_str(), outbuffer.size(), 1, poutfile);
				fclose(poutfile);
			}

			delete[] pBuffer;
			return true;
		}
		return false;
	}
	struct ThreadParameter
	{
		C*c;
		cpps_value func;
		cpps_value value;
#ifdef WIN32
		HANDLE eventFinish;
#endif

	};
	void		gc_cleanup(C *c, int tid);
	static unsigned int threadFunction(void *p)
	{
		ThreadParameter*param = (ThreadParameter*)p;
		C*c = param->c;
		cpps_value func = param->func;
		cpps_value value = param->value;
#ifdef WIN32
		SetEvent(param->eventFinish);
#endif
		cpps_try
		object ret = dofunction(c, func, value);
		cpps_catch
		gc_cleanup(c, GetCurrentThreadId());
		return 0;
	}
	
	bool	cpps_loadlibrary(C *c,std::string libname)
	{
		std::string path = "lib/"+ libname + "/";
		std::string fpath;

		if (c->modulelist.find(libname) != c->modulelist.end()) return true;
		bool sv = false;
#ifdef WIN32

		fpath = cpps_rebuild_filepath(path + (libname + ".dll"));
		if (!fpath.empty())
		{
			HMODULE module = ::LoadLibraryA(fpath.c_str());
			std::string libfuncname = "cpps_attach";
			if (module == NULL)
			{
				printf("Load module【%s】 faild.\r\n", libname.c_str());
				FreeLibrary(module);
				return false;
			}

			cpps_attach_func cpps_attach = (cpps_attach_func)GetProcAddress(module, libfuncname.c_str());
			if (cpps_attach == NULL)
			{
				FreeLibrary(module);
				printf("Load module 【%s】 faild\r\n", libname.c_str());
				return false;
			}

			c->modulelist.insert(std::unordered_map<std::string, HMODULE>::value_type(libname, module));
			sv = true;

			cpps_attach(c);


#elif LINUX

		fpath = cpps_rebuild_filepath(path + "lib" + (libname + ".so"));
		if (!fpath.empty())
		{
			HMODULE module = dlopen(fpath.c_str(), RTLD_LAZY);
			if (module == NULL)
			{
				printf("dlopen [%s]:%s faild\r\n", libname.c_str(), dlerror());
				return false;
			}
			dlerror();
			CPPS_ST_API* api = (CPPS_ST_API*)dlsym(module, "LIBAPI");
			if (api == NULL)
			{
				dlclose(module);
				printf("dlsym [LIBAPI] faild\r\n");
				return false;
			}

			c->modulelist.insert(std::unordered_map<std::string, HMODULE>::value_type(libname, module));
			sv = true;

			api->cpps_attach(c);


#endif
		}
		fpath = cpps_rebuild_filepath(path + "main.cpp");
		if (!fpath.empty())
		{
			if(!sv)
				c->modulelist.insert(std::unordered_map<std::string, HMODULE>::value_type(libname, NULL));
			std::string fileSrc;
			cpps_load_filebuffer(fpath.c_str(), fileSrc);
			node* o = loadbuffer(c,  fileSrc, fpath);
			cpps_stack* stack = c->stack_alloc();
			stack->init("main.cpp", 0, "import");

			c->push_stack(stack);
			cpps_step_all(c, CPPS_SINGLERET, c->_G,c->_G, o);
			c->pop_stack();


			cpps_gc_check_step(c);

			c->stack_free(stack);
		}
		return true;
	}
	bool	cpps_freelibrary(C*c, std::string libname)
	{

		if (c->modulelist.find(libname) == c->modulelist.end()) return true;

#ifdef WIN32

		bool ret = false;
		std::unordered_map<std::string, HMODULE>::iterator it = c->modulelist.find(libname);
		if (it != c->modulelist.end())
		{
			HMODULE module = it->second;
			if (module) {
				std::string libfuncname = "cpps_detach";

				cpps_detach_func cpps_detach = (cpps_detach_func)GetProcAddress(module, libfuncname.c_str());
				if (cpps_detach == NULL)
				{
					printf("Free Module【%s】 faild.\r\n", libname.c_str());
				}
				else
				{
					cpps_detach(c);
				}


				FreeLibrary(module);
			}
			c->modulelist.erase(it);
			ret = true;
		}
		return ret;

#elif LINUX
		bool ret = false;
		std::unordered_map<std::string, HMODULE>::iterator it = c->modulelist.find(libname);
		if (it != c->modulelist.end())
		{
			HMODULE module = it->second;



			dlerror();
			CPPS_ST_API* api = (CPPS_ST_API*)dlsym(module, "LIBAPI");
			if (api == NULL)
			{
				printf("dlsym 【LIBAPI】 faild\r\n");
			}
			else
			{
				api->cpps_detach(c);
			}


			dlclose(module);
			c->modulelist.erase(it);
			ret = true;
		}
		return ret;

#endif
	}
	cpps_value cpps_getargs(C* c)
	{
		cpps_vector* vct;
		cpps_value ret = newclass<cpps_vector>(c, &vct);
		for (int i = 0; i < c->application_argc; i++)
		{
			vct->push_back(cpps_value(c, c->application_argv[i]));
		}
		return ret;
	}
	void cpps_regbase(C *c)
	{
		module(c)[
			_class<std::string>("String")
		];
		module(c)[
			_class<C>("C_STATE"),
			def("printf", cpps_base_printf),
			def("print", cpps_base_printf),
			def("printfln", cpps_base_printfln),
			def("println", cpps_base_printfln),
			def("exit",exit),
			def("sleep", cpps_base_sleep),
			def("Sleep", cpps_base_sleep),
			def("tonumber", cpps_base_tonumber),
			def("toint", cpps_base_tointeger),
			def("tostring", cpps_base_tostring),
			def("isstring", cpps_base_isstring),
			def("isint", cpps_base_isint),
			def("isbool", cpps_base_isbool),
			def("isnull", cpps_base_isnull),
			def("isnumber", cpps_base_isnumber),
			def("isfunction", cpps_base_isfunction),
			def("objtype", cpps_base_objtype),
			def("system", cpps_base_system),
			def("SetConsoleTitle", cpps_base_setconsoletitle),
			def("assert", cpps_assert),
			defvar(c,"_VERSION", CPPS_VER),
			defvar(c,"_VERSIONNO", CPPS_VERN),
			def("encodecpps", cpps_encodecpps),
			def("decodecpps", cpps_decodecpps),
			def_inside("loadlibrary", cpps_loadlibrary),
			def_inside("freelibrary", cpps_freelibrary),
			def_inside("getargs", cpps_getargs)
		];

	}
}
