//  DEFINE GUARD
#ifndef MIC1_ALU_H
#define MIC1_ALU_H

//  INCLUDES
#include <strings.h>
#include "globals.h"

//  DECLARATIONS

/**
 *  Performs binary addition of the left and right operands and stores them in
 *  the alu output.
 *
 *  @name Add
 *  @param <DataBusType> leftOp       The address of the Left operand Bit String
 *  @param <DataBusType> rightOp      The address of the Right operand Bit String
 *  @param <DataBusType> aluOutput  The address of the Alu output bit string
 */
void Add(DataBusType leftOp, DataBusType rightOp, DataBusType aluOutput);
/**
 *  Performs bitwise And of the left and right operands and stores them in
 *  the alu output.
 *
 *  @name And
 *  @param <DataBusType> leftOp     The address of the Left operand Bit String
 *  @param <DataBusType> rightOp    The address of the Right operand Bit String
 *  @param <DataBusType> aluOutput  The address of the Alu output bit string
 */
void And(DataBusType leftOp, DataBusType rightOp, DataBusType aluOutput);
/**
 *  Performs bit inversion of the left operands and stores them in the alu
 *  output.
 *
 *  @name NotA
 *  @param <DataBusType> leftOp     The address of the Left operand Bit String
 *  @param <DataBusType> aluOutput  The address of the Alu output bit string
 */
void NotA(DataBusType leftOp, DataBusType aluOutput);
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
                 DataBusType aluOutput, Bit *nBit, Bit *zBit);

//  END DEFINE GUARD
#endif