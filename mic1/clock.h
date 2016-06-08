//  DEFINE GUARD
#ifndef MIC1_CLOCK_H
#define MIC1_CLOCK_H

//  INCLUDES
#include <stdbool.h>
#include "globals.h"
#include "variables.h"

//  DECLARATIONS
bool FirstSubcycle(void);
bool SecondSubcycle(void);
bool ThirdSubcycle(void);
bool FourthSubcycle(void);
int  Cycle(void);
void GeneratePulse(void);

//  END DEFINE GUARD
#endif