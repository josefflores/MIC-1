//  INCLUDES
#include "clock.h"

typedef struct Clock {
  int Cycle;
  int Subcycle;
} Clock;

//  Variables
static Clock Quartz = {0, 0};

/**
 *  Determine if it is in a given subcycle of the clock.
 *
 *  @function InSubCycle
 *  @param    <int>   subCycle  The clock's subCycle to check, start at 1.
 *  @return   <bool>  true      In given subCycle.
 *  @return   <bool>  false     Not in given subCycle.
 */
extern bool InSubCycle(int subCycle) {
  //  if the subcycle matches the expected subcycle
  return (Quartz.Subcycle == subCycle);
}
/**
 *  Gets the number of clock cycles that have occured.
 *
 *  @function GetCycle
 *  @return   <int>   The number of clock cycles
 */
extern int GetCycle(void) {
  //  return the number of cycles that have occured
  return Quartz.Cycle;
}
/**
 *  Sets the number of clock SubCycles to a cycle value between 0 and
 *  CLOCK_CYCLES inclusive.
 *
 *  @function SetSubCycle
 *  @return   <int>   The number of clock cycles
 */
extern int SetSubCycle(int subCycle) {
  Quartz.Subcycle = subCycle % (CLOCK_CYCLES + 1);
}
/**
 *  Generate a pulse of the clock, this moves through the subcycles and
 *  increments the total number of cycles.
 *
 *  @function GeneratePulse
 *  @return   <bool>  true      In given subCycle.
 *  @return   <bool>  false     Not in given subCycle.
 */
extern void GeneratePulse(void) {
  IncrementSubCycle();
  if (InSubCycle(1))
    IncrementCycle();
}
/**
 *  Increments a SubCycle to an integer between 1 and CLOCK_CYCLES inclusive.
 *
 *  @function IncrementSubCycle
 */
static void IncrementSubCycle(void) {
  Quartz.Subcycle = (Quartz.Subcycle % CLOCK_CYCLES) + 1;
}
/**
 *  Increments a clock Cycle.
 *
 *  @function IncrementCycle
 */
static void IncrementCycle(void) { Quartz.Cycle++; }