#pragma once
#include "comms.h"

NTSTATUS(*NtCompareSigningLevels)(PVOID, PVOID) = nullptr;

namespace Comms {

	BOOL Setup(LPCSTR routineName) {
		auto ntdll = LoadLibraryA("ntdll.dll");
		if (!ntdll) {
			PRINTF("[mapper] failed to load ntdll!\n");
			return FALSE;
		}

		auto addr = GetProcAddress(ntdll, routineName);
		if (!addr) {
			PRINTF("[mapper] failed to find routine address!\n");
			return FALSE;
		}

		*(PVOID*)&NtCompareSigningLevels = addr;
		return TRUE;
	}

	PVOID GetBaseAddress(DWORD processID) {
		Communication request = {};
		SecureZeroMemory(&request, sizeof(Communication));

		request.Request = Request::GETBASE;
		request.Reason = 0xDEADBEEF;
		request.processID = processID;
		request.Outbase = 0;

		NtCompareSigningLevels(&request, 0);
		return request.Outbase;
	}
}