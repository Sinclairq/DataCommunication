#pragma once
#include "stdafx.h"


int main(int argc, char* argv[]) {

	SetConsoleTitleA("communication p0c v1.0");

	if (argc < 2) {
		PRINTF("[mapper] invalid args! args are : usermode.exe processName\n");
		return -1;
	}

	if (!Comms::Setup("NtCompareSigningLevels")) {
		PRINTF("[mapper] failed to initialize communication!\n");
		return -1;
	}

	auto procID = Util::GetProcessID(StrToWstr(argv[1]).c_str());
	if (!procID) {
		PRINTF("[mapper] process not found!\n");
	}

	PRINTF("[mapper] Process ID -> %d\n", procID);

	auto base = Comms::GetBaseAddress(procID);
	if (!base) {
		PRINTF("[mapper] failed to get base address of process id -> %d\n", procID);
	}

	PRINTF("[mapper] Image Base -> 0x%x\n", base);
	
	std::getchar();
	return 0;
}