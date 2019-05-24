#pragma once
#include <string>
#include <memory>
#include <exception>
#include "JTransaqHandler.h"
#include "TransaqWrapper.h"

using namespace std;

class JTransaqServer
{
public:
	JTransaqServer(JTransaqHandler* p_handler) throw (exception);
	virtual void Initialize(const wstring &logPath, int logLevel) throw (exception);
	virtual void SetLogLevel(int logLevel) throw (exception);
	virtual void SendCommand(const wstring &data) throw (exception);
	virtual void UnInitialize() throw (exception);
	virtual ~JTransaqServer();
private:
	static bool Callback(BYTE* p_data, void* p_void);
	shared_ptr<CTransaqWrapper> wrapper;
	JTransaqHandler* handler;
};

