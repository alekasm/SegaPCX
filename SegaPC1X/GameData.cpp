#include "GameData.h"
#include <ddraw.h>

std::vector<Instructions> GameData::GenerateData(PEINFO info, GameVersions version)
{	
	DetourMaster* master = new DetourMaster(info);
	Patch_InitializeLauncher(master, version);
	Patch_InitializeROM(master, version);
	//Patch_InitializeDDRAW(master, version);
	std::vector<Instructions> ret_ins(master->instructions);
	delete master;
	return ret_ins;
}

/*
	Patches the initial CD-ROM check which prompts user to insert the CD-ROM.
*/
void GameData::Patch_InitializeLauncher(DetourMaster* master, GameVersions version)
{
	DWORD function_entry = Versions[version]->functions.INITIALIZE_LAUNCHER;
	Instructions instructions(function_entry + 0xC3);
	instructions.nop(5); //call smash.401060
	instructions.nop(2); //test eax, eax
	instructions.nop(6); //je smash.404984
	size_t is_size = instructions.GetInstructions().size();
	printf("[Initialize Launcher] Generated a total of %d bytes\n", is_size);
	master->instructions.push_back(instructions);	
}

/*
	Patches the second CD-ROM check which will delete the game ROMs if they are 
	not being loaded from a CD. Uses GetDriveTypeA, so realistically the ROMs
	could have been put on any CD-ROM and pass this check.
*/
void GameData::Patch_InitializeROM(DetourMaster* master, GameVersions version)
{
	DWORD function_entry = Versions[version]->functions.INTIALIZE_ROM;
	Instructions instructions(function_entry + 0x1C7);

	instructions.nop(5); //push smash.4DE690 (lpRootPathName)
	instructions.nop(6); //call GetDriveTypeA
	instructions.nop(3); //cmp eax, 5 (DRIVE_CDROM)
	instructions.nop(2); //je smash.403C0F
	instructions.nop(4); //lea eax, [esp+28]
	instructions.nop(1); //push eax
	instructions.nop(5); //call smash.436D8A
	instructions.nop(5); //mov ebp, 1
	instructions.nop(3); //add esp, 4
	instructions.nop(4); //mov [esp+18], ebp
	instructions.nop(2); //jmp smash.403C14
	
	size_t is_size = instructions.GetInstructions().size();
	printf("[Initialize ROM] Generated a total of %d bytes\n", is_size);
	master->instructions.push_back(instructions);
}

/*
	Skips setting the Display Mode in Direct Draw
*/
void GameData::Patch_InitializeDDRAW(DetourMaster* master, GameVersions version)
{
	DWORD function_entry = Versions[version]->functions.INITIALIZE_DDRAW;
	Instructions instructions(function_entry + 0x13C);
}
