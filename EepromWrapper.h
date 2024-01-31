#pragma once

#ifdef __AVR__

#define ARDUPAR_CONST_CHAR __FlashStringHelper
#else
#define ARDUPAR_CONST_CHAR char
#endif
class EepromWrapper{
	public:
	static int getAdressFor(int bytes);	///< returns an adress and reserves the requested number of bytes
	static void read_bytes(void* dst, int address, int nBytes); ///< read raw data from permanent storage
	static void write_bytes(void* dst, int address, int nBytes); ///< write raw data to permanent storage

	protected:
	static int nextFreeAdress;	///< points to the next free byte
};