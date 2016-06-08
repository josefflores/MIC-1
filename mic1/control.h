//  DEFINE GUARD
#ifndef MIC1_CONTROL_H
#define MIC1_CONTROL_H

//  INCLUDES
#include <stdbool.h>
#include <stdio.h>
#include <strings.h>
#include "globals.h"
#include "variables.h"

//  EXTERNALS
extern bool FirstSubcycle(void);
extern bool SecondSubcycle(void);
extern bool ThirdSubcycle(void);
extern bool FourthSubcycle(void);

//  DECLARATIONS
void BurnInProm(char *prom_file) ;

void OutputProm(void) ;

int BusRegister(FourBits RField) ;

void DecodeRegField(FourBits RField, DataBusType Field) ;

void DecodeAField(DataBusType ABits) ;

void DecodeBField(DataBusType BBits) ;

void DecodeCField(DataBusType CBits) ;

void LoadMirFromControlStore(void) ;

void DetermineMmux(Bit NBit, Bit ZBit, TwoBits Cond, Bit *Mmux) ;

int ConvertToCardinal(EightBits Addr) ;

void LoadMicroProgramCounter(Bit NBit, Bit ZBit, TwoBits Cond, EightBits Addr) ;

void ActivateControlStoreHelper(Bit *AmuxBit, TwoBits AluBits,
                                TwoBits ShiftBits, Bit *MbrBit, Bit *MarBit,
                                Bit *ReadBit, Bit *WriteBit) ;

void ActivateControlStore(Bit NBit, Bit ZBit, DataBusType ABits,
                          DataBusType BBits, DataBusType CBits, Bit *AmuxBit,
                          TwoBits AluBits, TwoBits ShiftBits, Bit *MbrBit,
                          Bit *MarBit, Bit *ReadBit, Bit *WriteBit) ;

//  END DEFINE GUARD
#endif