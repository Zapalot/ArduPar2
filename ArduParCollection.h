#pragma once
#include "AbstractArduPar.h"
class ArduParCollection
{
public:
  // some static members for keeping track of all the instances
  static AbstractArduPar *knownInstances[PAR_SETTINGS_MAX_NUMBER];
  static size_t numInstancesRegistered;
  static void registerInstance(AbstractArduPar *instance);
  static void updateParametersFromStream(Stream *inStream, int timeout); ///< distributes incoming data from a stream to the parameter setting instances
  static void dumpParameterInfos(Stream *outStream); ///< write information about all parameter instances to a stream
  static void dumpParameterInfos();
};