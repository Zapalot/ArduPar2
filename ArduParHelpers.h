#pragma once
#define DEBUG 1
#define TRACE(x)       \
  do                   \
  {                    \
    if (DEBUG)         \
      Serial.print(x); \
  } while (0)
#define TRACELN(x)       \
  do                     \
  {                      \
    if (DEBUG)           \
      Serial.println(x); \
  } while (0)

// the instances of classes derived from AbstractArduPar maintain a global list. You can change the maximum number of settings here.
#define PAR_SETTINGS_MAX_NUMBER 32

// this determines the maximum parameter command length
#define PAR_SETTINGS_BUFFER_SIZE 32