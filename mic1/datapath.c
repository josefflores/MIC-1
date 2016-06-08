#include "datapath.h"

void DumpRegisters(void) {

  printf("\nProgramCounter : %s  base 10:  %6d\n", ProgramCounter,
         btoi(ProgramCounter));
  printf("Accumulator    : %s  base 10:  %6d\n", Accumulator,
         btoi(Accumulator));
  printf("InstructionReg : %s  base 10:  %6d\n", InstructionReg,
         btoi(InstructionReg));
  printf("TempInstr      : %s  base 10:  %6d\n", TempInstruction,
         btoi(TempInstruction));
  printf("StackPointer   : %s  base 10:  %6d\n", StackPointer,
         btoi(StackPointer));
  printf("ARegister      : %s  base 10:  %6d\n", ARegister, btoi(ARegister));
  printf("BRegister      : %s  base 10:  %6d\n", BRegister, btoi(BRegister));
  printf("CRegister      : %s  base 10:  %6d\n", CRegister, btoi(CRegister));
  printf("DRegister      : %s  base 10:  %6d\n", DRegister, btoi(DRegister));
  printf("ERegister      : %s  base 10:  %6d\n", ERegister, btoi(ERegister));
  printf("FRegister      : %s  base 10:  %6d\n", FRegister, btoi(FRegister));
}

void LoadMar(DataBusType DataLines) {
  int i;

  for (i = 0; i < DATA_WORD_SIZE - 5; ++i)
    MAR[i] = DataLines[i + 4];
}

int SelectRegister(DataBusType Lines) {
  int i;

  for (i = DATA_WORD_SIZE - 1; i >= 0; --i)
    if (Lines[i] == ONE)
      return i;

  return DATA_WORD_SIZE - 1;
}

void LoadLatch(DataBusType latch, DataBusType bits) {
  switch (SelectRegister(bits)) {
  case 0:
    strcpy(latch, ProgramCounter);
    break;
  case 1:
    strcpy(latch, Accumulator);
    break;
  case 2:
    strcpy(latch, StackPointer);
    break;
  case 3:
    strcpy(latch, InstructionReg);
    break;
  case 4:
    strcpy(latch, TempInstruction);
    break;
  case 5:
    strcpy(latch, ZERORegister);
    break;
  case 6:
    strcpy(latch, PositiveONE);
    break;
  case 7:
    strcpy(latch, NegativeONE);
    break;
  case 8:
    strcpy(latch, Amask);
    break;
  case 9:
    strcpy(latch, Smask);
    break;
  case 10:
    strcpy(latch, ARegister);
    break;
  case 11:
    strcpy(latch, BRegister);
    break;
  case 12:
    strcpy(latch, CRegister);
    break;
  case 13:
    strcpy(latch, DRegister);
    break;
  case 14:
    strcpy(latch, ERegister);
    break;
  case 15:
    strcpy(latch, FRegister);
    break;
  }
}

void LoadRegisterBank(DataBusType CBits, DataBusType DataLines) {
  switch (SelectRegister(CBits)) {
  case 0:
    strcpy(ProgramCounter, DataLines);
    break;
  case 1:
    strcpy(Accumulator, DataLines);
    break;
  case 2:
    strcpy(StackPointer, DataLines);
    break;
  case 3:
    strcpy(InstructionReg, DataLines);
    break;
  case 4:
    strcpy(TempInstruction, DataLines);
    break;
  case 10:
    strcpy(ARegister, DataLines);
    break;
  case 11:
    strcpy(BRegister, DataLines);
    break;
  case 12:
    strcpy(CRegister, DataLines);
    break;
  case 13:
    strcpy(DRegister, DataLines);
    break;
  case 14:
    strcpy(ERegister, DataLines);
    break;
  case 15:
    strcpy(FRegister, DataLines);
    break;
  case 16: /* strcpy (DataLines, DataLines) ; */
    break;
  }
}

void ActivateDataPath(AddressBusType MarRegs, DataBusType MbrRegs,
                      DataBusType ABits, DataBusType BBits, DataBusType CBits,
                      Bit AmuxBit, TwoBits AluBits, TwoBits ShiftBits,
                      Bit MbrBit, Bit MarBit, Bit *NBit, Bit *ZBit) {
  DataBusType LeftOperand;
  DataBusType RightOperand;

  strcpy(MAR, MarRegs);
  strcpy(MBR, MbrRegs);

  if (SecondSubcycle()) {
    LoadLatch(ALatch, ABits);
    LoadLatch(BLatch, BBits);
  }

  if (ThirdSubcycle()) {
    if (AmuxBit == ONE)
      strcpy(LeftOperand, MBR);
    else
      strcpy(LeftOperand, ALatch);

    if (MarBit == ONE) {
      LoadMar(BLatch);
      strcpy(MarRegs, MAR);
    }

    strcpy(RightOperand, BLatch);
    ActivateAlu(LeftOperand, RightOperand, AluBits, AluResult, NBit, ZBit);
    ActivateShifter(AluResult, ShiftBits, ShifterResult);
  }

  if (FourthSubcycle()) {
    LoadRegisterBank(CBits, ShifterResult);
    if (MbrBit == ONE) {
      strcpy(MBR, ShifterResult);
      strcpy(MbrRegs, ShifterResult);
    }
  }
}

void InitializePCandStackPointer(int pc, int sp) {
  char pc_str[] = BIT_STRING_ZERO;
  char sp_str[] = BIT_STRING_ZERO;
  int i, mask = BIN_32768;

  if (pc < 0 || sp < 0 || pc > PC_MAX || sp > SP_MAX) {
    strcpy(ProgramCounter, BIT_STRING_ZERO);
    strcpy(StackPointer, BIT_STRING_SP);
  } else {
    for (i = 0; i < DATA_WORD_SIZE - 1; ++i) {
      if (pc & (mask >> i))
        pc_str[i] = ONE;

      if (sp & (mask >> i))
        sp_str[i] = ONE;
    }

    strcpy(ProgramCounter, pc_str);
    strcpy(StackPointer, sp_str);

    fprintf(stderr, "Starting PC is : %s  base 10:  %6d\nStarting SP is : %s  "
                    "base 10:  %6d\n\n",
            pc_str, btoi(pc_str), sp_str, btoi(sp_str));
  }

  strcpy(ZERORegister, BIT_STRING_ZERO);
  strcpy(PositiveONE, BIT_STRING_POS_ONE);
  strcpy(NegativeONE, BIT_STRING_NEG_ONE);
  strcpy(Amask, BIT_STRING_A_MASK);
  strcpy(Smask, BIT_STRING_S_MASK);
}