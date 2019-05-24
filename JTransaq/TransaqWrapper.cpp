#include "TransaqWrapper.h"


CTransaqWrapper::CTransaqWrapper(shared_ptr<CDLL> lib)
	: mLib(lib)
{
	FNPI(lib, GET_SERVICE_INFO);
	FNPI(lib, INITIALIZE);
	FNPI(lib, SET_LOG_LEVEL);
	FNPI(lib, SEND_COMMAND);
	FNPI(lib, SET_CALLBACK);
	FNPI(lib, SET_CALLBACK_EX);
	FNPI(lib, FREE_MEMORY);
	FNPI(lib, UNINITIALIZE);
}


CTransaqWrapper::~CTransaqWrapper()
{

}


int CTransaqWrapper::GetServiceInfo(const BYTE* request, BYTE** response)
{
	return FNPA(GET_SERVICE_INFO)(request, response);
}


BYTE* CTransaqWrapper::Initialize(const BYTE* logPath, int logLevel)
{
	return FNPA(INITIALIZE)(logPath, logLevel);
}


BYTE* CTransaqWrapper::SetLogLevel(int logLevel)
{
	return FNPA(SET_LOG_LEVEL)(logLevel);
}


BYTE* CTransaqWrapper::SendCommand(BYTE* pData)
{
	return FNPA(SEND_COMMAND)(pData);
}


bool CTransaqWrapper::SetCallback(TRANSAQ_CALLBACK pCallback)
{
	return FNPA(SET_CALLBACK)(pCallback);
}

bool CTransaqWrapper::SetCallbackEx(TRANSAQ_CALLBACK_EX pCallbackEx, void* userData)
{
	return FNPA(SET_CALLBACK_EX)(pCallbackEx, userData);
}


bool CTransaqWrapper::FreeMemory(BYTE* pData)
{
	return FNPA(FREE_MEMORY)(pData);
}


BYTE* CTransaqWrapper::UnInitialize()
{
	return FNPA(UNINITIALIZE)();
}
