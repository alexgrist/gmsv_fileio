#include "Main.h"

GarrysMod::Lua::ILuaBase* g_Lua;

void StringReplace(std::string &str, const std::string &strPattern, const std::string &strReplace)
{
	size_t found;

	found = str.find(strPattern);

	while (found != std::string::npos)
	{
		str.replace(found, strPattern.size(), strReplace);

		found = str.find(strPattern);
	};
}

void GetRelativePath(std::string &strFilePath)
{
	char currentPath[FILENAME_MAX];
	
	GetCurrentDir(currentPath, sizeof(currentPath));

	std::ostringstream strStream;

	strStream << currentPath << "/garrysmod/" << strFilePath;
	strFilePath = strStream.str();
	
	StringReplace(strFilePath, "\\", "/");
}

// A function to write a file.
int g_Write(lua_State* state)
{
	if (LUA->IsType(1, GarrysMod::Lua::Type::STRING) && LUA->IsType(2, GarrysMod::Lua::Type::STRING))
	{
		Bootil::BString strFileName = LUA->GetString(1);
		Bootil::BString strContents = LUA->GetString(2);

		GetRelativePath(strFileName);
		
		bool bStatus = Bootil::File::Write(strFileName, strContents);
		
		LUA->PushBool(bStatus);

		return 1;
	}

	LUA->PushBool(false);

	return 1;
}

// A function to read a file.
int g_Read(lua_State* state)
{
	if (LUA->IsType(1, GarrysMod::Lua::Type::STRING))
	{
		Bootil::BString strFileName = LUA->GetString(1);

		GetRelativePath(strFileName);

		Bootil::BString strFileContents;
		
		if (!Bootil::File::Read(strFileName, strFileContents))
		{
			LUA->PushBool(false);

			return 1;
		}
		
		LUA->PushString(strFileContents.c_str());

		return 1;
	}

	LUA->PushBool(false);

	return 1;
}

// A function to append to a file.
int g_Append(lua_State* state)
{
	if (LUA->IsType(1, GarrysMod::Lua::Type::STRING) && LUA->IsType(2, GarrysMod::Lua::Type::STRING))
	{
		std::string strFileName = LUA->GetString(1);
		std::string strContents = LUA->GetString(2);

		GetRelativePath(strFileName);

		std::ofstream file (strFileName.c_str(), std::ios::out | std::ios::app);

		if(file.is_open())
		{
			file << strContents;
			file.close();
			LUA->PushBool(true);
		}
		else
		{
			LUA->PushBool(false);
		}

		return 1;
	}

	LUA->PushBool(false);

	return 1;
}

// A function to delete a file or folder.
int g_Delete(lua_State* state)
{
	if (LUA->IsType(1, GarrysMod::Lua::Type::STRING))
	{
		Bootil::BString strPath = LUA->GetString(1);

		GetRelativePath(strPath);

		bool bStatus;
		
		if (Bootil::File::IsFolder(strPath))
		{
			bStatus = Bootil::File::RemoveFolder(strPath, true);
		}
		else
		{
			bStatus = Bootil::File::RemoveFile(strPath);
		}

		LUA->PushBool(bStatus);

		return 1;
	}

	LUA->PushBool(false);

	return 1;
}

// A function to make a directory.
int g_MakeDirectory(lua_State* state)
{
	if (LUA->IsType(1, GarrysMod::Lua::Type::STRING))
	{
		Bootil::BString strPath = LUA->GetString(1);
		
		GetRelativePath(strPath);
		
		bool bStatus = Bootil::File::CreateFolder(strPath);
		
		LUA->PushBool(bStatus);
		
		return 1;
	}

	LUA->PushBool(false);

	return 1;
}

// Called when the server starts.
GMOD_MODULE_OPEN()
{
	g_Lua = LUA;

	int iGlobalTable;
		LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
	iGlobalTable = LUA->ReferenceCreate();

	int iFileioTable = Lua::Table::Create();
		Lua::Table::Insert(iFileioTable, "Write", g_Write);
		Lua::Table::Insert(iFileioTable, "Read", g_Read);
		Lua::Table::Insert(iFileioTable, "Append", g_Append);
		Lua::Table::Insert(iFileioTable, "Delete", g_Delete);
		Lua::Table::Insert(iFileioTable, "MakeDirectory", g_MakeDirectory);
	Lua::Table::Add(iGlobalTable, "fileio", iFileioTable);

	LUA->ReferenceFree(iGlobalTable);

	return 0;
}

// Called when the server shuts down.
GMOD_MODULE_CLOSE()
{
	return 0;
}
