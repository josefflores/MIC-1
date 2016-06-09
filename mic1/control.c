//  INCLUDES
#include "control.h"

//  TYPEDEFINES
/**
 *  Defines a Prom structure, It is used to keep track of the microcode
 *  cycles.
 */
typedef struct Prom {
  int length; //  The length of the microcode.
  int pc;     //  The position in the microcode when running the program.
  MicroWord memBlock[MAX_SIZE]; // The microcode memory block.
} Prom;

//  VARIABLES
static MicroWord mir;
static Prom prom = {0, 0, STR_END};

//  DEFINITIONS
/**
 *  Resets the the program microcode position
 *
 *  @function resetPromPC
 */
extern void resetPromPC(void) { prom.pc = 0; }
/**
 *  Copies the promfile into memory
 *
 *  @function readProm
 *  @param  <char *> promfile The file name string
 *  @exit 2 File open error, the given file or default file could not be opened.
 */
extern void readProm(char *promFile) {
  //  VARIABLES
  int r, c;                   //  Loop counters, r: row, c: column
  char code[MICRO_WORD_SIZE]; //  Width of micro code string
  FILE *fp;                   //  Pointer to input file library

  //  Zero out the prom memory block
  for (r = 0; r < MAX_SIZE; ++r)
    for (c = 0; c < MICRO_WORD_SIZE - 1; ++c)
      prom.memBlock[r][c] = ZERO;

  /**
   *  Open promfile for loading, First attempts a given file name and then a
   *  default file name.
   */
  if ((fp = fopen(promFile, "r")) || (fp = fopen(DEFAULT_FILE, "r"))) {
    fprintf(stderr, "Can't open %s or %s, aborting \n", promFile, DEFAULT_FILE);
    exit(2);
  }

  /**
   *  Read in prom line by line, then write each character of the line to the
   *  prom.memBlock block.
   */
  for (r = 0; fscanf(fp, "%s", code) != EOF; ++r) {
    for (c = 0; c < MICRO_WORD_SIZE - 1; ++c)
      prom.memBlock[r][c] = code[c];
    //  Keep track of the number of rows that where written to prom.memBlock
    prom.length++;
  }
  //  Close file pointer
  fclose(fp);

  //  Display number of instructions that were read into the prom.memBlock.
  fprintf(stderr, "\nRead in %d micro instructions\n", prom.length);
}

extern void writeProm(void) {
  //  VARIABLES
  int r, c;

  for (r = 0; r < prom.length; ++r) {
    for (c = 0; c < MICRO_WORD_SIZE - 1; ++c)
      printf("%c", prom.memBlock[r][c]);

    printf("\n");
  }
}
extern void activateControlStore(Bit NBit, Bit ZBit, DataBusType ABits,
                                 DataBusType BBits, DataBusType CBits,
                                 Bit *AmuxBit, TwoBits AluBits,
                                 TwoBits ShiftBits, Bit *MbrBit, Bit *MarBit,
                                 Bit *ReadBit, Bit *WriteBit) {

  if (InSubCycle(1)) {
    loadMirFromControlStore();
  } else if (InSubCycle(2)) {
    decodeField_A(ABits);
    decodeField_B(BBits);
  } else if (InSubCycle(4)) {
    decodeField_C(CBits);
    loadMicroProgramCounter(NBit, ZBit);
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
static int busRegister(FourBits RField) {
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
static void decodeField_Reg(FourBits RField, DataBusType Field) {
  char str[] = BIT_STRING_ZERO;

  str[busRegister(RField)] = ONE;

  strcpy(Field, str);
}
static void decodeField_A(DataBusType ABits) {
  FourBits AField = {mir[20], mir[21], mir[22], mir[23]};
  decodeField_Reg(AField, ABits);
}
static void decodeField_B(DataBusType BBits) {
  FourBits BField = {mir[16], mir[17], mir[18], mir[19]};
  decodeField_Reg(BField, BBits);
}
static void decodeField_C(DataBusType CBits) {
  FourBits CField = {mir[12], mir[13], mir[14], mir[15]};

  if (mir[11] == ONE)
    decodeField_Reg(CField, CBits);
  else
    strcpy(CBits, BIT_STRING_ZERO);
}
static void loadMirFromControlStore(void) {
  int i;

  for (i = 0; i < MICRO_WORD_SIZE - 1; ++i)
    mir[i] = prom.memBlock[prom.pc][i];
}
static char determineMmux(Bit NBit, Bit ZBit) {
  if ((mir[1] == ONE && mir[2] == ONE) ||
      (mir[1] == ONE && mir[2] == ZERO && ZBit == ONE) ||
      (mir[1] == ZERO && mir[2] == ONE && NBit == ONE))
    return ONE;

  return ZERO;
}
static int convertToCardinal(Bit *Addr, int numBits) {
  int i, sum;

  for (i = sum = 0; i < numBits; ++i) {
    sum *= 2;
    if (Addr[i] == ONE)
      sum += 1;
  }
  return sum;
}
static void loadMicroProgramCounter(Bit NBit, Bit ZBit) {
  if (determineMmux(NBit, ZBit) == ZERO)
    prom.pc += 1;
  else
    prom.pc = convertToCardinal(mir + 24, 8);
}
