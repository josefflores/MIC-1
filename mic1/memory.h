//  DEFINE GUARD
#ifndef MIC1_MEMORY_H
#define MIC1_MEMORY_H

//  INCLUDES
#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include "globals.h"
#include "variables.h"

//  EXTERNAL DECLARATIONS
extern int Set_blocking_io();
extern int Set_nonblocking_io();
extern int True_ascii_to_mem_ascii(char *mem_location, char *character);
extern char btoc(char *mem_loc);

//  DECLARATIONS
void ActivateMemoryChip0(ChipRange Offset, DataBusType Data, Bit ReadBit,
                         Bit WriteBit) ;

void ActivateMemoryChip1(ChipRange Offset, DataBusType Data, Bit ReadBit,
                         Bit WriteBit) ;

void ActivateMemoryChip2(ChipRange Offset, DataBusType Data, Bit ReadBit,
                         Bit WriteBit) ;

void ActivateMemoryChip3(ChipRange Offset, DataBusType Data, Bit ReadBit,
                         Bit WriteBit) ;

int ComputeOffset(AddressBusType Address) ;

int ComputeChipSelect(Bit Address0, Bit Address1) ;

void ActivateMemory(AddressBusType Address, DataBusType Data, Bit ReadBit,
                    Bit WriteBit) ;

void DumpMemory(int From, int To) ;

void InitializeMemory(char *program_file) ;

void MemoryRead(int mem_loc, char *mem_val);

//  END DEFINE GUARD
#endif