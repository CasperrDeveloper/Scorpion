#include <Windows.h>
#include <string>
#include "Convert.h"
#include "Serializer.h"
#define ASLR(Address) (Address - 0x400000 + reinterpret_cast<unsigned int>(GetModuleHandle(nullptr)))

extern "C" {
#include "..\Lua\lua.h"
#include "..\Lua\lualib.h"
#include "..\Lua\lauxlib.h"
#include "..\Lua\lobject.h"
#include "..\Lua\lstate.h"
}

typedef void(__cdecl* Deserialize_Definition)(unsigned int, const std::string&, const char*, unsigned int);
Deserialize_Definition Deserialize = reinterpret_cast<Deserialize_Definition>(ASLR(0x5F9470));

void ExecuteScript(unsigned int rL, const char* Script) {
	lua_State* L = lua_open();
	LuaSerializer Serializer;
	RbxOpEncoder Encoder;

	std::string Buff;
	Buff = "spawn(function() local script = Instance.new'LocalScript'\r\n";
	Buff += Script;
	Buff += "\r\nend)";

	*reinterpret_cast<unsigned char*>(rL - 0x20) ^= (7 ^ (unsigned __int8)*reinterpret_cast<DWORD*>(rL - 0x20)) & 0x1F;

	std::string Code = Serializer.serialize(L, Buff, Encoder, 1);
	Deserialize(rL, Code, "Scorpion", 1);
	lua_close(L);
	free(&Code);
}
