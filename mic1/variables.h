//  INCLUDES
#include "globals.h"

//  DECLARATIONS
extern int microPc;
extern int rowCounter;
extern int power2[16];
extern int polled_io;
extern int input_x;
extern int input_y;
extern int input_buf;
extern int original_stdin_channel_flags;
extern int nonblock_stdin_channel_flags;

extern char input_characters[100][80];
extern char *inbuf;

extern Clock Quartz;

extern DataBusType ABits;//
extern DataBusType BBits;//
extern DataBusType CBits;//
extern DataBusType ProgramCounter ;
extern DataBusType Accumulator ;
extern DataBusType StackPointer ;
extern DataBusType InstructionReg;
extern DataBusType TempInstruction;
extern DataBusType ZERORegister;//
extern DataBusType PositiveONE;//
extern DataBusType NegativeONE;//
extern DataBusType Amask;//
extern DataBusType Smask;//
extern DataBusType ARegister;
extern DataBusType BRegister;
extern DataBusType CRegister;
extern DataBusType DRegister;
extern DataBusType ERegister;
extern DataBusType FRegister;
extern DataBusType ALatch;//
extern DataBusType BLatch;//
extern DataBusType MBR;//
extern DataBusType AluResult;//
extern DataBusType ShifterResult;//

extern AddressBusType MAR;//

extern Bit NBit;//
extern Bit ZBit;//
extern Bit AmuxBit;//
extern Bit MbrBit;//
extern Bit MarBit;//

extern TwoBits AluBits;//
extern TwoBits ShiftBits;//

extern MicroWord MIR;                   //
extern MicroWord microMemory[MAX_SIZE]; //

extern Memory_Chip MemoryChip0;
extern Memory_Chip MemoryChip1;
extern Memory_Chip MemoryChip2;
extern Memory_Chip MemoryChip3;

