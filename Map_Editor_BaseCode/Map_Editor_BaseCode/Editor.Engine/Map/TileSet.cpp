#include "stdafx.h"
#include "TileSet.hpp"
#include <iostream>
#include <sstream>
#include "../../Editor.FileSystem/FileManager/Managers/TMPManager.hpp"
/*
	NOTE: Not sure where to place this yet, it's just working ahead really...
*/

TileSet::TileSet(int _ID, INISection* _section)
:ID(_ID), section(_section)
{
	std::cout << "---------------------------------------------\nParsing tileset with ID: " << ID << " Memory: " << section << std::endl;
	parse();
	collectTiles();
}


TileSet::~TileSet()
{
}

void TileSet::parse()
{
	if (section)
	{
		FileName = section->readStringValue("FileName", "");
		SetName = section->readStringValue("SetName", "");
		TilesInSet = section->readIntValue("TilesInSet", 0);
		MarbleMadnessTile = section->readIntValue("MarbleMadness", -1);
		NonMarbleMadnessTile = section->readIntValue("NonMarbleMadness", -1);
		TileAnimIndex = section->readIntValue("TileAnimIndex", -1);
		TileXOffset = section->readIntValue("TileXOffset", 0);
		TileYOffset = section->readIntValue("TileYOffset", 0);
		TileAttachesTo = section->readIntValue("TileAttachesTo", 0);
		TileZAdjust = section->readIntValue("TileZAdjust", 0);
		Morphable = section->readBoolValue("Morphable", false);
		ShadowCaster = section->readBoolValue("ShadowCaster", false);
		AllowToPlace = section->readBoolValue("AllowToPlace", true);
		AllowTiberium = section->readBoolValue("AllowTiberium", false);
	}
	else
		std::cout << "Tileset with ID " << ID << " does not exist!" << std::endl;	
}

/*
[23:51:44] <Starkku> It serves different purpose in bridges
[23:51:55] <Starkku> It works for everything else too but it does different thing
[23:51:55] <@RP> Okay, but it works for anything else
[23:52:42] <@RP> Okay, for now it's just reading them so I'll create a function that looks for fileName + X (0 <= X <= 99) and a-z
[23:52:51] <Starkku> alright
[23:54:07] <Starkku> For tiles other than bridgeheads the lettered ones are basically variants that game randomly substitutes the non-lettered one with
[23:54:13] <Starkku> As far as I know
[23:54:41] <Starkku> And it only goes up to g as far as I know
[23:54:50] <Starkku> Rest of the letters won't work
[23:56:32] <Starkku> Well combined with the non-lettered one
[23:56:35] <Starkku> That makes 8 variants
*/
void TileSet::collectTiles()
{
	std::stringstream number;
	for (unsigned int i = 1; i <= TilesInSet; ++i)
	{
		if (i < 10)
			number << "0";
		
		number << i;

		if (TMPManager::getManager()->get(FileName + number.str() + ".TEM")) //lol, hardcoding for testing
		{
			std::cout << "Now parsing: " << FileName << number.str() << ".TEM" << std::endl;
			//Search for a-b-c-d-e-f-g
			for (unsigned int i = 65; i < 72; ++i) // ASCII 65 -> A, 72 -> H (loop until 71, G)
			{
				
				if (!TMPManager::getManager()->get(FileName + number.str() + (char)i + ".TEM"))
					break;
				else
					std::cout << "Now parsing: " << FileName << number.str() << (char)i << ".TEM" << std::endl;
			}
		}
		else
			break; 

		number.str(std::string());
	}
	std::cout << "Tiles collected for set: " << SetName << " (" << FileName << ")" << std::endl;
}