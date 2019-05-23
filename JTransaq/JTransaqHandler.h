#pragma once
#include <string>
#include "TransaqHandler.h"

using namespace std;

class JTransaqHandler : public CTransaqHandler
{
public:
	JTransaqHandler() : CTransaqHandler() { }
	virtual bool Handle(const wstring& data) override { return false; }
	virtual ~JTransaqHandler() { }
};

