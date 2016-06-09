//  INCLUDES
#include <stdbool.h>
#include <stdio.h>
#include <strings.h>

#include "globals.h"
#include "variables.h"
#include "clock.h"

//  DECLARATIONS
extern void resetPromPC(void);

extern void readProm(char *promFile);

extern void writeProm(void);

extern void activateControlStore(Bit NBit, Bit ZBit, DataBusType ABits,
                                 DataBusType BBits, DataBusType CBits,
                                 Bit *AmuxBit, TwoBits AluBits,
                                 TwoBits ShiftBits, Bit *MbrBit, Bit *MarBit,
                                 Bit *ReadBit, Bit *WriteBit);

static int busRegister(FourBits RField);

static void decodeField_Reg(FourBits RField, DataBusType Field);

static void decodeField_A(DataBusType ABits);

static void decodeField_B(DataBusType BBits);

static void decodeField_C(DataBusType CBits);

static void loadMirFromControlStore(void);

static char determineMmux(Bit NBit, Bit ZBit);

static int convertToCardinal(Bit *Addr, int numBits);

static void loadMicroProgramCounter(Bit NBit, Bit ZBit);