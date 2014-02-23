/*
 * LineSplitter.cpp
 *
 *  Created on: 3 dec. 2013
 *      Author: Rik
 *	  Semester: CAR
 */

#include "stdafx.h"
#include <string>
#include <sstream>
#include <stdlib.h>
#include <iostream>
#include "LineSplitter.hpp"
#include "CStringHelper.hpp"

LineSplitter::LineSplitter(const std::string& _line)
:index(0)
{
	std::stringstream eventLineStream(_line);
	//Put everything in a vector
	while (eventLineStream)
	{
		std::string s;
		if (!getline( eventLineStream, s, ',' )) break;
		paramVector.push_back(StringHelper::trim(s));
	}
}

void LineSplitter::discard()
{
	index++;
}

bool LineSplitter::pop(std::string& out)
{
	if(this->empty())
	{
		return false;
	}

	out = pop_string();
	return true;
}

const std::string& LineSplitter::pop_string()
{
	auto& ret = this->peek_string();
	this->discard();
	return ret;
}

const std::string& LineSplitter::peek_string()
{
	return this->paramVector[index];
}

const std::string& LineSplitter::peekFromIndex_string(unsigned int index)
{
	if(index < paramVector.size())
	{
		return this->paramVector[index];
	}
	else
	{
		return this->paramVector[paramVector.size()-1];
	}
}

bool LineSplitter::pop(int& out)
{
	if(this->empty())
	{
		return false;
	}

	out = pop_int();
	return true;
}

int LineSplitter::pop_int()
{
	auto ret = this->peek_int();
	this->discard();
	return ret;
}

int LineSplitter::peek_int()
{
	return atoi(this->paramVector[index].c_str());
}

int LineSplitter::peekFromIndex_int(unsigned int index)
{
	if(index < paramVector.size())
	{
		return atoi(this->paramVector[index].c_str());
	}
	else
	{
		return atoi(this->paramVector[paramVector.size()-1].c_str());
	}
}

bool LineSplitter::pop(bool& out)
{
	if(this->empty())
	{
		return false;
	}

	out = pop_bool();
	return true;
}

bool LineSplitter::pop_bool()
{
	auto ret = this->peek_int();
	this->discard();
	return ret;
}

bool LineSplitter::peek_bool()
{
	if(paramVector[index] == "1")
	{
		return true;
	}
	return false;
}

bool LineSplitter::peekFromIndex_bool(unsigned int index)
{
	if(index < paramVector.size())
	{
		if(paramVector[index] == "1")
		return true;
	}
	else
	{
		return false;
	}
	return false;
}

bool LineSplitter::pop(double out)
{
	if(this->empty())
	{
		return false;
	}

	out = pop_double();
	return true;
}

double LineSplitter::pop_double()
{
	auto ret = this->peek_double();
	this->discard();
	return ret;
}

double LineSplitter::peek_double()
{
	return atof(this->paramVector[index].c_str());
}

double LineSplitter::peekFromIndex_double(unsigned int index)
{
	if(index < paramVector.size())
	{
		return atof(this->paramVector[index].c_str());
	}
	else
	{
		return atof(this->paramVector[paramVector.size()-1].c_str());
	}
}

int LineSplitter::size() const
{
	return paramVector.size() - index;
}

bool LineSplitter::empty() const
{
	return this->size() <= 0;
}

std::vector<std::string> LineSplitter::getParamVector() const
{
	return paramVector;
}

void LineSplitter::dumpContent()
{
	std::cout << "Dumping vector" << std::endl;
	for(unsigned int i = 0; i < paramVector.size(); i++)
	{
		std::cout << paramVector[i] << std::endl;
	}
}
