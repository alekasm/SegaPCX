#include <Windows.h>
#include <string>
#include <iostream>
#include <conio.h>
#include "GameLoader.h"

int main(int argc, char** argv)
{
	printf("Welcome to SegaPC1X - Sega Smash Pack 1 Patcher\n");
	printf("Written by Aleksander Krimsky, SegaPC1X Version %d\n\n", GameLoader::SEGAPCX_VERSION);
	printf("Please create a backup of Smash.exe before patching it!\n");
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);
	std::string f_input;
f_label:
	printf("Please enter your Smash.exe location: ");
	std::getline(std::cin, f_input);
	if (f_input.find(GameLoader::GAME_FILE) == std::string::npos)
	{
		printf("The path you entered does not contain %s\n", GameLoader::GAME_FILE.c_str());
		goto f_label;
	}
	if (!std::ifstream(f_input.c_str()).good())
	{
		printf("Unable to find the file which you entered.\n");
		goto f_label;
	}

	BOOL hResult = GameLoader::CreatePatchedGame(f_input);
	if (hResult)
		printf("You may now run Smash.exe, it has been successfully patched!\n");
	else
		printf("Unfortunately Smash.exe has not been succesfully patched.\n");
	_getch();
}