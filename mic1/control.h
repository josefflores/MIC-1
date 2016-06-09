//  INCLUDES
#include <stdbool.h>
#include <stdio.h>
#include <strings.h>

#include "clock.h"
#include "globals.h"
#include "variables.h"

//  DECLARATIONS
extern void resetMicroPC(void);

extern void BurnInProm(char *promFile);

extern void OutputProm(void);

extern void ActivateControlStore(Bit NBit, Bit ZBit, DataBusType ABits,
                                 DataBusType BBits, DataBusType CBits,
                                 Bit *AmuxBit, TwoBits AluBits,
                                 TwoBits ShiftBits, Bit *MbrBit, Bit *MarBit,
                                 Bit *ReadBit, Bit *WriteBit);

static int BusRegister(FourBits RField);

static void DecodeRegField(FourBits RField, DataBusType Field);

static void DecodeAField(DataBusType ABits);

static void DecodeBField(DataBusType BBits);

static void DecodeCField(DataBusType CBits);

static void LoadMirFromControlStore(void);

static char DetermineMmux(Bit NBit, Bit ZBit);

static int ConvertToCardinal(Bit *Addr, int numBits);

static void LoadMicroProgramCounter(Bit NBit, Bit ZBit);