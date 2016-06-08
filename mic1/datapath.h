//  DEFINE GUARD
#ifndef MIC1_DATAPATH_H
#define MIC1_DATAPATH_H

//  INCLUDES
#include <stdbool.h>
#include <stdio.h>
#include <strings.h>

#include "globals.h"
#include "variables.h"
#include "clock.h"
#include "alu.h"

//  EXTERNAL DECLARATIONS
extern void ActivateShifter(DataBusType InputBits, TwoBits ShiftBits,
                            DataBusType ShifterOutput);
extern int btoi(char *mem_loc);

//  DECLARATIONS
void DumpRegisters(void);

void LoadMar(DataBusType DataLines);

int SelectRegister(DataBusType Lines);

void LoadLatch(DataBusType latch, DataBusType bits);

void LoadRegisterBank(DataBusType CBits, DataBusType DataLines);

void ActivateDataPath(AddressBusType MarRegs, DataBusType MbrRegs,
                      DataBusType ABits, DataBusType BBits, DataBusType CBits,
                      Bit AmuxBit, TwoBits AluBits, TwoBits ShiftBits,
                      Bit MbrBit, Bit MarBit, Bit *NBit, Bit *ZBit);
void InitializePCandStackPointer(int pc, int sp);

//  END DEFINE GUARD
#endif