#pragma once
#include "stdafx.h"

enum Request {
	GETBASE = 0,
	READPROCESSMEMORY = 1,
	WRITEPROCESSMEMORY = 2,
	OPENHANDLE = 3,
};

struct Communication {

	Request Request;
	DWORD processID;
	DWORD Reason; // must be 0xDEADBEEF....
	PVOID Outbase; // output image base for process.

	/*
	* READ/WRITE PROCESS MEMORY.
	*/
	PVOID Address;
	PVOID result;
	size_t size;
};

namespace Comms {
	BOOL Setup(LPCSTR routineName);
	PVOID GetBaseAddress(DWORD processID);
}