#include "StringArduPar.h"


void StringArduPar::setup(
      const ARDUPAR_CONST_CHAR *cmdString, ///< Osc Adress of the setting
      char *valuePointer,                   ///< points to the buffer where incoming strings will be written
      int maxLength,                        ///< maximum number of chars the buffer can hold
      boolean isPersistent = true,          ///< should the parameter value be initialized from eeprom on startup?
      int fixedEEPROMAdress = -1            ///< if you want a specific fixed adress, specify it here
  )
  {

    this->cmdString = cmdString;
    cmdStringLength = strlen_P((const char PROGMEM *)cmdString);
    ArduParCollection::registerInstance(this);
    this->valuePointer = valuePointer;
    this->maxLength = maxLength;
    // setup reading and writing from eeprom
    if (isPersistent)
    {
      // get a generated location for persistency if none was specified
      if (fixedEEPROMAdress == -1)
        fixedEEPROMAdress = EepromWrapper::getAdressFor(maxLength);
      this->eepromAdress = fixedEEPROMAdress;
      TRACE((F("Init from EEPROM. Adress: ")));
      TRACE((int)(eepromAdress));
      EepromWrapper::read_bytes(valuePointer, eepromAdress, maxLength);
      valuePointer[maxLength - 1] = 0; // make sure the string is zero terminated even if we read some garbage from eeprom
      TRACE((F(" value:")));
      TRACE((valuePointer));
      TRACE(F("\n"));
    }
    else
    {
      this->eepromAdress = -1;
    }
  };


  /// set the string parameter from the remaining data. one leading character after the command name is skipped
   void StringArduPar::parseParameterString(char *data)
  {
    int dataLength = strlen(data);
    if (dataLength > 1)
    {
      valueReceived = true; // flag: I got new data!
      // skip first char.
      data++;
      dataLength--;

      int copyLength = min(maxLength - 1, dataLength);
      strncpy(valuePointer, data, copyLength);
      valuePointer[copyLength] = 0; // make sure the string is terminated
      saveValue();
    }
  };

  // set the value and rpint some debug info
  void StringArduPar::saveValue()
  {
    TRACE((F("Setting ")));
    TRACE((this->cmdString));
    TRACE((F(" to ")));
    TRACE((valuePointer));
    TRACE((F("\n")));
    // save the new value
    if (eepromAdress >= 0)
    {
      TRACE((F("Writing EEProm adress")));
      TRACE(eepromAdress);
      TRACE((F("\n")));
      EepromWrapper::write_bytes(valuePointer,eepromAdress, maxLength);
    }
  };
  /// give human&machine readably status info
  void StringArduPar::dumpParameterInfo(Stream *out)
  {
    out->print(F("string\t"));
    out->print(this->cmdString);
    out->print(F("\t"));
    out->print(this->cmdString);
    out->print(F("\t"));
    out->print(valuePointer);
    out->print(F("\n"));
  }