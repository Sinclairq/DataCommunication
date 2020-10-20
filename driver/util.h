#pragma once
#include "stdafx.h"

namespace Util {

	PIMAGE_NT_HEADERS getHeader(PVOID module);
	PBYTE FindPattern(PVOID base, LPCSTR pattern, LPCSTR mask);
}