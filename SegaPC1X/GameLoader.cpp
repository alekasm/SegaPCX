#include "GameLoader.h"

const std::string GameLoader::PATCH_FILE = "SPC1Patch.dat";
const std::string GameLoader::GAME_FILE = "Smash.exe";
const std::string GameLoader::PATCH_NAME = "SegaPCX";
const std::string GameLoader::GAME_NAME = "Sega Smash Pack PC";

namespace
{
	std::map<std::string, GameVersions> version_hashes =
	{
		{"563f32477cefb3283a5f88b31575dfbb", GameVersions::ORIGINAL}
	};

	std::map<GameVersions, std::string> version_description =
	{
		{GameVersions::ORIGINAL, "Version 1.0 - 1999"}
	};
}

BOOL CreateMD5Hash(const std::string filename_string, std::string& md5hash)
{
	std::wstring filename_wstring = std::wstring(filename_string.begin(), filename_string.end());
	LPCWSTR filename = filename_wstring.c_str();

	DWORD cbHash = 16;
	HCRYPTHASH hHash = 0;
	HCRYPTPROV hProv = 0;
	BYTE rgbHash[16];
	CHAR rgbDigits[] = "0123456789abcdef";
	HANDLE hFile = CreateFileW(filename, GENERIC_READ, FILE_SHARE_READ, NULL,
		OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		printf("Failed to retrieve the MD5 Hash of the program:\n");
		printf("CreateFileW has an invalid handle.\n");
		return FALSE;
	}

	CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT);
	CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash);

	BOOL bResult = FALSE;
	DWORD BUFSIZE = 4096;
	BYTE rgbFile[4096];
	DWORD cbRead = 0;
	while (bResult = ReadFile(hFile, rgbFile, BUFSIZE, &cbRead, NULL))
	{
		if (0 == cbRead)
			break;
		CryptHashData(hHash, rgbFile, cbRead, 0);
	}

	if (CryptGetHashParam(hHash, HP_HASHVAL, rgbHash, &cbHash, 0))
	{
		for (DWORD i = 0; i < cbHash; i++)
		{
			char buffer[3]; //buffer needs terminating null
			sprintf_s(buffer, 3, "%c%c", rgbDigits[rgbHash[i] >> 4], rgbDigits[rgbHash[i] & 0xf]);
			md5hash.append(buffer);
		}
		CryptDestroyHash(hHash);
		CryptReleaseContext(hProv, 0);
		CloseHandle(hFile);
		return TRUE;
	}
	else
	{
		CloseHandle(hFile);
		printf("Failed to retrieve the MD5 Hash of the program:\n");
		printf("CryptGetHashParam returned false.\n");
		return FALSE;
	}
}

BOOL GameLoader::CreatePatchedGame(const std::string game_location)
{
	std::string md5sum;
	if (!CreateMD5Hash(game_location, md5sum))
	{
		return FALSE;
	}
	printf("md5sum=%s\n", md5sum.c_str());
	std::map<std::string, GameVersions>::const_iterator hash_it;
	hash_it = version_hashes.find(md5sum);
	if (hash_it == version_hashes.end())
	{
		printf("Could not authenticate game data based on the md5sum\n");
		return FALSE;
	}

	GameVersions game_version = hash_it->second;
	printf("Detected Version: %s\n", version_description.at(game_version).c_str());

	PEINFO info;
	if (!Patcher::CreateDetourSection(game_location.c_str(), &info))
	{	
		printf("Failed to create detour section!\n");
		return FALSE;
	}

	std::vector<Instructions> instructions = GameData::GenerateData(info, game_version);
	if (!Patcher::Patch(info, instructions, game_location))
	{
		printf("Failed to create patch\n!\n");
		return FALSE;
	}

	return TRUE;
}