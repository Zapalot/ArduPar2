#include "AbstractArduPar.h"

void AbstractArduPar::parseSerialData(char *data)
{
    TRACE((F("Matching serial cmd")));
    TRACE((cmdString));
    TRACE((F("to")));
    TRACELN((data));
    int foundPos = strncmp_P(data, (const char PROGMEM *)cmdString, cmdStringLength);

    if (foundPos == 0)
    {
        TRACE(F("matched:"));
        TRACELN((cmdString));
        parseParameterString(data + strlen_P((const char PROGMEM *)cmdString));
    }
}
