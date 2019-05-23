#pragma once
#include <string>
#include <Windows.h>

using namespace std;

class CDLL
{
public:
	CDLL(const wstring& module_name);
	FARPROC getProcAddress(const char* pszProcName);
	virtual ~CDLL();
private:
	HINSTANCE hLib;
};

