#include "ArduParCollection.h"
#include "AbstractArduPar.h"
size_t ArduParCollection::numInstancesRegistered=0;
AbstractArduPar* ArduParCollection::knownInstances[PAR_SETTINGS_MAX_NUMBER];


void ArduParCollection::registerInstance(AbstractArduPar* instance){
    //register instance in the global array
    if(numInstancesRegistered<PAR_SETTINGS_MAX_NUMBER){
      knownInstances[numInstancesRegistered]=instance;
      numInstancesRegistered++;
    }
    else{
      Serial.print(F("Max Parsetting instances exceeded, could not register"));
      Serial.println(instance->cmdString);
    }
}



/// this function automatically distributes incoming data from a stream to the parameter setting instances
void ArduParCollection::updateParametersFromStream(Stream *inStream, int timeout)
{
  if (!inStream->available())
    return; // if there is no data available, dont even start timeouts
  // read data from stream
  char buf[PAR_SETTINGS_BUFFER_SIZE];
  int bufPos = 0;
  int inByte;
  long lastCharMillis = millis();
  // even if the buffer is full, we keep on reading to flush the remaining data.
  bool receivedNewLine = false;
  while ((millis() - lastCharMillis) < timeout && !receivedNewLine)
  {
    inByte = inStream->read();
    if (inByte == '\n' || inByte == '\r')
      receivedNewLine = true;
    if (inByte > 0)
    {
      lastCharMillis = millis();
      if (bufPos < PAR_SETTINGS_BUFFER_SIZE - 1)
      {
        buf[bufPos] = inByte;
        bufPos++;
      }
    }
  }

  buf[bufPos] = 0;

  // let all the parameter setting instances have a look at the data
  if (bufPos > 0)
  {
    for (int i = 0; i < numInstancesRegistered; i++)
    {
      knownInstances[i]->parseSerialData(buf);
    }
  }
};

/// write information about all parameter instances to a stream
void ArduParCollection::dumpParameterInfos(Stream *outStream)
{
  for (int i = 0; i < numInstancesRegistered; i++)
  {
    knownInstances[i]->dumpParameterInfo(outStream);
  }
};

/// write information about all parameter instances to a stream
void ArduParCollection::dumpParameterInfos()
{
  dumpParameterInfos(&Serial);
};
