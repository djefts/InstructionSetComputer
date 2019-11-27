//
// Created by David Jefts on 2019-11-21.
//

#ifndef INSTRUCTIONSETCOMPUTER_INSTRUCTION_SET_H
#define INSTRUCTIONSETCOMPUTER_INSTRUCTION_SET_H

/***** MATHEMATICAL AND LOGICAL OPERATIONS *****/
int AND(int source, int destination);
int OR(int input1, int input2);
int XOR(int input1, int input2);
int ADD(int input1, int input2);
int SUB(int input1, int input2);
int INC(int input1, int input2);
int DEC(int input1, int input2);
int NOT(int input1, int input2);

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
