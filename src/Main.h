#ifndef _MAIN_HEADER_
#define _MAIN_HEADER_

#include <iostream>
#include <string>

#ifndef _WIN32
	#include <sys/stat.h>
	#include <sys/types.h>
	#include <unistd.h>
	#define GetCurrentDir getcwd
#else
	#include <direct.h>
	#define GetCurrentDir _getcwd
#endif

#include <GarrysMod/Lua/Interface.h>
#include <Bootil/Bootil.h>
#include "Lua.h"

extern GarrysMod::Lua::ILuaBase* g_Lua;

#endif
