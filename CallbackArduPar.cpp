#include "CallbackArduPar.h"


void CallbackArduPar::setup(
    const ARDUPAR_CONST_CHAR *cmdString,
    void (*callbackFunction)(void)        ///< A pointer to the function that will be triggered.
){
    this->cmdString = cmdString;
    cmdStringLength = strlen_P((const char PROGMEM *)cmdString);
    this->callbackFunction = callbackFunction;
    ArduParCollection::registerInstance(this);
}

/// set the attached integer parameter from a string that was received
void CallbackArduPar::parseParameterString(char *data){
    TRACE((F("Calling ")));
    TRACE((this->cmdString));
    TRACE((F("\n")));
    callbackFunction();
};

void CallbackArduPar::dumpParameterInfo(Stream *out)
{
    out->print(F("trigger\t"));
    out->print(this->cmdString);
    out->print(F("\t"));
    out->print(this->cmdString);
    out->print(F("\n"));
}

#ifdef ARDUPAR_USE_OSC
void CallbackArduPar::parseOscMessage(OSCMessage& message){

    if(!isOscMessageForMe(message))return;
    callbackFunction();
};
#endif