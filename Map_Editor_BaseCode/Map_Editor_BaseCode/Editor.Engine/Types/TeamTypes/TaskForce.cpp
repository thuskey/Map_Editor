#include "stdafx.h"
#include "TaskForce.hpp"
#include "../../../Editor.FileSystem/IniFile/INIFile.hpp"
#include "../../../Editor.FileSystem/IniFile/INISection.hpp"
#include "../../../Log.hpp"

TaskForce::TaskForce(const std::string& id)
:ID(id)
{

}

void TaskForce::parse(INIFile* file)
{
	INISection* section = file->getSection(ID);

	section->readStringValue("Name", Name);
	section->readIntValue("Group", Group);

	Log::note("Types of TaskForce aren't parsed yet!");
	for (unsigned int i = 0; i < 5; ++i)
	{
		if (!section->checkKeyExistance(Log::toString(i)))
			break; // Stop looking if an index is missing
	}
}
