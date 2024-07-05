#include "EepromWrapper.h"
#include "Arduino.h"
#ifdef __XTENSA__
#include <EEPROM.h>
#endif
int EepromWrapper::nextFreeAdress=0;
bool EepromWrapper::isInitialized=false;
int EepromWrapper::getAdressFor(int bytes){
	int curAdress=nextFreeAdress;
	nextFreeAdress+=bytes;
	return(curAdress);

}
#if defined(__AVR__)
#include <avr/eeprom.h>
///< read raw data from permanent storage
void EepromWrapper::read_bytes(void* data, int address, int nBytes){
		eeprom_read_block(data,(void *) address,nBytes); 
}
///< write raw data to permanent storage
void EepromWrapper::write_bytes(void* data, int address, int nBytes){
      eeprom_write_block(data,(void *) address,nBytes); 
}
#endif

#ifdef __XTENSA__

///< read raw data from permanent storage
void EepromWrapper::read_bytes(void* data, int address, int nBytes){
	if(!EepromWrapper::isInitialized){
		EEPROM.begin(1024);
		EepromWrapper::isInitialized=true;
	}
	EEPROM.readBytes(address,data,nBytes); 

}
///< write raw data to permanent storage
void EepromWrapper::write_bytes(void* data, int address, int nBytes){
	if(!EepromWrapper::isInitialized){
		EEPROM.begin(1024);
		EepromWrapper::isInitialized=true;
	}
	EEPROM.writeBytes(address,data,nBytes); 
		EEPROM.commit();
}
#endif
