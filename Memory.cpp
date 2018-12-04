#include "Memory.h"

	bool Compare(const char* pData, const char* bMask, const char* szMask) {
		while (*szMask) {
			if (*szMask != '?') {
				if (*pData != *bMask) return 0;
			}
			++szMask, ++pData, ++bMask;
		}
		return 1;
	}

	DWORD Scan(const char* Vftable) {
		MEMORY_BASIC_INFORMATION MBI;
		SYSTEM_INFO SI;
		GetSystemInfo(&SI);
		DWORD Start = reinterpret_cast<DWORD>(SI.lpMinimumApplicationAddress);
		DWORD End = reinterpret_cast<DWORD>(SI.lpMaximumApplicationAddress);
		while (Start < End && VirtualQuery(reinterpret_cast<LPVOID>(Start), &MBI, sizeof(MBI))) {
			if ((MBI.Protect & PAGE_READWRITE) && !(MBI.Protect & PAGE_GUARD)) {
				for (unsigned int Data = reinterpret_cast<DWORD>((MBI.BaseAddress)); Data - reinterpret_cast<DWORD>(MBI.BaseAddress) < MBI.RegionSize; ++Data) {
					if (Compare(reinterpret_cast<const char*>(Data), Vftable, "xxxx"))
						return Data;
				}
			}
			Start += MBI.RegionSize;
		}
		return 0;
	}