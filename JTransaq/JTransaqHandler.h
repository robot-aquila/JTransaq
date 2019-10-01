#pragma once
#include <string>
#include <iostream>

using namespace std;

class JTransaqHandler
{
public:
	JTransaqHandler()
	{
	}

	virtual bool Handle(const wstring& data)
	{
		wcout << L"JTransaqHandler::Handle(const wstring&): " << data.substr(0, 32) << endl;
		return false;
	}

	virtual ~JTransaqHandler()
	{
	}

};

