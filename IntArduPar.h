#pragma once
#include "Arduino.h"
#include "ArduParHelpers.h"
#include "ArduParCollection.h"
#include "EepromWrapper.h"

////////////////////
/// a setting for integer values with optional eeprom persistency
class AbstractArduPar;

class IntArduPar : public AbstractArduPar
{
public:
  int value;
  int *valuePointer; ///< points to the parameter value to be set
  int eepromAdress;  ///< an adress in eeprom memory for permanent storage of the parameter value. When <0 no storage will happen
  int minValue;      ///< lower Bound of the Parameter. Received values are constrained to be in the Range of [minValue,maxValue]
  int maxValue;      ///< upper Bound of the Parameter. Received values are constrained to be in the Range of [minValue,maxValue]

  /// simplest possible constructor, will use own value and no persistency
  IntArduPar() : value(0),
                 valuePointer(&this->value)
  {
  }
  /// set up the setting. has to be called to make it functional
  void setup(
      const ARDUPAR_CONST_CHAR *cmdString,
      int minValue,
      int maxValue,
      boolean isPersistent = true, ///< should the parameter value be initialized from eeprom on startup?
      int *valuePointer = 0,       ///< the setting can modify an arbitrary location im memory if you give it here.
      int fixedEEPROMAdress = -1   ///< if you want a specific fixed adress, specify it here
  );

  void parseParameterString(char *data); ///< parse the numeric literal part of a set command
  void setValue(int newValue);  ///< set the value and rpint some debug info
  void dumpParameterInfo(Stream *out);  ///< give human&machine readably status info
};