#include "shifter.h"

void ShiftLeft(DataBusType InputBits, DataBusType ShifterOutput) {
  int i;

  for (i = 0; i < DATA_WORD_SIZE - 1; i++)
    ShifterOutput[i] = InputBits[i + 1];

  ShifterOutput[DATA_WORD_SIZE - 2] = ZERO;
}

void ShiftRight(DataBusType InputBits, DataBusType ShifterOutput) {
  int i;

  ShifterOutput[0] = ZERO;

  for (i = 1; i < DATA_WORD_SIZE - 1; i++)
    ShifterOutput[i] = InputBits[i - 1];
}

void ActivateShifter(DataBusType InputBits, TwoBits ShiftBits,
                     DataBusType ShifterOutput) {

  Bit ShiftBit0, ShiftBit1;

  ShiftBit0 = ShiftBits[0];
  ShiftBit1 = ShiftBits[1];

  strcpy(ShifterOutput, InputBits);

  if ((ShiftBit0 == ZERO) && (ShiftBit1 == ONE))

    ShiftRight(InputBits, ShifterOutput);

  else if

      ((ShiftBit0 == ONE) && (ShiftBit1 == ZERO))

    ShiftLeft(InputBits, ShifterOutput);
}
