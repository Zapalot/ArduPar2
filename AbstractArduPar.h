#pragma once
#include "Arduino.h"
#include "ArduParHelpers.h"
#include "EepromWrapper.h"


/// A common interface for all kinds of parameter settings.
class AbstractArduPar
{
public:
  virtual void parseSerialData(char *data);          ///< digest incoming serial data that potentially contains a "set" command
  virtual void parseParameterString(char *data) = 0; ///< derived classed implement parsing and setting parameters from a string here
  virtual void dumpParameterInfo(Stream *out) = 0;   ///< derived classed can give some information about semselves this way. preferably in a machine-readable way.

  const ARDUPAR_CONST_CHAR *cmdString; ///< serial input is parsed for this command string, anything that follows is interpreted as parameter data
  size_t cmdStringLength;              ///< used for comparisons
  bool valueReceived = false;          ///< indicates that a new value was received either from a Stream or by OSC. Set to false to be notified again.
};

