#include <Windows.h>
#include <string>
#include <Windowsx.h> //Button_SetCheck macro`
#include <CommCtrl.h> //CommCtrl includes sliders
#include <iostream>
#include "SegaPCX.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);
}