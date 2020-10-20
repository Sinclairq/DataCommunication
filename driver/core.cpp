#pragma once
#include "core.h"

namespace Core {

	BOOL ReadVirtualMemory(PVOID dest, PVOID src, size_t size) {

		size_t pSize;
		if (NT_SUCCESS(MmCopyVirtualMemory(PsGetCurrentProcess(), src, 
			PsGetCurrentProcess(), dest, size, KernelMode, &pSize)
			) && size == pSize) {
			return TRUE;
		}

		return FALSE;
	}

	BOOL WriteVirtualMemory(PVOID dest, PVOID src, size_t size) {

		if (NT_SUCCESS(MmCopyVirtualMemory(PsGetCurrentProcess(), dest,
			PsGetCurrentProcess(), src, size, KernelMode, &size))) {
			return TRUE;
		}

		return FALSE;
	}

	PVOID GetModuleBase(LPCSTR moduleName) {

		PVOID moduleBase = NULL;
		ULONG info = 0;
		NTSTATUS status = ZwQuerySystemInformation(SystemModuleInformation, 0, info, &info);

		if (!info) {
			return moduleBase;
		}

		PRTL_PROCESS_MODULES modules = (PRTL_PROCESS_MODULES)ExAllocatePoolWithTag(NonPagedPool, info, 'HEIL');

		status = ZwQuerySystemInformation(SystemModuleInformation, modules, info, &info);

		if (!NT_SUCCESS(status)) {
			return moduleBase;
		}

		PRTL_PROCESS_MODULE_INFORMATION module = modules->Modules;


		if (modules->NumberOfModules > 0) {

			if (!moduleName) {
				moduleBase = modules->Modules[0].ImageBase;
			}
			else {

				for (auto i = 0; i < modules->NumberOfModules; i++) {

					if (!strcmp((CHAR*)module[i].FullPathName, moduleName)) {
						moduleBase = module[i].ImageBase;
					}
				}
			}
		}

		if (modules) {
			ExFreePoolWithTag(modules, 'HEIL');
		}

		return moduleBase;
	}

}