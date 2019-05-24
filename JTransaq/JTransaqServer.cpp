#include "JTransaqServer.h"
#include "Conv.h"
#include "DLL.h"
#include <Windows.h>
#include <iostream>

#ifndef JTRANSAQ_MODULE_NAME
#define JTRANSAQ_MODILE_NAME "JTransaq64.dll"
#endif

#define JTRANSAQ_RETURN_VOID(p_str) \
	if (p_str != 0) { \
		std::exception e((const char*) p_str); \
		wrapper->FreeMemory(p_str); \
		throw e; \
	} \


wstring replace_mod(wstring new_module) {
	wstring curr_mod(FROM_UTF8(JTRANSAQ_MODULE_NAME));
	HMODULE h = ::GetModuleHandle(curr_mod.c_str());
	wchar_t path[MAX_PATH + 1] = { 0 };
	DWORD len = ::GetModuleFileName(h, path, MAX_PATH);
	wstring result(path, len - curr_mod.length());
	result.append(new_module);
	return result;
}


JTransaqServer::JTransaqServer(JTransaqHandler* p_handler)
	: handler(p_handler)
{
	shared_ptr<CDLL> lib = make_shared<CDLL>(replace_mod(L"txmlconnector64.dll"));
	wrapper = make_shared<CTransaqWrapper>(lib);
	if (!wrapper->SetCallbackEx(JTransaqServer::CallbackEx, static_cast<void*>(this))) {
		throw std::exception("Error setting callback function");
	}
}


void JTransaqServer::Initialize(const wstring &logPath, int logLevel)
{
	string log_path = TO_UTF8(logPath);
	BYTE* p_str = wrapper->Initialize((const BYTE*)log_path.c_str(), logLevel);
	JTRANSAQ_RETURN_VOID(p_str);
}


void JTransaqServer::SetLogLevel(int logLevel)
{
	BYTE* p_str = wrapper->SetLogLevel(logLevel);
	JTRANSAQ_RETURN_VOID(p_str);
}


void JTransaqServer::SendCommand(const wstring &data)
{
	static string success_tpl("<result success=\"true\"/>");
	string x = TO_UTF8(data);
	BYTE* p_str = wrapper->SendCommand((BYTE*)x.c_str());
	if (p_str == 0) {
		throw std::exception("Unexpected null response");
	}
	string result((const char*)p_str);
	wrapper->FreeMemory(p_str);
	if (result != success_tpl) {
		throw std::exception(result.c_str());
	}
}


void JTransaqServer::UnInitialize()
{
	BYTE* p_str = wrapper->UnInitialize();
	JTRANSAQ_RETURN_VOID(p_str);
}


JTransaqServer::~JTransaqServer()
{

}


bool JTransaqServer::CallbackEx(BYTE* p_data, void* p_void)
{
	if (!p_void || !p_data) {
		return false;
	}
	JTransaqServer* p_server = static_cast<JTransaqServer*>(p_void);
	wstring data = FROM_UTF8(p_data);
	p_server->wrapper->FreeMemory(p_data);
	return p_server->handler->Handle(data);
}

