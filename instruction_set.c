//
// Created by David Jefts on 2019-11-21.
//

#include <stdio.h>
#include "Headers/instruction_set.h"


/***** MATHEMATICAL AND LOGICAL OPERATIONS *****/
void AND(u_int8_t *source, u_int8_t *destination) {
    printf("\tPERFORMING BITWISE AND OPERATION\n\t\tDestination 0x%x --> ", *destination);
    *destination = *destination & *source;
    printf("0x%x\n", *destination);
}

void OR(u_int8_t *source, u_int8_t *destination) {
    printf("\tPERFORMING BITWISE OR OPERATION\n\t\tDestination 0x%x --> ", *destination);
    *destination = *destination | *source;
    printf("0x%x\n", *destination);
}

void XOR(u_int8_t *source, u_int8_t *destination) {
    printf("\tPERFORMING BITWISE XOR OPERATION\n\t\tDestination 0x%x --> ", *destination);
    *destination = *destination ^ *source;
    printf("0x%x\n", *destination);
}

void ADD(u_int8_t *source, u_int8_t *destination) {
    printf("\tPERFORMING ADDITION OPERATION\n\t\tDestination 0x%x --> ", *destination);
    *destination = *destination + *source;
    printf("0x%x\n", *destination);
}

void SUB(u_int8_t *source, u_int8_t *destination) {
    printf("\tPERFORMING SUBTRACTION OPERATION\n\t\tDestination 0x%x --> ", *destination);
    *destination = *destination - *source;
    printf("0x%x\n", *destination);
}

void INC(u_int8_t *destination) {
    printf("\tPERFORMING INCREMENT OPERATION\n\t\tDestination 0x%x --> ", *destination);
    *destination += 0x1;
    printf("0x%x\n", *destination);
}

void DEC(u_int8_t *destination) {
    printf("\tPERFORMING DECREMENT OPERATION\n\t\tDestination 0x%x --> ", *destination);
    *destination -= 0x1;
    printf("0x%x\n", *destination);
}

void NOT(u_int8_t *destination) {
    printf("\tPERFORMING BITWISE NOT OPERATION\n\t\tDestination 0x%x --> ", *destination);
    *destination = ~*destination;
    printf("0x%x\n", *destination);
}

/***** MATHEMATICAL AND LOGICAL OPERATIONS MODIFIED FOR MAR REGISTER *****/
void AND_MAR(u_int8_t *source, u_int16_t *destination) {
    printf("\tPERFORMING BITWISE AND OPERATION\n\t\tDestination 0x%x --> ", *destination);
    *destination = *destination & *source;
    printf("0x%x\n", *destination);
}

void OR_MAR(u_int8_t *source, u_int16_t *destination) {
    printf("\tPERFORMING BITWISE OR OPERATION\n\t\tDestination 0x%x --> ", *destination);
    *destination = *destination | *source;
    printf("0x%x\n", *destination);
}

void XOR_MAR(u_int8_t *source, u_int16_t *destination) {
    printf("\tPERFORMING BITWISE XOR OPERATION\n\t\tDestination 0x%x --> ", *destination);
    *destination = *destination ^ *source;
    printf("0x%x\n", *destination);
}

void ADD_MAR(u_int8_t *source, u_int16_t *destination) {
    printf("\tPERFORMING ADDITION OPERATION\n\t\tDestination 0x%x --> ", *destination);
    *destination = *destination + *source;
    printf("0x%x\n", *destination);
}

void SUB_MAR(u_int8_t *source, u_int16_t *destination) {
    printf("\tPERFORMING SUBTRACTION OPERATION\n\t\tDestination 0x%x --> ", *destination);
    *destination = *destination - *source;
    printf("0x%x\n", *destination);
}

void INC_MAR(u_int16_t *destination) {
    printf("\tPERFORMING INCREMENT OPERATION\n\t\tDestination 0x%x --> ", *destination);
    *destination += 0x1;
    printf("0x%x\n", *destination);
}

void DEC_MAR(u_int16_t *destination) {
    printf("\tPERFORMING DECREMENT OPERATION\n\t\tDestination 0x%x --> ", *destination);
    *destination -= 0x1;
    printf("0x%x\n", *destination);
}

void NOT_MAR(u_int16_t *destination) {
    printf("\tPERFORMING BITWISE NOT OPERATION\n\t\tDestination 0x%x --> ", *destination);
    *destination = ~*destination;
    printf("0x%x\n", *destination);
}

/***** BRANCHES / JUMPS *****/
void BRA(unsigned long *PC, unsigned int data) {
    printf("Setting PC(%lu) to %d\n\t\t", *PC, data);
    *PC = data;
    printf("PC = %lu\n", *PC);
}

void BRZ(unsigned long *PC, u_int8_t *ACC, unsigned int data) {
    if(*ACC == 0) {
        printf("Setting PC(%lu) to %d\n\t\t", *PC, data);
        *PC = data;
        printf("PC = %lu\n", *PC);
    } else {
        printf("ACC = 0x%02x instead of 0. Not branching.\n", *ACC);
    }
}

void BNE(unsigned long *PC, u_int8_t *ACC, unsigned int data) {
    if(*ACC != 0) {
        printf("Setting PC(%lu) to %d\n\t\t", *PC, data);
        *PC = data;
        printf("PC = %lu\n", *PC);
    } else {
        printf("ACC = 0x%02x. Not branching.\n", *ACC);
    }
}

void BLT(unsigned long *PC, u_int8_t *ACC, unsigned int data) {
    int8_t accumulator = *ACC;
    if(accumulator < 0) {
        printf("Setting PC(%lu) to %d\n\t\t", *PC, data);
        *PC = data;
        printf("ACC = %d, PC = %lu\n", accumulator, *PC);
    } else {
        printf("ACC = 0x%02x = %d. Not branching.\n", *ACC, accumulator);
    }
}

void BLE(unsigned long *PC, u_int8_t *ACC, unsigned int data) {
    int8_t accumulator = *ACC;
    if(accumulator <= 0) {
        printf("Setting PC(%lu) to %d\n\t\t", *PC, data);
        *PC = data;
        printf("ACC = %d, PC = %lu\n", accumulator, *PC);
    } else {
        printf("ACC = 0x%02x = %d. Not branching.\n", *ACC, accumulator);
    }
}

void BGT(unsigned long *PC, u_int8_t *ACC, unsigned int data) {
    int8_t accumulator = *ACC;
    if(accumulator > 0) {
        printf("Setting PC(%lu) to %d\n\t\t", *PC, data);
        *PC = data;
        printf("ACC = %d, PC = %lu\n", accumulator, *PC);
    } else {
        printf("ACC = 0x%02x = %d. Not branching.\n", *ACC, accumulator);
    }
}

void BGE(unsigned long *PC, u_int8_t *ACC, unsigned int data) {
    int8_t accumulator = *ACC;
    if(accumulator >= 0) {
        printf("Setting PC(%lu) to %d\n\t\t", *PC, data);
        *PC = data;
        printf("ACC = %d, PC = %lu\n", accumulator, *PC);
    } else {
        printf("ACC = 0x%02x = %d. Not branching.\n", *ACC, accumulator);
    }
}