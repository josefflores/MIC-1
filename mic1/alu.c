//  INCLUDES
#include "alu.h"

//  DEFINITIONS
/**
 *  Performs alu operations, by reading the alubit code to determine what action
 *  to take. Not sure what is happening with the nBits and zBits part of this.
 *
 *  @function activateAlu
 *  @param <DataBusType> leftOp     The address of the Left operand Bit String
 *  @param <DataBusType> rightOp    The address of the Right operand Bit String
 *  @param <TwoBits>     aluBits    The alu opcode bits
 *  @param <DataBusType> aluOutput  The address of the Alu output bit string
 *  @param <Bit *>       nBit       TODO
 *  @param <Bit *>       zBit       TODO
 */
extern void activateAlu(DataBusType leftOp, DataBusType rightOp,
                        TwoBits aluBits, DataBusType aluOutput, Bit *nBit,
                        Bit *zBit) {
  //  VARIABLES
  int i;

  //  Check the alu bit instructions to determine the operation.
  if (aluBits[0] == ZERO && aluBits[1] == ZERO) {
    //  00 : A + B
    add(leftOp, rightOp, aluOutput);
  } else if (aluBits[0] == ZERO && aluBits[1] == ONE) {
    //  01 : A and B
    and(leftOp, rightOp, aluOutput);
  } else if (aluBits[0] == ONE && aluBits[1] == ZERO) {
    //  10 : A
    passThrough(leftOp, aluOutput);
  } else if (aluBits[0] == ONE && aluBits[1] == ONE) {
    //  11 : ~A
    notA(leftOp, aluOutput);
  }

  //  If aluOutput[0] is on, then the nBit should be on
  *nBit = aluOutput[0];

  //  If any bit is on, then turn off the zBit otherwise turn it on
  if (strchr(aluOutput, ONE) != NULL)
    *zBit = ZERO;
  else
    *zBit = ONE;
}
/**
 *  Passes an input through to the alu output.
 *
 *  @function passThrough
 *  @param <DataBusType> leftOp     The address of the Left operand Bit String
 *  @param <DataBusType> aluOutput  The address of the Alu output bit string
 */
static void passThrough(DataBusType leftOp, DataBusType aluOutput) {
  strcpy(leftOp, aluOutput);
}
/**
 *  Performs binary addition of the left and right operands and stores them in
 *  the alu output.
 *
 *  @function add
 *  @param <DataBusType> leftOp     The address of the Left operand Bit String
 *  @param <DataBusType> rightOp    The address of the Right operand Bit String
 *  @param <DataBusType> aluOutput  The address of the Alu output bit string
 */
static void add(DataBusType leftOp, DataBusType rightOp,
                DataBusType aluOutput) {
  //  VARIABLES
  int i;            //  Loop Counter
  Bit carry = ZERO; //  Initialize the carry bit to ZERO

  //  Iterate through all the bits.
  for (i = DATA_WORD_SIZE - 1; i >= 0; --i) {
    /**
     *  Perform binary addition with a carry bit, the following are cases for
     *  every scenario
     */
    if (leftOp[i] == ZERO && rightOp[i] == ZERO && carry == ZERO) {
      //  All bits are 1
      aluOutput[i] = ZERO;
      carry = ZERO;
    } else if (leftOp[i] == ONE && rightOp[i] == ONE && carry == ONE) {
      // All bits are 0
      aluOutput[i] = ONE;
      carry = ONE;
    } else if ((leftOp[i] == ONE && rightOp[i] == ZERO && carry == ZERO) ||
               (leftOp[i] == ZERO && rightOp[i] == ONE && carry == ZERO) ||
               (leftOp[i] == ZERO && rightOp[i] == ZERO && carry == ONE)) {
      // One bit is 1 and two bits are 0
      aluOutput[i] = ONE;
      carry = ZERO;
    } else {
      //  One bit is 0 and two bits are 1
      aluOutput[i] = ZERO;
      carry = ONE;
    }
  }
}
/**
 *  Performs bitwise And of the left and right operands and stores them in
 *  the alu output.
 *
 *  @function and
 *  @param <DataBusType> leftOp     The address of the Left operand Bit String
 *  @param <DataBusType> rightOp    The address of the Right operand Bit String
 *  @param <DataBusType> aluOutput  The address of the Alu output bit string
 */
static void and(DataBusType leftOp, DataBusType rightOp,
                DataBusType aluOutput) {
  //  VARIABLES
  int i;

  //  Iterate through all the bits.
  for (i = 0; i < DATA_WORD_SIZE - 1; ++i) {
    /**
     *  Perform 'and' operation on each pair of operands at the given index
     *  storing result in the alu output.
     */
    if (leftOp[i] == ONE && rightOp[i] == ONE)
      aluOutput[i] = ONE;
    else
      aluOutput[i] = ZERO;
  }
}
/**
 *  Performs bit inversion of the left operands and stores them in the alu
 *  output.
 *
 *  @function notA
 *  @param <DataBusType> leftOp     The address of the Left operand Bit String
 *  @param <DataBusType> aluOutput  The address of the Alu output bit string
 */
static void notA(DataBusType leftOp, DataBusType aluOutput) {
  //  VARIABLES
  int i;

  //  Iterate through all the bits.
  for (i = 0; i < DATA_WORD_SIZE - 1; ++i) {
    //  Invert the bit at the given index storing result in the alu output
    if (leftOp[i] == ONE)
      aluOutput[i] = ZERO;
    else
      aluOutput[i] = ONE;
  }
}
