#pragma once
#include <Windows.h>
#include <vector>
#include <string>
#include "Patcher.h"
#include "GameVersion.h"


class GameData
{
public:
	static std::vector<Instructions> GenerateData(PEINFO, GameVersions);
private:
	static void Patch_InitializeLauncher(DetourMaster*, GameVersions);
	static void Patch_InitializeROM(DetourMaster*, GameVersions);
	static void Patch_InitializeDDRAW(DetourMaster*, GameVersions);
};