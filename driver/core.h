#pragma once
#include "stdafx.h"

namespace Core {
	BOOL ReadVirtualMemory(PVOID dest, PVOID src, size_t size);
	BOOL WriteVirtualMemory(PVOID dest, PVOID src, size_t size);
	PVOID GetModuleBase(LPCSTR moduleName);
}