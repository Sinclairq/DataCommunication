#pragma once
#include <ntifs.h>
#include <ntddk.h>
#include <windef.h>
#include <ntimage.h>

#include "structs.h"

#define RVA(addr, size)			((PBYTE)(addr + *(DWORD*)(addr + ((size) - 4)) + size))
#define printf(text, ...)		(DbgPrintEx(0, 0, text, ##__VA_ARGS__))
#define WINVER_2004				(19041)
#define COMMUNICATION_KEY		(0xDEADBEEF)

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

extern "C" NTSTATUS ZwQuerySystemInformation(SYSTEM_INFORMATION_CLASS systemInformationClass, PVOID systemInformation, ULONG systemInformationLength, PULONG returnLength);
extern "C" NTSTATUS NTAPI MmCopyVirtualMemory(PEPROCESS SourceProcess, PVOID SourceAddress, PEPROCESS TargetProcess, PVOID TargetAddress, SIZE_T BufferSize, KPROCESSOR_MODE PreviousMode, PSIZE_T ReturnSize);
extern "C" NTKERNELAPI PVOID PsGetProcessSectionBaseAddress(PEPROCESS Process);

#include "memory.h"
#include "util.h"
#include "core.h"