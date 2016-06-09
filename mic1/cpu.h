//  INCLUDES
#include "globals.h"
#include "variables.h"
#include "control.h"

//  EXTERNALS
extern  void ActivateDataPath(AddressBusType MarRegs, DataBusType MbrRegs,
                      DataBusType ABits, DataBusType BBits, DataBusType CBits,
                      Bit AmuxBit, TwoBits AluBits, TwoBits ShiftBits,
                      Bit MbrBit, Bit MarBit, Bit *NBit, Bit *ZBit) ;

//  DECLARATIONS
void ActivateCpu (AddressBusType MarRegs, DataBusType MbrRegs, Bit ReadBit, Bit WriteBit);
