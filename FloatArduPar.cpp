#include "FloatArduPar.h"

void FloatArduPar::setup(
    const ARDUPAR_CONST_CHAR *cmdString,
    float minValue,
    float maxValue,
    boolean isPersistent, ///< should the parameter value be initialized from eeprom on startup?
    float *valuePointer,  ///< the setting can modify an arbitrary location im memory if you give it here.
    int fixedEEPROMAdress ///< if you want a specific fixed adress, specify it here
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
            TRACE((F("Getting EEPROM. asking for auto address: ")));
            fixedEEPROMAdress = EepromWrapper::getAdressFor(sizeof(float));
        };
        this->eepromAdress = fixedEEPROMAdress;
        TRACE((F("Init from EEPROM. Adress: ")));
        TRACE((int)(eepromAdress));
        float tempFloat = 0;
        EepromWrapper::read_bytes(&tempFloat, eepromAdress, sizeof(float));
#if defined(__AVR__)
			bool success=isfinite(tempFloat);
#else
			bool success=std::isfinite(tempFloat);
#endif

        if (success)
        {
            *valuePointer = tempFloat;
        }
        TRACE((F(" value:")));
        TRACELN((*valuePointer));
    }
    else
    {
        this->eepromAdress = -1; // used to signal non-persistence to other methods
    };
};

/// set the attached integer parameter from a string that was received
void FloatArduPar::parseParameterString(char *data)
{
    setValue(atof(data));
};

// set the value and rpint some debug info
void FloatArduPar::setValue(float newValue)
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
        EepromWrapper::write_bytes(valuePointer, eepromAdress, sizeof(float));
    }
};

void FloatArduPar::dumpParameterInfo(Stream *out)
{
    out->print(F("float\t"));
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
void FloatArduPar::parseOscMessage(OSCMessage& message){
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
