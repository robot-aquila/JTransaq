#pragma once
#include <string>
#include "JTransaqHandler.h"

using namespace std;

class JTransaqServer
{
public:
	JTransaqServer(JTransaqHandler* pHandler);
	virtual wstring Initialize(const wstring &logPath, int logLevel);
	virtual wstring SetLogLevel(int logLevel);
	virtual wstring SendCommand(const wstring &data);
	virtual wstring UnInitialize();
	virtual ~JTransaqServer();
private:

};

