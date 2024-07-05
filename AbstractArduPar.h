#pragma once
#include "Arduino.h"
#include "ArduParHelpers.h"
#include "EepromWrapper.h"

#ifdef ARDUPAR_USE_OSC
#include <OSCMessage.h>
#endif

/// A common interface for all kinds of parameter settings.
class AbstractArduPar
{
public:
  virtual void parseSerialData(char *data);          ///< digest incoming serial data that potentially contains a "set" command
  virtual void parseParameterString(char *data) = 0; ///< derived classed implement parsing and setting parameters from a string here
  virtual void dumpParameterInfo(Stream *out) = 0;   ///< derived classed can give some information about semselves this way. preferably in a machine-readable way.
  const ARDUPAR_CONST_CHAR *cmdString;               ///< serial input is parsed for this command string, anything that follows is interpreted as parameter data
  size_t cmdStringLength;                            ///< used for comparisons
  bool valueReceived = false;                        ///< indicates that a new value was received either from a Stream or by OSC. Set to false to be notified again.

  // optional osc support
#ifdef ARDUPAR_USE_OSC
  virtual void parseOscMessage(OSCMessage &message){}; ///< digest incoming message, similar to parseParameterString
                                                       /// Get the OSC Adress of the Setting
  const __FlashStringHelper *getAddress()
  {
    return (cmdString);
  }
  /// Return true is the message OSC Adress is identical to that of the setting.
  boolean isOscMessageForMe(OSCMessage &mes)
  {
    TRACELN("matching with");
    TRACELN(getAddress());
    TRACELN(strcmp_P(mes.getAddress(), (const char PROGMEM *)this->getAddress()));
    return (strcmp_P(mes.getAddress(), (const char PROGMEM *)this->getAddress()) == 0);
  };
#endif
};
