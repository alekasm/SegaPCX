#pragma once
#include <Windows.h>

struct FunctionType
{
	DWORD INITIALIZE_LAUNCHER;
	DWORD INTIALIZE_ROM;
	DWORD INITIALIZE_DDRAW;
};

struct DataType
{
	//DWORD RES_TYPE;
};

struct DetourOffsetType
{
	//static const DWORD MY_SLEEP = 0x0;
};

struct GameVersion
{
	FunctionType functions;
	DataType data;
};

const struct VersionClassics : GameVersion
{
	VersionClassics()
	{
		functions.INITIALIZE_LAUNCHER = 0x404730;
		functions.INTIALIZE_ROM = 0x403A20;
		functions.INITIALIZE_DDRAW = 0x4016F0;
	}
} version_original;

//The order of this matters
enum GameVersions { ORIGINAL };
static const GameVersion* const Versions[1] =
{
	&version_original
};