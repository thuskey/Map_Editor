#include "stdafx.h"
#include "Side.hpp"
#include "../../Log.hpp"

Side::Side()
{

}

void Side::loadRules(INIFile* file)
{
	INISection* rulesSection = file->getSection("Sides");
	if (!rulesSection) return;

	for (auto& it : *rulesSection)
	{
		//Log::note("Adding Side: " + section.first, Log::DEBUG);
		sideList.push_back(it);
	}
}
