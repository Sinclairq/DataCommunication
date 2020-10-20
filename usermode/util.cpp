#pragma once
#include "util.h"

namespace Util {

	DWORD GetProcessID(LPCWSTR processName) {
		HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
		DWORD procID = NULL;

		if (handle == INVALID_HANDLE_VALUE)
			return procID;

		PROCESSENTRY32W entry = { 0 };
		entry.dwSize = sizeof(PROCESSENTRY32W);

		if (Process32FirstW(handle, &entry)) {
			if (!_wcsicmp(processName, entry.szExeFile)) {
				procID = entry.th32ProcessID;
			}
			else while (Process32NextW(handle, &entry)) {
				if (!_wcsicmp(processName, entry.szExeFile)) {
					procID = entry.th32ProcessID;
				}
			}
		}

		CloseHandle(handle);
		return procID;
	}
}