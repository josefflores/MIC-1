#include "clock.h"

bool FirstSubcycle(void) { return (Quartz.Subcycle == 1); }

bool SecondSubcycle(void) { return (Quartz.Subcycle == 2); }

bool ThirdSubcycle(void) { return (Quartz.Subcycle == 3); }

bool FourthSubcycle(void) { return (Quartz.Subcycle == 4); }

int Cycle(void) { return Quartz.Cycle; }

void GeneratePulse(void) {
  Quartz.Subcycle = (Quartz.Subcycle % CLOCK_CYCLES) + 1;
  if (FirstSubcycle())
    Quartz.Cycle++;
}
