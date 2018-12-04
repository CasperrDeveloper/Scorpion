#pragma once
#include <Windows.h>
#define ASLR(Address) (Address - 0x400000 + reinterpret_cast<unsigned int>(GetModuleHandle(nullptr)))

	bool Compare(const char* pData, const char* bMask, const char* szMask);
	DWORD Scan(const char* Vftable);