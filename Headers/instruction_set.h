//
// Created by David Jefts on 2019-11-21.
//

#ifndef INSTRUCTIONSETCOMPUTER_INSTRUCTION_SET_H
#define INSTRUCTIONSETCOMPUTER_INSTRUCTION_SET_H

/***** MATHEMATICAL AND LOGICAL OPERATIONS *****/
void AND(unsigned char *source, unsigned char *destination);
void OR(unsigned char *source, unsigned char *destination);
void XOR(unsigned char *source, unsigned char *destination);
void ADD(unsigned char *source, unsigned char *destination);
void SUB(unsigned char *source, unsigned char *destination);
void INC(unsigned char *destination);
void DEC(unsigned char *destination);
void NOT(unsigned char *destination);

/***** MEMORY OPERATIONS *****/
int STOR(int input1, int input2);
int LOAD(int input1, int input2);

/***** BRANCHES / JUMPS *****/
int BRA(int input1, int input2);
int BRZ(int input1, int input2);
int BNE(int input1, int input2);
int BLT(int input1, int input2);
int BLE(int input1, int input2);
int BGT(int input1, int input2);
int BGE(int input1, int input2);

#endif //INSTRUCTIONSETCOMPUTER_INSTRUCTION_SET_H
