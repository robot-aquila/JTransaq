#include <exception>
#include "DLL.h"
#include "Conv.h"

CDLL::CDLL(const wstring& module_name)
{
	hLib = LoadLibrary(module_name.c_str());
	if ( hLib == NULL ) {
		throw std::exception((string("Unable to load dll: ") + TO_UTF8(module_name)).c_str());
	}
}


FARPROC CDLL::getProcAddress(const char* pszProcName)
{
	FARPROC addr = GetProcAddress(hLib, pszProcName);
	if ( addr == NULL ) {
		throw std::exception((string("Procedure not found: ") + pszProcName).c_str());
	}
	return addr;
}


CDLL::~CDLL()
{
	FreeLibrary(hLib);
}
