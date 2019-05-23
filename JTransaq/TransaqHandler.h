#pragma once
#include <string>

using namespace std;

class CTransaqHandler
{
public:
	CTransaqHandler() { }
	virtual bool Handle(const wstring& data) { return false; }
	virtual ~CTransaqHandler() { }
};

