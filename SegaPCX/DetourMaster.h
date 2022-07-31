#pragma once
#include "Instructions.h"
#include "PEINFO.h"

struct DetourMaster
{
	DWORD current_location;
	DWORD base_location;
	PEINFO info;

	DetourMaster(PEINFO info)
	{
		this->info = info;
		current_location = info.GetDetourVirtualAddress();
		base_location = current_location;
		current_location += 0x128; //Reserve space for variables
	}

	DWORD GetNextDetour()
	{
		return current_location;
	}

	void SetLastDetourSize(size_t size)
	{
		//Technically this includes instructions outside of the detour but who cares
		current_location += (size % 4) + size;
	}
	std::vector<Instructions> instructions;
};