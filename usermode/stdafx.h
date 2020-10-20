#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>

#define PRINTF(text, ...)		(printf_s(text, ##__VA_ARGS__))
#define StrToWstr(string)		(std::wstring(string, &string[strlen(string)]))
#include "comms.h"
#include "util.h"