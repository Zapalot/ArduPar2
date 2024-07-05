#pragma once
#include "Arduino.h"
#include "ArduParHelpers.h"
#include "ArduParCollection.h"
#include "EepromWrapper.h"
#ifdef ARDUPAR_USE_OSC
#include <OSCMessage.h>
#endif
////////////////////
/// a setting for integer values with optional eeprom persistency
class AbstractArduPar; //prototype

class FloatArduPar : public AbstractArduPar
{
public:
  float value;
  float *valuePointer; ///< points to the parameter value to be set
  int eepromAdress;  ///< an adress in eeprom memory for permanent storage of the parameter value. When <0 no storage will happen
  float minValue;      ///< lower Bound of the Parameter. Received values are constrained to be in the Range of [minValue,maxValue]
  float maxValue;      ///< upper Bound of the Parameter. Received values are constrained to be in the Range of [minValue,maxValue]

  /// simplest possible constructor, will use own value and no persistency
  FloatArduPar() : value(0),
                 valuePointer(&this->value)
  {
  }
  /// set up the setting. has to be called to make it functional
  void setup(
      const ARDUPAR_CONST_CHAR *cmdString,
      float minValue,
      float maxValue,
      boolean isPersistent = true, ///< should the parameter value be initialized from eeprom on startup?
      float *valuePointer = 0,       ///< the setting can modify an arbitrary location im memory if you give it here.
      int fixedEEPROMAdress = -1   ///< if you want a specific fixed adress, specify it here
  );

  void parseParameterString(char *data); ///< parse the numeric literal part of a set command
  void setValue(float newValue);  ///< set the value and rpint some debug info
  void dumpParameterInfo(Stream *out);  ///< give human&machine readably status info
#ifdef ARDUPAR_USE_OSC
  void parseOscMessage(OSCMessage& message); ///< digest incoming message, similar to parseParameterString
#endif
};