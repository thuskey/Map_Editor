/*
 * BinaryReader.hpp
 *
 *  Created on: 12 feb. 2014
 *      Author: Rik
 *	  Semester: CAR
 */

#ifndef BINARYREADER_HPP_
#define BINARYREADER_HPP_

//#include "../Handlers/MixFileHandler.hpp"
#include <fstream>
#include <vector>
#include <string>

class BinaryReader {
public:
	BinaryReader(const std::string& fileName);
	BinaryReader(int _startingOffset);
	~BinaryReader();
	/*
		Sets the offset from the filestream to the specified value
		@param _offset The offset that will be set
	*/
	void setOffset(int _offset);
	/*
		Testcode
		Sets the offset from the filestream to the specified value + current position in the file
		Used mainly for MIX files inside another MIX
		@param _offset The offset that will be set
	*/
	void setStartingOffset(int _offset);
	/*
		Reads and returns the current offset
		@return The current offset from the file
	*/
	int getOffset();
	/*
		Restores the offset to the value before setOffset() was called
	*/
	void restoreOffset();
	/*
		Sets the offset to position 0
	*/
	void resetOffset();

	//Integers
	/*
		Reads an unsigned integer from the file
	*/
	unsigned int readUInt(bool isBigEndian = false);
	/*
		Reads a signed integer from the file
	*/
	int readInt(bool isBigEndian = false);
	//Shorts
	/*
		Reads an unsigned short from the file
	*/
	unsigned short readUShort(bool isBigEndian = false);
	/*
		Reads a signed short from the file
	*/
	short readShort(bool isBigEndian = false);
	//Bytes
	/*
		Reads a single byte from the file
	*/
	byte readByte();
	/*
		Kind of obsolete, skips the amount of bytes given
		@param amount The amount of bytes to skip
	*/
	void discardBytes(unsigned int amount);
	/*
		Reads a series of bytes from the current position of the filestream
		@param amountOfBytes The amount of bytes to read out
	*/
	std::vector<byte> readByteBlock(unsigned int amountOfBytes);
	/*
		Reads a series of bytes from the specified offset
		@param offset The offset to start reading from
		@param amountOfBytes The amount of bytes to read out
	*/
	std::vector<byte> readByteBlockFromOffset(__int32 offset, unsigned int amountOfBytes);
	//Endian conversion
	/*
		Trivial, these functions convert values from little to big endian and vice versa
	*/
	unsigned short littleToBigUShort(unsigned short toSwap);
	short littleToBigShort(short toSwap);
	unsigned int littleToBigUInt(unsigned int toSwap);
	int littleToBigInt(int toSwap);

private:
	bool isOpened = false;
	std::string fullFileName;
	int startingOffset = 0;
	int previousOffset = 0;
	std::ifstream fileStream;

};

#endif /* BINARYREADER_HPP_ */
