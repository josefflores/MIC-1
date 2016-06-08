#include "memory.h"

void ActivateMemoryChip0(ChipRange Offset, DataBusType Data, Bit ReadBit,
                         Bit WriteBit) {
  int I;

  if (ReadBit == ONE)
    for (I = 0; I < DATA_WORD_SIZE - 1; I++)
      Data[I] = MemoryChip0[Offset][I];
  else if (WriteBit == ONE)
    for (I = 0; I < DATA_WORD_SIZE - 1; I++)
      MemoryChip0[Offset][I] = Data[I];
}

void ActivateMemoryChip1(ChipRange Offset, DataBusType Data, Bit ReadBit,
                         Bit WriteBit) {
  int I;

  if (ReadBit == ONE)
    for (I = 0; I < DATA_WORD_SIZE - 1; I++)
      Data[I] = MemoryChip1[Offset][I];
  else if (WriteBit == ONE)
    for (I = 0; I < DATA_WORD_SIZE - 1; I++)
      MemoryChip1[Offset][I] = Data[I];
}

void ActivateMemoryChip2(ChipRange Offset, DataBusType Data, Bit ReadBit,
                         Bit WriteBit) {
  int I;

  if (ReadBit == ONE)
    for (I = 0; I < DATA_WORD_SIZE - 1; I++)
      Data[I] = MemoryChip2[Offset][I];
  else if (WriteBit == ONE)
    for (I = 0; I < DATA_WORD_SIZE - 1; I++)
      MemoryChip2[Offset][I] = Data[I];
}

void ActivateMemoryChip3(ChipRange Offset, DataBusType Data, Bit ReadBit,
                         Bit WriteBit) {
  static int subcycles = 0, sub1020 = 0, sub1021 = 0;
  int I; /* loop counter index */
  char print_char;
  char test_char;

  subcycles++;
  if (ReadBit == ONE) {
    switch (Offset) {
    default:
      for (I = 0; I < DATA_WORD_SIZE - 1; I++)
        Data[I] = MemoryChip3[Offset][I];
      break;

    case 1022:
      for (I = 0; I < DATA_WORD_SIZE - 1; I++)
        Data[I] = MemoryChip3[Offset][I];
      break;

    case 1021:
      for (I = 0; I < DATA_WORD_SIZE - 1; I++)
        Data[I] = MemoryChip3[Offset][I];
      break;

    case 1020:
      if ((sub1021++ % 8 == 0) && MemoryChip3[1021][14] == '1' &&
          MemoryChip3[1021][12] == '1') {
        True_ascii_to_mem_ascii(&MemoryChip3[1020][0],
                                &input_characters[input_x][input_y]);
        if (input_characters[input_x][++input_y] == '\0') {
          input_y = 0;
          input_characters[input_x][input_y] = '\0';
          input_x = (input_x + 1) % 100;
          if (input_characters[input_x][input_y] == '\0') {
            MemoryChip3[1021][15] = '1';
            MemoryChip3[1021][14] = '0';
            polled_io = 1;
          } else {
            MemoryChip3[1021][15] = '0';
            MemoryChip3[1021][14] = '1';
            polled_io = 0;
          }
        }
      }

      for (I = 0; I < DATA_WORD_SIZE - 1; I++)
        Data[I] = MemoryChip3[Offset][I];
      break;
    }

  } else if (WriteBit == ONE) {

    switch (Offset) {
    default:
      for (I = 0; I < DATA_WORD_SIZE - 1; I++)
        MemoryChip3[Offset][I] = Data[I];
      break;

    case 1022:
      if (subcycles % 4 == 0 && MemoryChip3[1023][12] == '1' &&
          MemoryChip3[1023][14] == '1') {
        for (I = 0; I < DATA_WORD_SIZE - 1; I++)
          MemoryChip3[Offset][I] = Data[I];
        test_char = btoc(Data);
        write(1, &test_char, 1);
        MemoryChip3[1023][14] = '1';
        MemoryChip3[1023][15] = '0';
      }
      break;

    case 1021:
      if (Data[12] == '1') {
        for (I = 0; I < DATA_WORD_SIZE - 1; I++)
          MemoryChip3[Offset][I] = '0';
        polled_io = 1;
        MemoryChip3[Offset][14] = '0';
        MemoryChip3[Offset][15] = '1';
        MemoryChip3[Offset][12] = '1';
      } else {
        for (I = 0; I < DATA_WORD_SIZE - 1; I++)
          MemoryChip3[Offset][I] = '0';
        polled_io = 0;
      }
      break;

    case 1023:
      if (Data[12] == '1') {
        for (I = 0; I < DATA_WORD_SIZE - 1; I++)
          MemoryChip3[Offset][I] = '0';
        MemoryChip3[Offset][14] = '1';
        MemoryChip3[Offset][15] = '0';
        MemoryChip3[Offset][12] = '1';
      } else {
        for (I = 0; I < DATA_WORD_SIZE - 1; I++)
          MemoryChip3[Offset][I] = '0';
        polled_io = 0;
      }
      break;

    case 1020:
      break;
    }
  }
}

int ComputeOffset(AddressBusType Address) {

  int m;      /* loop counter index            */
  int temp;   /* temp decimal for calculations */
  int Offset; /* decimal equivalent of binary  */

  Offset = 0;

  for (m = 2; m < (ADDR_WORD_SIZE - 1); m++) /*   10 bit offset  */
  {
    if (Address[m] == '1')
      temp = 1;
    else
      temp = 0;

    Offset = (2 * Offset) + temp;
  }

  return (Offset);
}

int ComputeChipSelect(Bit Address0, Bit Address1) {

  if ((Address0 == ZERO) && (Address1 == ZERO))
    return (0);
  else if ((Address0 == ZERO) && (Address1 == ONE))
    return (1);
  else if ((Address0 == ONE) && (Address1 == ZERO))
    return (2);
  else
    return (3);
}

void ActivateMemory(AddressBusType Address, DataBusType Data, Bit ReadBit,
                    Bit WriteBit) {
  int Offset = ComputeOffset(Address);

  switch (ComputeChipSelect(Address[0], Address[1])) {
  case 0:
    ActivateMemoryChip0(Offset, Data, ReadBit, WriteBit);
    break;
  case 1:
    ActivateMemoryChip1(Offset, Data, ReadBit, WriteBit);
    break;
  case 2:
    ActivateMemoryChip2(Offset, Data, ReadBit, WriteBit);
    break;
  case 3:
    ActivateMemoryChip3(Offset, Data, ReadBit, WriteBit);
    break;
  }
}

void DumpMemory(int From, int To) {

  int MemorySlot;
  int Offset;
  int ChipNumber;

  for (MemorySlot = From; MemorySlot <= To; MemorySlot++) {
    ChipNumber = MemorySlot / MEMORY_CHIP_SIZE;
    Offset = MemorySlot % MEMORY_CHIP_SIZE;

    if (ChipNumber == 0)
      printf("%s", MemoryChip0[Offset]);
    if (ChipNumber == 1)
      printf("%s", MemoryChip1[Offset]);
    if (ChipNumber == 2)
      printf("%s", MemoryChip2[Offset]);
    if (ChipNumber == 3)
      printf("%s", MemoryChip3[Offset]);

    printf("\n");
  }
}

void InitializeMemory(char *program_file) {
  FILE *inputfile, *fopen(); /* pointer to input file  library   */
                             /* function to OPEN file for input  */
  int ChipNumber;
  int Offset;
  int MemorySlot;

  for (MemorySlot = 0; MemorySlot <= 4095; MemorySlot++) {
    ChipNumber = MemorySlot / MEMORY_CHIP_SIZE;
    Offset = MemorySlot % MEMORY_CHIP_SIZE;
    if (ChipNumber == 0)
      strcpy(MemoryChip0[Offset], BIT_STRING_NEG_ONE);
    else if (ChipNumber == 1)
      strcpy(MemoryChip1[Offset], BIT_STRING_NEG_ONE);
    else if (ChipNumber == 2)
      strcpy(MemoryChip2[Offset], BIT_STRING_NEG_ONE);
    else if (ChipNumber == 3)
      strcpy(MemoryChip3[Offset], BIT_STRING_NEG_ONE);
  }

  strcpy(MemoryChip3[1020], BIT_STRING_ZERO);
  strcpy(MemoryChip3[1021], BIT_STRING_ZERO);
  strcpy(MemoryChip3[1022], BIT_STRING_ZERO);
  strcpy(MemoryChip3[1023], BIT_STRING_ZERO);

  /* open program file for loading                */

  if ((inputfile = fopen(program_file, "r")) == NULL) {
    if ((inputfile = fopen("inner.dat", "r")) == NULL) {
      fprintf(stderr, "Can't open Program File, aborting \n");
      exit(2);
    }
  }

  for (MemorySlot = 0; MemorySlot < (MEMORY_CHIP_SIZE * 4); MemorySlot++) {
    ChipNumber = MemorySlot / MEMORY_CHIP_SIZE;
    Offset = MemorySlot % MEMORY_CHIP_SIZE;
    if (ChipNumber == 0)
      if ((fscanf(inputfile, "%s", MemoryChip0[Offset])) == EOF)
        break;
    if (ChipNumber == 1)
      if ((fscanf(inputfile, "%s", MemoryChip1[Offset])) == EOF)
        break;
    if (ChipNumber == 2)
      if ((fscanf(inputfile, "%s", MemoryChip2[Offset])) == EOF)
        break;
    if (ChipNumber == 3)
      if ((fscanf(inputfile, "%s", MemoryChip3[Offset])) == EOF)
        break;
  }

  fprintf(stderr, "Read in %d machine instructions\n", MemorySlot);
  fclose(inputfile);
}

void MemoryRead(int mem_loc, char *mem_val) {
  switch (mem_loc / 1024) {
  case 0:
    strncpy(mem_val, MemoryChip0[mem_loc], 16);
    mem_val[17] = '\0';
    break;
  case 1:
    strncpy(mem_val, MemoryChip1[mem_loc - 1024], 16);
    mem_val[17] = '\0';
    break;
  case 2:
    strncpy(mem_val, MemoryChip2[mem_loc - 2048], 16);
    mem_val[17] = '\0';
    break;
  case 3:
    strncpy(mem_val, MemoryChip3[mem_loc - 3072], 16);
    mem_val[17] = '\0';
    break;
  }
}
