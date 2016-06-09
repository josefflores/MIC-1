//  INCLUDES
#include "control.h"

//  VARIABLES
static int rowCounter = 0;
static int microPc = 0;
static MicroWord mir;
static MicroWord microMemory[MAX_SIZE];

//  DEFINITIONS
extern void resetMicroPC(void) { microPc = 0; }
extern void BurnInProm(char *promFile) {

  int r, c;
  char code[MICRO_WORD_SIZE]; /* width of control store code      */
  FILE *fp;                   /* pointer to input file library    */

  //  Zero out microMemory
  for (r = 0; r < MAX_SIZE; ++r)
    for (c = 0; c < MICRO_WORD_SIZE - 1; ++c)
      microMemory[r][c] = ZERO;

  //  Open promfile for loading
  if ((fp = fopen(promFile, "r")) || (fp = fopen("promfile.dat", "r"))) {
    fprintf(stderr, "Can't open Promfile, aborting \n");
    exit(2);
  }

  // Read in code LINE BY LINE and scan it
  for (r = 0; fscanf(fp, "%s", code) != EOF; ++r) {
    for (c = 0; c < MICRO_WORD_SIZE - 1; ++c)
      microMemory[r][c] = code[c];
    ++rowCounter;
  }

  fprintf(stderr, "\nRead in %d micro instructions\n", rowCounter);
  fclose(fp);
}
extern void OutputProm(void) {
  int r, c;

  for (r = 0; r < rowCounter; ++r) {
    for (c = 0; c < MICRO_WORD_SIZE - 1; ++c)
      printf("%c", microMemory[r][c]);

    printf("\n");
  }
}
extern void ActivateControlStore(Bit NBit, Bit ZBit, DataBusType ABits,
                                 DataBusType BBits, DataBusType CBits,
                                 Bit *AmuxBit, TwoBits AluBits,
                                 TwoBits ShiftBits, Bit *MbrBit, Bit *MarBit,
                                 Bit *ReadBit, Bit *WriteBit) {

  if (InSubCycle(1)) {
    LoadMirFromControlStore();
  } else if (InSubCycle(2)) {
    DecodeAField(ABits);
    DecodeBField(BBits);
  } else if (InSubCycle(4)) {
    DecodeCField(CBits);
    LoadMicroProgramCounter(NBit, ZBit);
  }

  *AmuxBit = mir[0];
  AluBits[0] = mir[3];
  AluBits[1] = mir[4];
  ShiftBits[0] = mir[5];
  ShiftBits[1] = mir[6];
  *MbrBit = mir[7];
  *MarBit = mir[8];
  *ReadBit = mir[9];
  *WriteBit = mir[10];
}
static int BusRegister(FourBits RField) {
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
static void DecodeRegField(FourBits RField, DataBusType Field) {
  char str[] = BIT_STRING_ZERO;

  str[BusRegister(RField)] = ONE;

  strcpy(Field, str);
}
static void DecodeAField(DataBusType ABits) {
  FourBits AField = {mir[20], mir[21], mir[22], mir[23]};
  DecodeRegField(AField, ABits);
}
static void DecodeBField(DataBusType BBits) {
  FourBits BField = {mir[16], mir[17], mir[18], mir[19]};
  DecodeRegField(BField, BBits);
}
static void DecodeCField(DataBusType CBits) {
  FourBits CField = {mir[12], mir[13], mir[14], mir[15]};

  if (mir[11] == ONE)
    DecodeRegField(CField, CBits);
  else
    strcpy(CBits, BIT_STRING_ZERO);
}
static void LoadMirFromControlStore(void) {
  int i;

  for (i = 0; i < MICRO_WORD_SIZE - 1; ++i)
    mir[i] = microMemory[microPc][i];
}
static char DetermineMmux(Bit NBit, Bit ZBit) {
  if ((mir[1] == ONE && mir[2] == ONE) ||
      (mir[1] == ONE && mir[2] == ZERO && ZBit == ONE) ||
      (mir[1] == ZERO && mir[2] == ONE && NBit == ONE))
    return ONE;

  return ZERO;
}
static int ConvertToCardinal(Bit *Addr, int numBits) {
  int i, sum;

  for (i = sum = 0; i < numBits; ++i) {
    sum *= 2;
    if (Addr[i] == ONE)
      sum += 1;
  }
  return sum;
}
static void LoadMicroProgramCounter(Bit NBit, Bit ZBit) {
  if (DetermineMmux(NBit, ZBit) == ZERO)
    microPc += 1;
  else
    microPc = ConvertToCardinal(mir + 24, 8);
}
