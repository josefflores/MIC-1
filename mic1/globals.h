
//  DEFINE GUARD
#ifndef MIC1_GLOBALS_H
#define MIC1_GLOBALS_H

//  INCLUDES
#include <stdlib.h>
#include <string.h>

//  DEFINES
#define ZERO '0'
#define ONE '1'
#define BLANK ' '
#define STR_END '\0'

#define ADDR_WORD_SIZE 13
#define DATA_WORD_SIZE 17
#define MEMORY_CHIP_SIZE 1024
#define MICRO_WORD_SIZE 33
#define MAX_SIZE 256
#define MICRO_PC_SIZE 9

#define CLOCK_CYCLES 4

#define PC_MAX 2047
#define SP_MAX 4095

#define BIT_STRING_POS_ONE "0000000000000001"
#define BIT_STRING_ZERO "0000000000000000"
#define BIT_STRING_NEG_ONE "1111111111111111"
#define BIT_STRING_A_MASK "0000111111111111"
#define BIT_STRING_S_MASK "0000000011111111"
#define BIT_STRING_SP "0000111110000000"

#define BIN_32768 0x00008000

//  TYPEDEFINES
typedef char AddressBusType[ADDR_WORD_SIZE];
typedef char DataBusType[DATA_WORD_SIZE];

typedef char Bit;
typedef Bit TwoBits[2];
typedef Bit FourBits[5];
typedef Bit EightBits[9];
typedef Bit MicroWord[MICRO_WORD_SIZE];



typedef int ChipRange;

typedef DataBusType Memory_Chip[MEMORY_CHIP_SIZE];

//  END DEFINE GUARD
#endif