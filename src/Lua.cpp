#include "Lua.h"

int Lua::Table::Create()
{
	int iTableReference;
	g_Lua->CreateTable();

	iTableReference = g_Lua->ReferenceCreate();

	return iTableReference;
}

void Lua::Table::Add(int iTableReference, const std::string &key, int iTable)
{
	g_Lua->ReferencePush(iTableReference);
		g_Lua->PushString(key.c_str());
		g_Lua->ReferencePush(iTable);
	g_Lua->SetTable(-3);

	g_Lua->ReferenceFree(iTable);
}

void Lua::Table::Insert(int iTableReference, const std::string &key, GarrysMod::Lua::CFunc value)
{
	g_Lua->ReferencePush(iTableReference);
		g_Lua->PushString(key.c_str());
		g_Lua->PushCFunction(value);
	g_Lua->SetTable(-3);
}

void Lua::Table::Insert(int iTableReference, const std::string &key, int value)
{
	g_Lua->ReferencePush(iTableReference);
		g_Lua->PushString(key.c_str());
		g_Lua->PushNumber(value);
	g_Lua->SetTable(-3);
}

void Lua::Table::Insert(int iTableReference, const std::string &key, std::string value)
{
	g_Lua->ReferencePush(iTableReference);
		g_Lua->PushString(key.c_str());
		g_Lua->PushString(value.c_str());
	g_Lua->SetTable(-3);
}

void Lua::Table::Insert(int iTableReference, int key, std::string value)
{
	g_Lua->ReferencePush(iTableReference);
		g_Lua->PushNumber(key);
		g_Lua->PushString(value.c_str());
	g_Lua->SetTable(-3);
}
