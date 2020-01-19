#include <Windows.h>
#include <string>
#include <Windowsx.h> //Button_SetCheck macro
#include <CommCtrl.h> //CommCtrl includes sliders
#include <iostream>
#include "GameLoader.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);
	Parameters params;
	params.fullscreen = false;
	GameLoader::CreatePatchedGame(GameLoader::GAME_FILE, params);
}