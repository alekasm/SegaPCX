#pragma once
#include <Windows.h>
#include "Shlwapi.h"
#include "shellapi.h"
#include <fstream>
#include <vector>
#include <wincrypt.h>
#include <Windows.h>
#include <algorithm>
#include <regex>
#include "Patcher.h"
//#include "FileVersion.h"
//#include "Message.h"
#include "GameData.h"

#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "Shell32.lib")
#pragma comment(lib, "Kernel32.lib")
#pragma comment(lib, "Advapi32.lib" )

struct Parameters
{
	bool fullscreen;
};

class SCXLoader
{
public:
	static const unsigned int SEGAPCX_VERSION = 0;
};