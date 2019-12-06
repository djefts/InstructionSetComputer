//
// Created by David Jefts on 2019-11-21.
//

#include <stdio.h>
#include "Headers/instruction_set.h"


/***** MATHEMATICAL AND LOGICAL OPERATIONS *****/
void AND(unsigned char *source, unsigned char *destination) {
    printf("\tPERFORMING BITWISE AND OPERATION\n\t\tDestination 0x%x --> ", *destination);
    *destination = *destination & *source;
    printf("0x%x\n", *destination);
}

void OR(unsigned char *source, unsigned char *destination) {
    printf("\tPERFORMING BITWISE OR OPERATION\n\t\tDestination 0x%x --> ", *destination);
    *destination = *destination | *source;
    printf("0x%x\n", *destination);
}

void XOR(unsigned char *source, unsigned char *destination) {
    printf("\tPERFORMING BITWISE XOR OPERATION\n\t\tDestination 0x%x --> ", *destination);
    *destination = *destination ^ *source;
    printf("0x%x\n", *destination);
}

void ADD(unsigned char *source, unsigned char *destination) {
    printf("\tPERFORMING ADDITION OPERATION\n\t\tDestination 0x%x --> ", *destination);
    *destination = *destination + *source;
    printf("0x%x\n", *destination);
}

void SUB(unsigned char *source, unsigned char *destination) {
    printf("\tPERFORMING SUBTRACTION OPERATION\n\t\tDestination 0x%x --> ", *destination);
    *destination = *destination - *source;
    printf("0x%x\n", *destination);
}

void INC(unsigned char *destination) {
    printf("\tPERFORMING INCREMENT OPERATION\n\t\tDestination 0x%x --> ", *destination);
    *destination += 0x1;
    printf("0x%x\n", *destination);
}

void DEC(unsigned char *destination) {
    printf("\tPERFORMING DECREMENT OPERATION\n\t\tDestination 0x%x --> ", *destination);
    *destination -= 0x1;
    printf("0x%x\n", *destination);
}

void NOT(unsigned char *destination) {
    printf("\tPERFORMING BITWISE NOT OPERATION\n\t\tDestination 0x%x --> ", *destination);
    *destination = ~*destination;
    printf("0x%x\n", *destination);
}

/***** BRANCHES / JUMPS *****/
int BRA(int input1, int input2) {
    printf("\tRunning BRA function");
    return 0;
}

int BRZ(int input1, int input2) {
    printf("\tRunning BRZ function");
    return 0;
}

int BNE(int input1, int input2) {
    printf("\tRunning BNE function");
    return 0;
}

int BLT(int input1, int input2) {
    printf("\tRunning BLT function");
    return 0;
}

int BLE(int input1, int input2) {
    printf("\tRunning BLE function");
    return 0;
}

int BGT(int input1, int input2) {
    printf("\tRunning BGT function");
    return 0;
}

int BGE(int input1, int input2) {
    printf("\tRunning BGE function");
    return 0;
}