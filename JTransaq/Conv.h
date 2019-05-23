#pragma once
#include <string>
#include <codecvt>

using namespace std;

string TO_UTF8(const wstring& wide_string);
wstring FROM_UTF8(const string& byte_string);
