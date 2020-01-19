#include "GameLoader.h"

const std::string GameLoader::PATCH_FILE = "SPC1Patch.dat";
const std::string GameLoader::GAME_FILE = "Smash.exe";
const std::string GameLoader::PATCH_NAME = "SegaPCX";
const std::string GameLoader::GAME_NAME = "Sega Smash Pack PC";

namespace
{
	std::map<std::string, GameVersions> version_hashes =
	{
		{"UNKNOWN", GameVersions::ORIGINAL}
	};

	std::map<GameVersions, std::string> version_description =
	{
		{GameVersions::ORIGINAL, "Version 1.0 - 1999"}
	};

	std::string PatchDirectory;
	std::string VideoGameLocation = "";
	std::string VideoGameInstallDirectory = "";
	bool ValidInstallation = false;
	std::string patched_hash;
	int patched_version = -1;
	GameVersions game_version;
}

BOOL GameLoader::CreatePatchedGame(const std::string game_location, Parameters params)
{
	if (!std::ifstream(game_location.c_str()).good())
	{
		OutputDebugString("Failed to find the game file!\n");
		return FALSE;
	}

	PEINFO info;
	if (!Patcher::CreateDetourSection(game_location.c_str(), &info))
	{	
		OutputDebugString("Failed to create detour section!\n");
		return FALSE;
	}

	std::vector<Instructions> instructions = GameData::GenerateData(info, game_version);
	if (!Patcher::Patch(info, instructions, game_location))
	{
		OutputDebugString("Failed to create patch\n!\n");
		return FALSE;
	}

	OutputDebugString("Patch successful!\n");
	return TRUE;
}
