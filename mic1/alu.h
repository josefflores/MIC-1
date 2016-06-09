//  INCLUDES
#include <strings.h>

#include "globals.h"

//  DECLARATIONS
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
                        Bit *zBit);
/**
 *  Passes an input through to the alu output.
 *
 *  @function passThrough
 *  @param <DataBusType> leftOp     The address of the Left operand Bit String
 *  @param <DataBusType> aluOutput  The address of the Alu output bit string
 */
static void passThrough(DataBusType leftOp, DataBusType aluOutput);
/**
 *  Performs binary addition of the left and right operands and stores them in
 *  the alu output.
 *
 *  @function add
 *  @param <DataBusType> leftOp       The address of the Left operand Bit String
 *  @param <DataBusType> rightOp      The address of the Right operand Bit
 * String
 *  @param <DataBusType> aluOutput  The address of the Alu output bit string
 */
static void add(DataBusType leftOp, DataBusType rightOp, DataBusType aluOutput);
/**
 *  Performs bitwise And of the left and right operands and stores them in
 *  the alu output.
 *
 *  @function and
 *  @param <DataBusType> leftOp     The address of the Left operand Bit String
 *  @param <DataBusType> rightOp    The address of the Right operand Bit String
 *  @param <DataBusType> aluOutput  The address of the Alu output bit string
 */
static void and(DataBusType leftOp, DataBusType rightOp, DataBusType aluOutput);
/**
 *  Performs bit inversion of the left operand and stores the result in the alu
 *  output.
 *
 *  @function notA
 *  @param <DataBusType> leftOp     The address of the Left operand Bit String
 *  @param <DataBusType> aluOutput  The address of the Alu output bit string
 */
static void notA(DataBusType leftOp, DataBusType aluOutput);