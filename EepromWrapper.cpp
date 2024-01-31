#include "EepromWrapper.h"
#include "Arduino.h"
int EepromWrapper::nextFreeAdress=0;
int EepromWrapper::getAdressFor(int bytes){
	int curAdress=nextFreeAdress;
	nextFreeAdress+=bytes;
	return(curAdress);

}
#ifdef __AVR__
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

#ifdef ESP32
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
