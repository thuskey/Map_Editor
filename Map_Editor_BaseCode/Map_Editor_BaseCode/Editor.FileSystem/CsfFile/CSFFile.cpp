#include "stdafx.h"
#include "CSFFile.hpp"
#include "../../Config.hpp"
#include "../FileManager/FileSystem.hpp"
#include "../FileManager/BinaryReader.hpp"
#include "../../Log.hpp"

CSFFile::CSFFile(const FileProperties& props)
:csfReader(props.reader)
{
	csfReader->setOffset(props.offset);
	csfReader->setSize(props.size);
	parse();
}

void CSFFile::parse()
{
	ID = csfReader->readInt();

	if (ID != Identifier_FSC)
	{
		Log::note("This is not a valid CSF file, the game will not read it.", Log::DEBUG);
		return;
	}

	Flags1 = csfReader->readInt();
	NumLabels = csfReader->readInt();
	NumExtraValues = csfReader->readInt();
	Zero = csfReader->readInt();
	Language = csfReader->readInt();

	if (Config::language != -1 && Config::language != Language)
	{
		Log::note("This CSF file has a language other than 'ra2md.csf' has, expected '" + Log::toString(Config::language)
			+ "', got '" + Log::toString(Language) + "'.", Log::DEBUG);
		return;
	}
	if (Config::language == -1)
	{
		Config::language = Language;
	}

	for (int i = 0; i < NumLabels; ++i)
	{
		if (csfReader->readInt() == Identifier_LBL)
		{
			int stringPairs = csfReader->readInt();
			int labelLength = csfReader->readInt();
			int poop2 = csfReader->getOffset();
			std::string name = csfReader->readTextLine(labelLength, false);
			int poop3 = csfReader->getOffset();

			for (int j = 0; j < stringPairs; ++j)
			{
				int poop = csfReader->getOffset();
				unsigned int strwStr = csfReader->readUInt();
				bool bExtraValue = strwStr == Identifier_WRTS;
				if (bExtraValue || strwStr == Identifier_RTS)
				{
					int length = csfReader->readUInt();
					std::wstring value = csfReader->readWTextLine(length);
					std::string extraValue = "";

					if (bExtraValue)
					{
						unsigned int extraLength = csfReader->readUInt();
						extraValue = csfReader->readTextLine(extraLength, false);
					}

					int ValueDataLength = length << 1;
					for (int i = 0; i < ValueDataLength; ++i) 
					{
						value[i] = ~value[i];
					}

					setValue(name, value, extraValue);
				}
				else
				{
					Log::note("Found a value that's STR nor STRW, unable to tell what's going to be missing!", Log::DEBUG);
				}
			}
		}
		else
		{
			Log::note("Found an invalid label, unable to tell what's going to be missing!", Log::DEBUG);
		}
	}

	valid = true;
}

void CSFFile::setValue(const std::string& name, const std::wstring& value, const std::string& extraValue)
{
	entryList[name] = std::make_unique<CSFEntry>(value, extraValue);
	//entryList.push_back(std::make_unique<CSFEntry>(name, value, extraValue));
}

bool CSFFile::get(const std::string& name, std::wstring& value)
{
	if (entryList[name].get())
	{
		value = entryList[name].get()->Value;
		return true;
	}
		return false;
}