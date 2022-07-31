#include <Windows.h>
#include <string>
#include <iostream>
#include <conio.h>
#include  <io.h>
#include  <stdio.h>
#include  <stdlib.h>

#include "GameLoader.h"

int main(int argc, char** argv)
{
  printf("Welcome to SegaPCX - Sega Smash Pack 1 & 2 Patcher\n");
  printf("Current Version: %d\n", GameLoader::SEGAPCX_VERSION);
  printf("Written by: Aleksander Krimsky - krimsky.net\n\n");
  printf("Please create a backup of your game before patching it!\n");
  HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

  std::string f_input;
f_label:
  printf("Enter your Smash.exe/Smash2.exe location: ");
  std::getline(std::cin, f_input);
  if (f_input.find(".exe") == std::string::npos)
  {
    printf("Please use the full path to your game, including the file itself.\n");
    goto f_label;
  }
  //HANDLE hFile = CreateFileW(filename, GENERIC_READ, FILE_SHARE_READ, NULL,
//  OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
  HANDLE hFile = CreateFile(
    f_input.c_str(),
    GENERIC_READ | GENERIC_WRITE, 0, NULL,
    OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
  if (hFile == INVALID_HANDLE_VALUE)
  {
    unsigned error = GetLastError();
    switch (error)
    {
    case ERROR_ACCESS_DENIED:
      printf("Access denied, Try any of the following:\n");
      printf("1. Right-click -> \"Run-as-Administrator\"\n");
      printf("2. Move the game files to a user directory (ie Desktop)\n");
      printf("3. Ensure the game is not located on read-only/removable storage ie usb/cd/iso/zip\n");
      goto f_label;
      break;
    case ERROR_FILE_NOT_FOUND:
      printf("Unable to find the file which you entered.\n");
      goto f_label;
      break;
    default:
      printf("Unable to create a file handle. Error Code: %u\n", error);
      goto f_label;
    }
  }

  BOOL hResult = GameLoader::CreatePatchedGame(hFile, f_input);
  if (hResult)
    printf("You may now run Smash.exe, it has been successfully patched!\n");
  else
    printf("Unfortunately Smash.exe has not been succesfully patched.\n");
  printf("Press any key to exit...\n");
  _getch();
  return 0;
}