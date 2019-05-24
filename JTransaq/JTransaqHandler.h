#pragma once
#include <string>

using namespace std;

class JTransaqHandler
{
public:
	JTransaqHandler() { }
	virtual bool Handle(const wstring& data) { return false; }
	virtual ~JTransaqHandler() { }
};

