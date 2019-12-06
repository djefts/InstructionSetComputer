//
// Created by David Jefts on 2019-11-21.
//

#ifndef INSTRUCTIONSETCOMPUTER_INSTRUCTION_SET_H
#define INSTRUCTIONSETCOMPUTER_INSTRUCTION_SET_H

/***** MATHEMATICAL AND LOGICAL OPERATIONS *****/
void AND(u_int8_t *source, u_int8_t *destination);
void OR(u_int8_t *source, u_int8_t *destination);
void XOR(u_int8_t *source, u_int8_t *destination);
void ADD(u_int8_t *source, u_int8_t *destination);
void SUB(u_int8_t *source, u_int8_t *destination);
void INC(u_int8_t *destination);
void DEC(u_int8_t *destination);
void NOT(u_int8_t *destination);
void AND_MAR(u_int8_t *source, u_int16_t *destination);
void OR_MAR(u_int8_t *source, u_int16_t *destination);
void XOR_MAR(u_int8_t *source, u_int16_t *destination);
void ADD_MAR(u_int8_t *source, u_int16_t *destination);
void SUB_MAR(u_int8_t *source, u_int16_t *destination);
void INC_MAR(u_int16_t *destination);
void DEC_MAR(u_int16_t *destination);
void NOT_MAR(u_int16_t *destination);

/***** MEMORY OPERATIONS *****/
int STOR(int input1, int input2);
int LOAD(int input1, int input2);

/***** BRANCHES / JUMPS *****/
void BRA(unsigned long *PC, unsigned int data);
void BRZ(unsigned long *PC, u_int8_t *ACC, unsigned int data);
void BNE(unsigned long *PC, u_int8_t *ACC, unsigned int data);
void BLT(unsigned long *PC, u_int8_t *ACC, unsigned int data);
void BLE(unsigned long *PC, u_int8_t *ACC, unsigned int data);
void BGT(unsigned long *PC, u_int8_t *ACC, unsigned int data);
void BGE(unsigned long *PC, u_int8_t *ACC, unsigned int data);

#endif //INSTRUCTIONSETCOMPUTER_INSTRUCTION_SET_H
