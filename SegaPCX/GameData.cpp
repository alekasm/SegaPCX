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
  //Sega PC1/PC2 both check at offset C3, how convenient.
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
  DWORD drive_check;
  DWORD jmp_addr;

  switch (version)
  {
  case GameVersions::PC1_ORIGINAL:
  {
    drive_check = function_entry + 0x1C7;
    jmp_addr = 0x403C0F;
  }
  break;
  case GameVersions::PC2_ORIGINAL:
  {
    drive_check = function_entry + 0x1CA;
    jmp_addr = 0x403C1F;
  }
  break;
  }

  Instructions instructions(drive_check);
  instructions.jmp(jmp_addr, FALSE);

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
