#include "control.h"

void BurnInProm(char *prom_file) {

  int row, col;
  char code[MICRO_WORD_SIZE]; /* width of control store code      */
  FILE *inputfile;            /* pointer to input file library    */

  //  Zero out microMemory
  for (row = 0; row < MAX_SIZE; ++row)
    for (col = 0; col < MICRO_WORD_SIZE - 1; ++col)
      microMemory[row][col] = ZERO;

  //  Open promfile for loading
  if ((inputfile = fopen(prom_file, "r")) == NULL)
    if ((inputfile = fopen("promfile.dat", "r")) == NULL) {
      fprintf(stderr, "Can't open Promfile, aborting \n");
      exit(2);
    }

  // Read in code LINE BY LINE and scan it
  for (row = 0; fscanf(inputfile, "%s", code) != EOF; ++row){
    for (col = 0; col < MICRO_WORD_SIZE - 1; ++col)
      microMemory[row][col] = code[col];
    ++rowCounter;
  }

  fprintf(stderr, "\nRead in %d micro instructions\n", rowCounter);
  fclose(inputfile);
}

void OutputProm(void) {
  int row, col;

  for (row = 0; row < rowCounter; ++row) {
    for (col = 0; col < MICRO_WORD_SIZE - 1; ++col)
      printf("%c", microMemory[row][col]);

    printf("\n");
  }
}

int BusRegister(FourBits RField) {
  int sum = 0;

  if (RField[3] == ONE)
    sum = 1;

  if (RField[2] == ONE)
    sum += 2;
  if (RField[1] == ONE)
    sum += 4;
  if (RField[0] == ONE)
    sum += 8;

  return sum;

}

void DecodeRegField(FourBits RField, DataBusType Field) {
  char str[] = BIT_STRING_ZERO;

  str[BusRegister(RField)] = ONE;

  strcpy(Field, str);
}

void DecodeAField(DataBusType ABits) {
  FourBits AField = {MIR[20], MIR[21], MIR[22], MIR[23]};
  DecodeRegField(AField, ABits);
}

void DecodeBField(DataBusType BBits) {
  FourBits BField = {MIR[16], MIR[17], MIR[18], MIR[19]};
  DecodeRegField(BField, BBits);
}

void DecodeCField(DataBusType CBits) {
  FourBits CField = {MIR[12], MIR[13], MIR[14], MIR[15]};

  if (MIR[11] == ONE)
    DecodeRegField(CField, CBits);
  else
    strcpy(CBits, BIT_STRING_ZERO);
}

void LoadMirFromControlStore(void) {
  int i;

  for (i = 0; i < MICRO_WORD_SIZE - 1; ++i)
    MIR[i] = microMemory[microPc][i];
}

void DetermineMmux(Bit NBit, Bit ZBit, TwoBits Cond, Bit *Mmux) {
  if ((Cond[0] == ONE && Cond[1] == ONE) ||
      (Cond[0] == ONE && Cond[1] == ZERO && ZBit == ONE) ||
      (Cond[0] == ZERO && Cond[1] == ONE && NBit == ONE))
    *Mmux = ONE;
  else
    *Mmux = ZERO;
}

int ConvertToCardinal(EightBits Addr) {
  int i, sum;

  for (i = sum = 0; i <= 7; ++i) {
    sum *= 2;
    if (Addr[i] == ONE)
      sum += 1;
  }
  return sum;
}

void LoadMicroProgramCounter(Bit NBit, Bit ZBit, TwoBits Cond, EightBits Addr) {
  Bit Mmux;

  DetermineMmux(NBit, ZBit, Cond, &Mmux);

  if (Mmux == ZERO)
    microPc += 1;
  else
    microPc = ConvertToCardinal(Addr);
}

void ActivateControlStoreHelper(Bit *AmuxBit, TwoBits AluBits,
                                TwoBits ShiftBits, Bit *MbrBit, Bit *MarBit,
                                Bit *ReadBit, Bit *WriteBit) {
  *AmuxBit = MIR[0];
  AluBits[0] = MIR[3];
  AluBits[1] = MIR[4];
  ShiftBits[0] = MIR[5];
  ShiftBits[1] = MIR[6];
  *MbrBit = MIR[7];
  *MarBit = MIR[8];
  *ReadBit = MIR[9];
  *WriteBit = MIR[10];
}

void ActivateControlStore(Bit NBit, Bit ZBit, DataBusType ABits,
                          DataBusType BBits, DataBusType CBits, Bit *AmuxBit,
                          TwoBits AluBits, TwoBits ShiftBits, Bit *MbrBit,
                          Bit *MarBit, Bit *ReadBit, Bit *WriteBit) {

  if (FirstSubcycle()) {
    LoadMirFromControlStore();
    ActivateControlStoreHelper(AmuxBit, AluBits, ShiftBits, MbrBit, MarBit,
                               ReadBit, WriteBit);
  }

  if (SecondSubcycle()) {
    DecodeAField(ABits);
    DecodeBField(BBits);
    ActivateControlStoreHelper(AmuxBit, AluBits, ShiftBits, MbrBit, MarBit,
                               ReadBit, WriteBit);
  }

  if (ThirdSubcycle()) {
    ActivateControlStoreHelper(AmuxBit, AluBits, ShiftBits, MbrBit, MarBit,
                               ReadBit, WriteBit);
  }

  if (FourthSubcycle()) {
    DecodeCField(CBits);

    TwoBits Cond = {MIR[1], MIR[2]};
    EightBits Addr = {MIR[24], MIR[25], MIR[26], MIR[27],
                      MIR[28], MIR[29], MIR[30], MIR[31]};

    LoadMicroProgramCounter(NBit, ZBit, Cond, Addr);
    ActivateControlStoreHelper(AmuxBit, AluBits, ShiftBits, MbrBit, MarBit,
                               ReadBit, WriteBit);
  }
}
