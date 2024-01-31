#pragma once
#include "Arduino.h"
#include "ArduParHelpers.h"
#include "ArduParCollection.h"
#include "EepromWrapper.h"

////////////////////
/// a setting for integer values with optional eeprom persistency
class CallbackArduPar : public AbstractArduPar
{
public:
  void (*callbackFunction)(void); ///< points to the function to be called

  /// set up the setting. has to be called to make it functional
  void setup(
      const ARDUPAR_CONST_CHAR *cmdString,
      void (*callbackFunction)(void)        ///< A pointer to the function that will be triggered.
  );

  void parseParameterString(char *data); ///< parse the numeric literal part of a set command
  void dumpParameterInfo(Stream *out);  ///< give human&machine readably status info
};