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

const struct PC1Original : GameVersion
{
  PC1Original()
  {
    functions.INITIALIZE_LAUNCHER = 0x404730;
    functions.INTIALIZE_ROM = 0x403A20;
    functions.INITIALIZE_DDRAW = 0x4016F0;
  }
} version_pc1_original;

const struct PC2Original : GameVersion
{
  PC2Original()
  {
    functions.INITIALIZE_LAUNCHER = 0x404A50;
    functions.INTIALIZE_ROM = 0x403A30;
    //functions.INITIALIZE_DDRAW = 0x4016F0;
  }
} version_pc2_original;

//The order of this matters
enum GameVersions { PC1_ORIGINAL, PC2_ORIGINAL };
static const GameVersion* const Versions[2] =
{
  &version_pc1_original, &version_pc2_original
};