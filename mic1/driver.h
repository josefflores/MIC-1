//  DEFINE GUARD
#ifndef MIC1_DATAPATH_H
#define MIC1_DATAPATH_H

//  INCLUDES
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>
#include "globals.h"
#include "variables.h"
#include "util.h"
#include "datapath.h"


//  DECLARATIONS
extern void BurnInProm(char *prom_file);
extern void InitializeMemory(char *program_file);
extern void InitializePCandStackPointer(int pc, int sp);
extern void ActivateCpu(AddressBusType MarRegs, DataBusType MbrRegs,
                        Bit ReadBit, Bit WriteBit);
extern void ActivateMemory(AddressBusType Address, DataBusType Data,
                           Bit ReadBit, Bit WriteBit);
extern void DumpMemory(int From, int To);
extern void GeneratePulse(void);
extern int Cycle(void);
extern void DumpRegisters(void);

//  END DEFINE GUARD
#endif