#pragma once
#include <Windows.h>
#include <memory>
#include "DLL.h"

using namespace std;

#define FN(fn) FN_ ## fn				// function name
#define FNP(fn) FNT_ ## fn				// function pointer
#define FNPT(fn) (__stdcall *FNP(fn))	// function pointer typedef
#define FNPA(fn) fptr_ ## fn			// function pointer attribute
#define FNPAD(fn) FNP(fn) FNPA(fn)		// function pointer attribute declaration
#define FNPI(lib, fn) FNPA(fn) = (FNP(fn))lib->getProcAddress(FN(fn))

#define FN_GET_SERVICE_INFO		"GetServiceInfo"
#define FN_INITIALIZE			"Initialize"
#define FN_SET_LOG_LEVEL		"SetLogLevel"
#define FN_SEND_COMMAND			"SendCommand"
#define FN_SET_CALLBACK			"SetCallback"
#define FN_SET_CALLBACK_EX		"SetCallbackEx"
#define FN_FREE_MEMORY			"FreeMemory"
#define FN_UNINITIALIZE			"UnInitialize"

typedef bool (*TRANSAQ_CALLBACK) (BYTE* pData);
typedef bool (*TRANSAQ_CALLBACK_EX) (BYTE* pData, void*);

typedef int FNPT(GET_SERVICE_INFO) (const BYTE* request, BYTE** response);
typedef BYTE* FNPT(INITIALIZE) (const BYTE* logPath, int logLevel);
typedef BYTE* FNPT(SET_LOG_LEVEL) (int logLevel);
typedef BYTE* FNPT(SEND_COMMAND) (BYTE* pData);
typedef bool FNPT(SET_CALLBACK) (TRANSAQ_CALLBACK pCallback);
typedef bool FNPT(SET_CALLBACK_EX) (TRANSAQ_CALLBACK_EX pCallbackEx, void* userData);
typedef bool FNPT(FREE_MEMORY) (BYTE* pData);
typedef BYTE* FNPT(UNINITIALIZE) ();

class CTransaqWrapper
{
public:
	CTransaqWrapper(shared_ptr<CDLL> lib);
	virtual ~CTransaqWrapper();
	virtual int GetServiceInfo(const BYTE* request, BYTE** response);
	virtual BYTE* Initialize(const BYTE* logPath, int logLevel);
	virtual BYTE* SetLogLevel(int logLevel);
	virtual BYTE* SendCommand(BYTE* pData);
	virtual bool SetCallback(TRANSAQ_CALLBACK pCallback);
	virtual bool SetCallbackEx(TRANSAQ_CALLBACK_EX pCallbackEx, void* userData);
	virtual bool FreeMemory(BYTE* pData);
	virtual BYTE* UnInitialize();
private:
	shared_ptr<CDLL> mLib;
	FNPAD(GET_SERVICE_INFO);
	FNPAD(INITIALIZE);
	FNPAD(SET_LOG_LEVEL);
	FNPAD(SEND_COMMAND);
	FNPAD(SET_CALLBACK);
	FNPAD(SET_CALLBACK_EX);
	FNPAD(FREE_MEMORY);
	FNPAD(UNINITIALIZE);
};

