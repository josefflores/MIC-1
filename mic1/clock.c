//  INCLUDES
#include "clock.h"

//  TYPEDEFINES
/**
 *  Defines a clock structure, It is used to keep track of subcycles and total
 *  cycles.
 */
typedef struct Clock {
  int cycle;    //  number of subCycles/ pulse circuits that have competed.
  int subCycle; //  A pulse count
} Clock;

//  VARIABLES
static Clock sysClock;

//  DEFINITIONS
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
  return (sysClock.subCycle == subCycle);
}
/**
 *  Gets the number of clock cycles that have occured.
 *
 *  @function GetCycle
 *  @return   <int>   The number of clock cycles
 */
extern int GetCycle(void) {
  //  return the number of cycles that have occured
  return sysClock.cycle;
}
/**
 *  Resets the subCycle count to 0.
 *
 *  @function resetClockSubCycle
 */
extern void resetClockSubCycle(void) { sysClock.subCycle = 0; }
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
  sysClock.subCycle = (sysClock.subCycle % CLOCK_CYCLES) + 1;
}
/**
 *  Increments a clock Cycle.
 *
 *  @function IncrementCycle
 */
static void IncrementCycle(void) { sysClock.cycle++; }