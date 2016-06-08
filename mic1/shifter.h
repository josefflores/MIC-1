//  DEFINE GUARD
#ifndef MIC1_SHIFTER_H
#define MIC1_SHIFTER_H

//  INCLUDES
#include <strings.h>
#include "globals.h"

//  DECLARATIONS
void ShiftLeft(DataBusType InputBits, DataBusType ShifterOutput);
void ShiftRight(DataBusType InputBits, DataBusType ShifterOutput);
void ActivateShifter(DataBusType InputBits, TwoBits ShiftBits,
                     DataBusType ShifterOutput);

//  END DEFINE GUARD
#endif