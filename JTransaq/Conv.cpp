#include "Conv.h"

std::wstring_convert<std::codecvt_utf8<wchar_t>> _wstring_utf8_converter;

string TO_UTF8(const wstring& wide_string)
{
	return _wstring_utf8_converter.to_bytes(wide_string);
}

wstring FROM_UTF8(const string& byte_string)
{
	return _wstring_utf8_converter.from_bytes(byte_string);
}

wstring FROM_UTF8(BYTE* p_data)
{
	return _wstring_utf8_converter.from_bytes((char*) p_data);
}
