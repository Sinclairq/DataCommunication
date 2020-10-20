#pragma once
#include "stdafx.h"

PVOID(__fastcall* NtCompareSigningLevelsOrig)(PVOID, PVOID);

PVOID NtCompareSigningLevelsHook(Communication* arg0, PBYTE arg1) {

	/*
	* Simple check to make sure the call was from usermode.
	*/
	if (ExGetPreviousMode() != UserMode) {
		return NtCompareSigningLevelsOrig(arg0, arg1);
	}

	Communication comms = {};
	if(!Core::ReadVirtualMemory(&comms, arg0, sizeof(Communication)) || comms.Reason != COMMUNICATION_KEY) {
		return NtCompareSigningLevelsOrig(arg0, arg1);
	}

	printf("[mapper] called w reason -> 0x%x", comms.Reason);
	
	auto args = (Communication*)arg0;

	switch (comms.Request) {

		case Request::GETBASE: {

			if (comms.processID) {
				PEPROCESS process = { 0 };
				PsLookupProcessByProcessId((HANDLE)args->processID, &process);
				args->Outbase = PsGetProcessSectionBaseAddress(process);
				ObDereferenceObject(process);
			}
			break;
		}
	}

	return NULL;
}

NTSTATUS DriverEntry(PDRIVER_OBJECT driver, PUNICODE_STRING regPath) {

	RTL_OSVERSIONINFOW info = { 0 };

	if (!info.dwBuildNumber) {
		RtlGetVersion(&info);
	}

	printf("[mapper] os version -> %d", info.dwBuildNumber);

	auto base = Core::GetModuleBase(0);

	if (!base) {
		return STATUS_FAILED_DRIVER_ENTRY;
	}

	printf("[mapper] ntoskrnl.exe -> 0x%x", base);

	auto addr = Util::FindPattern(base, 
				"\x4C\x8B\x05\x00\x00\x00\x00\x33\xC0\x4D\x85\xC0\x74\x08\x49\x8B\xC0\xE8\x00\x00\x00\x00\xF7\xD8",
				"xxx????xxxxxxxxxxx????xx");

	if (!addr) {
		printf("Unable to find singature!");
		return STATUS_FAILED_DRIVER_ENTRY;
	}

	addr = RVA(addr, 7);
	printf("[mapper] addr -> 0x%x", addr);

	*(PVOID*)&NtCompareSigningLevelsOrig =
			InterlockedExchangePointer(
				(volatile PVOID*)addr,
				NtCompareSigningLevelsHook
			);

	printf("[mapper] swapped pointer -> 0x%x to 0x%x", addr, &NtCompareSigningLevelsHook);

	return STATUS_SUCCESS;
}
