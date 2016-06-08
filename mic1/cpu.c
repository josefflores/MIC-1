#include "cpu.h"

void ActivateCpu (AddressBusType MarRegs, DataBusType MbrRegs, Bit ReadBit, Bit WriteBit) {

    ActivateControlStore (NBit, ZBit, ABits, BBits, CBits,
                          &AmuxBit, AluBits, ShiftBits, &MbrBit, &MarBit,
                          &ReadBit, &WriteBit) ;

    ActivateDataPath (MarRegs, MbrRegs, ABits, BBits, CBits,
                      AmuxBit, AluBits, ShiftBits, MbrBit, MarBit,
                      &NBit, &ZBit) ;

}
