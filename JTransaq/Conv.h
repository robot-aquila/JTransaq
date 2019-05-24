#pragma once
#include <string>
#include <codecvt>
#include <Windows.h>

using namespace std;

string TO_UTF8(const wstring& wide_string);
wstring FROM_UTF8(const string& byte_string);
wstring FROM_UTF8(BYTE* p_data);
