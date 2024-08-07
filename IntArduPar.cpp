#include "IntArduPar.h"

void IntArduPar::setup(
    const ARDUPAR_CONST_CHAR *cmdString,
    int minValue,
    int maxValue,
    boolean isPersistent , ///< should the parameter value be initialized from eeprom on startup?
    int *valuePointer ,       ///< the setting can modify an arbitrary location im memory if you give it here.
    int fixedEEPROMAdress    ///< if you want a specific fixed adress, specify it here
)
{
    this->cmdString = cmdString;
    cmdStringLength = strlen_P((const char PROGMEM *)cmdString);

    if (valuePointer == 0)
        valuePointer = &this->value;
    this->valuePointer = valuePointer;
    this->minValue = minValue;
    this->maxValue = maxValue;
    ArduParCollection::registerInstance(this);

    if (isPersistent)
    {

        if (fixedEEPROMAdress == -1)
        {
            TRACE((F("Getting EEPROM. Adress: ")));
            fixedEEPROMAdress = EepromWrapper::getAdressFor(sizeof(int));
        };
        this->eepromAdress = fixedEEPROMAdress;
        TRACE((F("Init from EEPROM. Adress: ")));
        TRACE((int)(eepromAdress));
        EepromWrapper::read_bytes(valuePointer, eepromAdress, sizeof(int));
        TRACE((F(" value:")));
        TRACELN((*valuePointer));
    }
    else
    {
        this->eepromAdress = -1; // used to signal non-persistence to other methods
    };
};

/// set the attached integer parameter from a string that was received
void IntArduPar::parseParameterString(char *data)
{
    setValue(atoi(data));
};

// set the value and rpint some debug info
void IntArduPar::setValue(int newValue)
{
    valueReceived = true; // flag: I got new data!
    newValue = constrain(newValue, minValue, maxValue);
    TRACE((F("Setting ")));
    TRACE((this->cmdString));
    TRACE((F(" to ")));
    TRACE((newValue));
    TRACE((F("\n")));
    *valuePointer = newValue;
    // save the new value
    if (eepromAdress >= 0)
    {
        TRACE((F("Writing EEProm adress")));
        TRACE(eepromAdress);
        TRACE((F("\n")));
        EepromWrapper::write_bytes(valuePointer, eepromAdress, sizeof(int));
    }
};

void IntArduPar::dumpParameterInfo(Stream *out)
{
    out->print(F("int\t"));
    out->print(this->cmdString);
    out->print(F("\t"));
    out->print(this->cmdString);
    out->print(F("\t"));
    out->print(*valuePointer);
    out->print(F("\t"));
    out->print(minValue);
    out->print(F("\t"));
    out->print(maxValue);
    out->print(F("\n"));
}
#ifdef ARDUPAR_USE_OSC
void IntArduPar::parseOscMessage(OSCMessage& message){
    if(!isOscMessageForMe(message))return;
    float newValue;
    if(message.getType(0)=='i'){
      newValue =  (float)message.getInt(0);
    }
    else{
      if(message.getType(0)=='f'){ 
        newValue = message.getFloat(0);
      }    
      else{
        return;
      }
    }
    setValue(newValue);
  };
#endif