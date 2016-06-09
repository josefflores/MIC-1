//  INCLUDES
#include "driver.h"

//  GLOBAL DEFINITIONS
int power2[16] = {1,   2,   4,    8,    16,   32,   64,    128,
                  256, 512, 1024, 2048, 4096, 8192, 16384, 32768};

int polled_io = 0; /* flag for non-blocking input  */

char input_characters[100][80];
char *inbuf;

int input_x = 0, input_y = 0, input_buf = 0;

int original_stdin_channel_flags;
int nonblock_stdin_channel_flags;


int MemorySlot;

DataBusType ProgramCounter = BIT_STRING_ZERO;
DataBusType Accumulator = BIT_STRING_ZERO;
DataBusType StackPointer = BIT_STRING_ZERO;
DataBusType InstructionReg = BIT_STRING_ZERO;
DataBusType TempInstruction = BIT_STRING_ZERO;
DataBusType ARegister = BIT_STRING_ZERO;
DataBusType BRegister = BIT_STRING_ZERO;
DataBusType CRegister = BIT_STRING_ZERO;
DataBusType DRegister = BIT_STRING_ZERO;
DataBusType ERegister = BIT_STRING_ZERO;
DataBusType FRegister = BIT_STRING_ZERO;

Memory_Chip MemoryChip0;
Memory_Chip MemoryChip1;
Memory_Chip MemoryChip2;
Memory_Chip MemoryChip3;



DataBusType ABits;//
DataBusType BBits;//
DataBusType CBits;//
DataBusType ZERORegister;//
DataBusType PositiveONE;//
DataBusType NegativeONE;//
DataBusType Amask;//
DataBusType Smask;//
DataBusType ALatch;//
DataBusType BLatch;//
DataBusType MBR;//
DataBusType AluResult;//
DataBusType ShifterResult;//

AddressBusType MAR;//

Bit NBit;//
Bit ZBit;//
Bit AmuxBit;//
Bit MbrBit;//
Bit MarBit;//

TwoBits AluBits;//
TwoBits ShiftBits;//




//  DRIVER
/**** call sequence:   mic1 promfile_name programfile_name pc sp    ****/
int main(int argc, char **argv) {

  DataBusType Data;
  AddressBusType Address;
  Bit ReadBit;
  Bit WriteBit;
  int ClockCycle, mem_location, ml, i, j, m, col, mem_offset;
  char query[80];
  char mem_loc[17];

  char promfile[80];
  char programfile[80];
  int pc, sp;

  if ((original_stdin_channel_flags = fcntl(0, F_GETFL, 0)) == -1) {
    perror("fnctl failed: ");
    exit(1);
  }

  nonblock_stdin_channel_flags = original_stdin_channel_flags | O_NONBLOCK;

  switch (argc) {
  case 1:
    promfile[0] = STR_END;
    programfile[0] = STR_END;
    pc = -1;
    sp = -1;
    break;
  case 2:
    strcpy(promfile, argv[1]);
    programfile[0] = STR_END;
    pc = -1;
    sp = -1;
    break;
  case 3:
    strcpy(promfile, argv[1]);
    strcpy(programfile, argv[2]);
    pc = -1;
    sp = -1;
    break;
  case 4:
    strcpy(promfile, argv[1]);
    strcpy(programfile, argv[2]);
    pc = atoi(argv[3]);
    sp = -1;
    break;
  case 5:
    strcpy(promfile, argv[1]);
    strcpy(programfile, argv[2]);
    pc = atoi(argv[3]);
    sp = atoi(argv[4]);
    break;
  default:
    fprintf(stderr, "Too many command line arguments, aborting\n");
    exit(2);
  }

  for (i = 0; i < 100; i++) {
    for (j = 0; j < 80; j++)
      input_characters[i][j] = STR_END;
  }

  readProm(promfile);
  InitializeMemory(programfile);
  InitializePCandStackPointer(pc, sp);
  strcpy(Address, "000000000000");
  strcpy(Data, BIT_STRING_ZERO);
  ReadBit = ZERO;
  WriteBit = ZERO;

TAG:
  for (;;) {
    if (polled_io) {
      Set_nonblocking_io();
      if ((inbuf = fgets(&input_characters[input_buf][0], 99, stdin))) {
        input_characters[input_buf][col = strlen(inbuf)] = '\n';
        input_characters[input_buf][col + 1] = STR_END;
        input_buf = (input_buf + 1) % 100;
        polled_io = 0;
        MemoryChip3[1021][14] = ONE;
        MemoryChip3[1021][15] = ZERO;
        Set_blocking_io();
      }
    }

    GeneratePulse();

    ActivateCpu(Address, Data, ReadBit, WriteBit);

    ActivateMemory(Address, Data, ReadBit, WriteBit);

    if ((ReadBit == ONE) && (WriteBit == ONE)) {
      sleep(1);
      Set_blocking_io();
      tcflush(0, TCIFLUSH);
      break;
    }
  }

  DumpRegisters();
  ClockCycle = GetCycle();
  printf("\nTotal cycles   : %d\n\n", ClockCycle);
  tcflush(0, TCIFLUSH); /* dump anything in the input queue */
                        /***********
                            printf("If you would like to examine memory enter  y  if not enter  n: ");
                            gets(query);
                        ***********/
  if (1 || query[0] == 'y' || query[0] == 'Y') {
    while (1) {
      printf("Type decimal address to view memory,  q  to quit or  c  to "
             "continue: ");
      fgets(query, 79, stdin);
      if (query[0] == 'c') {
        printf("\nThe new PC is  : %s\n\n", ProgramCounter);
        resetPromPC();
        resetClockSubCycle();
        goto TAG;
      }
      if (query[0] == 'q' || query[0] == 'Q') {
        printf("MIC-1 emulator finishing, goodbye\n\n");
        exit(1);
      } else {
        ml = mem_location = atoi(query);
        if (mem_location < 0 || mem_location > 4095) {
          printf("BAD LOCATION VALUE, MUST BE BETWEEN 0 and 4095\n");
          continue;
        }
        for (i = 11; i >= 0; i--) {
          if (mem_location >= power2[i]) {
            Address[11 - i] = ONE;
            mem_location -= power2[i];
          } else {
            Address[11 - i] = ZERO;
          }
        }
        Address[12] = STR_END;
        ActivateMemory(Address, mem_loc, ONE, ZERO);

        mem_loc[16] = STR_END;
        printf("     the location %4d has value %16s , or %5d  or signed %6d\n",
               ml, mem_loc, btoi(mem_loc), (short)btoi(mem_loc));
        printf("Type  <Enter>  to continue debugging\nType        q  to "
               "quit\nType        f for forward range\nType        b for "
               "backward range: ");
        fgets(query, 79, stdin);
        if (query[0] == 'q' | query[0] == 'Q') {
          printf("MIC-1 emulator finishing, goodbye\n\n");
          exit(1);
        } else {
          if (query[0] == 'f' || query[0] == 'F') {
            printf("Type the number of forward locations to dump: ");
            fgets(query, 79, stdin);
            mem_offset = atoi(query);
            if (ml + mem_offset > 4091) {
              printf("BAD OFFSET VALUE, GOES BEYOND 4091\n");
              continue;
            }
            /********************** continue here *******/
            for (m = 0; m < mem_offset; m++) {
              mem_location = ml + m + 1;
              for (i = 11; i >= 0; i--) {
                if (mem_location >= power2[i]) {
                  Address[11 - i] = ONE;
                  mem_location -= power2[i];
                } else {
                  Address[11 - i] = ZERO;
                }
              }
              Address[12] = STR_END;
              ActivateMemory(Address, mem_loc, ONE, ZERO);

              mem_loc[16] = STR_END;
              printf("     the location %4d has value %16s , or %5d  or signed "
                     "%6d\n",
                     (ml + m + 1), mem_loc, btoi(mem_loc),
                     (short)btoi(mem_loc));
            }
          } else {
            if (query[0] == 'b' || query[0] == 'B') {
              printf("Type the number of reverse locations to dump: ");
              fgets(query, 79, stdin);
              mem_offset = atoi(query);
              if (ml - mem_offset < 0) {
                printf("BAD OFFSET VALUE, GOES BELOW 0\n");
                continue;
              }
              /********************** continue here *******/
              for (m = 0; m < mem_offset; m++) {
                mem_location = (ml - (m + 1));
                for (i = 11; i >= 0; i--) {
                  if (mem_location >= power2[i]) {
                    Address[11 - i] = ONE;
                    mem_location -= power2[i];
                  } else {
                    Address[11 - i] = '0';
                  }
                }
                Address[12] = STR_END;
                ActivateMemory(Address, mem_loc, ONE, ZERO);

                mem_loc[16] = STR_END;
                printf("     the location %4d has value %16s , or %5d  or "
                       "signed %6d\n",
                       (ml - (m + 1)), mem_loc, btoi(mem_loc),
                       (short)btoi(mem_loc));
              }
            } else
              continue;
          }
        }
        continue;
        /**************************************************************************/
      }
    }
  }
  printf("MIC-1 emulator finishing, goodbye\n\n");
  exit(1);

} /* END Driver */