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

%feature("director") JTransaqHandler; 
%typemap(throws, throws="Exception") std::exception, exception {
    jclass exClass = jenv->FindClass("java/lang/Exception");
    if (exClass)
        jenv->ThrowNew(exClass, $1.what());
    return $null;
}

%include "JTransaqHandler.h"
%include "JTransaqServer.h"