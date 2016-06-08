//  INCLUDES
#include "alu.h"

/**
 *  Performs binary addition of the left and right operands and stores them in
 *  the alu output.
 *
 *  @name Add
 *  @param <DataBusType> leftOp     The address of the Left operand Bit String
 *  @param <DataBusType> rightOp    The address of the Right operand Bit String
 *  @param <DataBusType> aluOutput  The address of the Alu output bit string
 */
void Add(DataBusType leftOp, DataBusType rightOp, DataBusType aluOutput) {
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
 *  @name And
 *  @param <DataBusType> leftOp     The address of the Left operand Bit String
 *  @param <DataBusType> rightOp    The address of the Right operand Bit String
 *  @param <DataBusType> aluOutput  The address of the Alu output bit string
 */
void And(DataBusType leftOp, DataBusType rightOp, DataBusType aluOutput) {
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
 *  @name NotA
 *  @param <DataBusType> leftOp     The address of the Left operand Bit String
 *  @param <DataBusType> aluOutput  The address of the Alu output bit string
 */
void NotA(DataBusType leftOp, DataBusType aluOutput) {
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
/**
 *  Performs alu operations, by reading the alubit code to determine what action
 *  to take. Not sure what is happening with the nBits and zBits part of this.
 *
 *  @name ActivateAlu
 *  @param <DataBusType> leftOp     The address of the Left operand Bit String
 *  @param <DataBusType> rightOp    The address of the Right operand Bit String
 *  @param <TwoBits>     aluBits    The alu opcode bits
 *  @param <DataBusType> aluOutput  The address of the Alu output bit string
 *  @param <Bit *>       nBit       TODO
 *  @param <Bit *>       zBit       TODO
 */
void ActivateAlu(DataBusType leftOp, DataBusType rightOp, TwoBits aluBits,
                 DataBusType aluOutput, Bit *nBit, Bit *zBit) {
  //  VARIABLES
  int i;

  //  Check the alu bit instructions to determine the operation.
  if (aluBits[0] == ZERO && aluBits[1] == ZERO) {
    //  00
    Add(leftOp, rightOp, aluOutput);
  } else if (aluBits[0] == ZERO && aluBits[1] == ONE) {
    //  01
    And(leftOp, rightOp, aluOutput);
  } else if (aluBits[0] == ONE && aluBits[1] == ZERO) {
    //  10
    strcpy(aluOutput, leftOp);
  } else if (aluBits[0] == ONE && aluBits[1] == ONE) {
    //  11
    NotA(leftOp, aluOutput);
  }

  //  TODO COMMENT HERE
  *nBit = aluOutput[0];

  //  TODO Comment here
  if (strchr(aluOutput, ONE) != NULL)
    *zBit = ZERO;
  else
    *zBit = ONE;
}