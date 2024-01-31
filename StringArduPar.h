#pragma once
#include "Arduino.h"
#include "ArduParHelpers.h"
#include "ArduParCollection.h"
#include "EepromWrapper.h"

////////////////////
/// a setting for string values with optional eeprom persistency
class StringArduPar : public AbstractArduPar
{
public:
  char *valuePointer; ///< points to the parameter value to be set
  int eepromAdress;   ///< an adress in eeprom memory for permanent storage of the parameter value. When <0 no storage will happen
  int maxLength;      ///< maximum Length the buffers can hold

  /// Initialize the setting. Has to be called for the setting to become usable.
  void setup(
      const ARDUPAR_CONST_CHAR *cmdString, ///< Osc Adress of the setting
      char *valuePointer,                   ///< points to the buffer where incoming strings will be written
      int maxLength,                        ///< maximum number of chars the buffer can hold
      boolean isPersistent = true,          ///< should the parameter value be initialized from eeprom on startup?
      int fixedEEPROMAdress = -1            ///< if you want a specific fixed adress, specify it here
  );
  virtual void parseParameterString(char *data);  ///< set the string parameter from the remaining data. one leading character after the command name is skipped
  void saveValue();  // set the value and rpint some debug info
  virtual void dumpParameterInfo(Stream *out);  ///< give human&machine readably status info
};
