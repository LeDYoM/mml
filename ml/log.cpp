#include "include/log.h"
#include "logPriv.h"

#include <string>
#if defined(_MSC_VER) || defined(__BORLANDC__)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#ifndef OUTPUT_TO_COMPILER
//			#define OutputDebugString(x)
#endif
#endif

void logOutput(const std::string &str)
{
	std::cout << str;
#if defined(_MSC_VER) || defined(__BORLANDC__)
	OutputDebugString(str.c_str());
#endif
}
