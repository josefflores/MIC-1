//  DEFINE GUARD
#ifndef MIC1_CPU_H
#define MIC1_CPU_H

//  INCLUDES
#include "globals.h"
#include "variables.h"

//  EXTERNALS
extern  void ActivateControlStore(Bit NBit, Bit ZBit, DataBusType ABits,
                          DataBusType BBits, DataBusType CBits, Bit *AmuxBit,
                          TwoBits AluBits, TwoBits ShiftBits, Bit *MbrBit,
                          Bit *MarBit, Bit *ReadBit, Bit *WriteBit) ;
extern  void ActivateDataPath(AddressBusType MarRegs, DataBusType MbrRegs,
                      DataBusType ABits, DataBusType BBits, DataBusType CBits,
                      Bit AmuxBit, TwoBits AluBits, TwoBits ShiftBits,
                      Bit MbrBit, Bit MarBit, Bit *NBit, Bit *ZBit) ;

//  DECLARATIONS
void ActivateCpu (AddressBusType MarRegs, DataBusType MbrRegs, Bit ReadBit, Bit WriteBit);

//  END DEFINE GUARD
#endif