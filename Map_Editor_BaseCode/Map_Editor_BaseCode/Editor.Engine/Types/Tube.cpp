#include "stdafx.h"
#include "Tube.hpp"
#include "../../Editor.FileSystem/IniFile/LineSplitter.hpp"
#include "../../Log.hpp"

Tube::Tube(const std::string& entry)
{
	parse(entry);
}


void Tube::parse(const std::string& entry)
{
	LineSplitter split(entry);
	split.pop(startX);
	split.pop(startY);
	split.pop(direction);
	split.pop(endX);
	split.pop(endY);

	for (unsigned int i = 0; i < 94; ++i)
	{
		steps.push_back(split.peekFromIndex_int(i));
		if (split.peekFromIndex_int(i) == -1)
			break;
	}
}