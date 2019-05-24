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
		cout << "JTransaqHandler::Handle(const wstring&) called" << endl;
		return false;
	}

	virtual ~JTransaqHandler()
	{
	}

};

