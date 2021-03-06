/*
 * MixFile.hpp
 *
 *  Created on: 12 feb. 2014
 *      Author: Rik
 *	  Semester: CAR
 */

#include <string>
#include <vector>


#ifndef MIXFILE_HPP_
#define MIXFILE_HPP_

class BinaryReader;

class MixFile {
public:
	struct t_mix_header
	{
		__int16 files = 0;
		__int32 size = 0;
	} header;

	struct t_mix_index_header
	{
		__int32 id;
		__int32 offset;
		__int32 size;
	};

	MixFile(const std::string& _mixName, MixFile* _parent = nullptr, int fileID = 0);
	MixFile(BinaryReader* _mixReader, int offset = 0, int size = 0, const std::string& _mixName = "");

	/*
		Handles the header of the MIX file
	*/
	void handleHeader();

	/*
		Checks whether a file exists in the MIX
		@param fileID The ID of the file to look for
	*/
	bool checkFileExistance(__int32 fileID);
	/*
		@param fileID The ID of the file to look for
		@return The offset from the file
	*/
	int getAFileOffset(__int32 fileID);

	int getAFileSize(__int32 fileID);

	/*
		Gets a file from the MIX and returns it in a byte vector
		@param fileID The ID of the file to look for
		@return The file in bytes
	*/
	std::vector<byte> getFile(__int32 fileID);
	/*
		This is used to determine what mixReader should be used
		If it is a parent mix (present in the root), its own reader will be used
		If it is a child mix (present in a parent mix), the reader from the parent will be used
	*/
	void determineMixReader();
	/*
		Testcode - Dumps the entire index of the MIX file
	*/
	void dumpIndex();
	/*
		Reads the header as a Tiberian Dawn header, without any encryption
		Part of XCC code
		@param fileCount The amount of files in the MIX
	*/
	void readTDHeader(unsigned short fileCount);
	/*
		Reads the header as a Red Alert header, with possible encryption
		If no encryption is used, the header is read out as a TD header
		Part of XCC code
	*/
	void readRAHeader();

	/*
		Finds the upper most parent from the MIX and returns it
		@return The name of the parent's MIX
	*/
	std::string getUpperParentName();

	BinaryReader* getUpperParentMix();

	std::vector<t_mix_index_header> mixIndex;
	std::string mixName = "";
	/* if parent */
	//BinaryReader mixReader;
	/* if child */
	BinaryReader* mixReader;
	MixFile* parent = nullptr;
	int startingOffset = 0;
	int bodyOffset = 0;
};

#endif /* MIXFILE_HPP_ */
