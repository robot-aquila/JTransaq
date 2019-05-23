%module(directors="1") JTransaq
%include "std_wstring.i"

%{
#include "JTransaqHandler.h"
#include "JTransaqServer.h"
%}

%pragma(java) jniclasscode=%{
	static {
		JTransaqLoader.loadLibrary();
	}
%}

%include "JTransaqHandler.h"
%include "JTransaqServer.h"