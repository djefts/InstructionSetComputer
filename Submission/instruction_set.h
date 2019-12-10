//
// Created by David Jefts on 2019-11-21.
//

#ifndef INSTRUCTIONSETCOMPUTER_INSTRUCTION_SET_H
#define INSTRUCTIONSETCOMPUTER_INSTRUCTION_SET_H

/***** MATHEMATICAL AND LOGICAL OPERATIONS *****/
void AND(uint8_t *source, uint8_t *destination);
void OR(uint8_t *source, uint8_t *destination);
void XOR(uint8_t *source, uint8_t *destination);
void ADD(uint8_t *source, uint8_t *destination);
void SUB(uint8_t *source, uint8_t *destination);
void INC(uint8_t *destination);
void DEC(uint8_t *destination);
void NOT(uint8_t *destination);
void AND_MAR(uint8_t *source, uint16_t *destination);
void OR_MAR(uint8_t *source, uint16_t *destination);
void XOR_MAR(uint8_t *source, uint16_t *destination);
void ADD_MAR(uint8_t *source, uint16_t *destination);
void SUB_MAR(uint8_t *source, uint16_t *destination);
void INC_MAR(uint16_t *destination);
void DEC_MAR(uint16_t *destination);
void NOT_MAR(uint16_t *destination);

/***** MEMORY OPERATIONS *****/
int STOR(int input1, int input2);
int LOAD(int input1, int input2);

/***** BRANCHES / JUMPS *****/
void BRA(unsigned long *PC, unsigned int data);
void BRZ(unsigned long *PC, uint8_t *ACC, unsigned int data);
void BNE(unsigned long *PC, uint8_t *ACC, unsigned int data);
void BLT(unsigned long *PC, uint8_t *ACC, unsigned int data);
void BLE(unsigned long *PC, uint8_t *ACC, unsigned int data);
void BGT(unsigned long *PC, uint8_t *ACC, unsigned int data);
void BGE(unsigned long *PC, uint8_t *ACC, unsigned int data);

#endif //INSTRUCTIONSETCOMPUTER_INSTRUCTION_SET_H
