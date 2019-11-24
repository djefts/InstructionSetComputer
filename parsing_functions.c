//
// Created by David Jefts on 2019-11-21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Headers/parsing_functions.h"

void parse_instruction(char *opcode, char *data) {
    if(strcmp(opcode, "00011000") == 0) {
        /* NOOP */
        return;
    }
    
    if(strcmp(opcode, "00011001") == 0) {
        /* HALT */
        return;
    }
    
    switch(opcode[0]) {
        case '0': {
            /* MEMORY / BRANCH OPERATIONS */
            char instr[4];
            memcpy(instr, &opcode[1], 3);
            instr[3] = '\0';
            printf("Instr: %s\n", instr);
            
            if(strcmp(instr, "000") == 0) {
                /* MEMORY OPERATIONS */
                char method[3];
                memcpy(method, &opcode[1], 2);
                method[2] = '\0';
                printf("Method: %s\n", method);
                if(strcmp(method, "00") == 0) {
                    /* INDIRECT ADDRESSING MODE*/
                    break;
                } else if(strcmp(method, "01") == 0) {
                    /* DIRECT ADDRESSING MODE */
                    switch(opcode[5]) {
                        case '0':
                            // ACC
                            break;
                        case '1':
                            // MAR
                            break;
                    }
                } else if(strcmp(method, "10") == 0) {
                    /* REGISTER INDIRECT ADDRESSING MODE */
                    break;
                }
            }
            
            break;
        }
        case '1': {
            /* MATHEMATICAL OR LOGICAL OPERATIONS */
            printf("");
            char instr[4];
            memcpy(instr, &opcode[1], 3);
            instr[3] = '\0';
            
            printf("Instr: %s\n", instr);
            break;
        }
        default: {
            printf("There is no such thing as a number not equal to 0 or 1. \'%c\'", opcode[0]);
            exit(1);
        }
    }
}

int num_data_bits(char *opcode) {
    if(strcmp(opcode, "00011000") == 0) {
        /* NOOP */
        return 0;
    }
    
    if(strcmp(opcode, "00011001") == 0) {
        /* HALT */
        return -1;
    }
    
    switch(opcode[0]) {
        case '0': {
            char instr[4];
            memcpy(instr, &opcode[1], 3);
            instr[3] = '\0';
            
            if(strcmp(instr, "000") == 0) {
                /* MEMORY OPERATIONS */
                char method[3];
                memcpy(method, &opcode[6], 2);
                method[2] = '\0';
                
                printf("\tMemory Operation - ");
                if(strcmp(method, "00") == 0) {
                    /* INDIRECT ADDRESSING MODE*/
                    printf("Indirect Addressing\n");
                    return 16;
                } else if(strcmp(method, "01") == 0) {
                    /* DIRECT ADDRESSING MODE */
                    switch(opcode[5]) {
                        case '0':
                            // ACC
                            printf("Direct Addressing into ACC\n");
                            return 8;
                        case '1':
                            // MAR
                            printf("Direct Addressing into MAR\n");
                            return 16;
                    }
                } else if(strcmp(method, "10") == 0) {
                    /* REGISTER INDIRECT ADDRESSING MODE */
                    printf("Register Indirect Addressing\n");
                    return 0;
                } else {
                    printf("\'%s\' IS NOT A VALID ADDRESSING MODE FOR MEMORY OPERATIONS", method);
                    exit(1);
                }
            }
            break;
        }
        case '1': {
            /* MATHEMATICAL OR LOGICAL OPERATIONS */
            printf("\tMathematical Operation - ");
            int bytes_needed = 0;
            
            // determine if destination is memory
            char dest[3];
            memcpy(dest, &opcode[4], 2);
            dest[2] = '\0';
            if(strcmp(dest, "11") == 0) {
                printf("Into Memory");
                bytes_needed += 2;
            }
            // determine if source is constant or memory
            char src[3];
            memcpy(src, &opcode[6], 2);
            src[2] = '\0';
            if(strcmp(src, "10") == 0) {
                printf("From Constant");
                bytes_needed += 1;
            } else if(strcmp(src, "11") == 0) {
                printf("From Memory");
                bytes_needed += 2;
            }
            
            printf("\n");
            return bytes_needed * 8;
        }
        default: {
            printf("There is no such thing as a number not equal to 0 or 1. \'%c\'", opcode[0]);
            exit(1);
        }
    }
    
    return 0;
}

unsigned char hex_char_to_int(unsigned char hex) {
    /**
     * @return A HEX UNSIGNED CHARACTER
     */
    switch(hex) {
        case '0':
            return 0x0;
        case '1':
            return 0x1;
        case '2':
            return 0x2;
        case '3':
            return 0x3;
        case '4':
            return 0x4;
        case '5':
            return 0x5;
        case '6':
            return 0x6;
        case '7':
            return 0x7;
        case '8':
            return 0x8;
        case '9':
            return 0x9;
        case 'a':
            return 0xa;
        case 'b':
            return 0xb;
        case 'c':
            return 0xc;
        case 'd':
            return 0xd;
        case 'e':
            return 0xe;
        case 'f':
            return 0xf;
        default:
            printf("ERROR IN HEX CHAR TO INT METHOD\n");
            printf("\"%x\" or \"%c\" IS NOT A VALID HEXADECIMAL VALUE", hex, hex);
            exit(1);
    }
}

void hex_byte_to_binary(unsigned char hex, char *byte) {
    /**
     * @return A STRING BINARY NUMBER
     */
    char *nibble1 = nibble_to_binary(hex / 16);
    char *nibble2 = nibble_to_binary(hex % 16);
    snprintf(byte, 9, "%s%s", nibble1, nibble2);  // 8 bits + null terminator
    // printf("\t%02x = %s\n", hex, byte);
}

char *nibble_to_binary(unsigned char hex) {
    switch(hex) {
        case 0x0:
            return "0000";
        case 0x1:
            return "0001";
        case 0x2:
            return "0010";
        case 0x3:
            return "0011";
        case 0x4:
            return "0100";
        case 0x5:
            return "0101";
        case 0x6:
            return "0110";
        case 0x7:
            return "0111";
        case 0x8:
            return "1000";
        case 0x9:
            return "1001";
        case 0xa:
            return "1010";
        case 0xb:
            return "1011";
        case 0xc:
            return "1100";
        case 0xd:
            return "1101";
        case 0xe:
            return "1110";
        case 0xf:
            return "1111";
        default:
            printf("ERROR IN HEX VALUE TO BINARY METHOD\n");
            printf("\"%x\" or \"%c\" IS NOT A VALID HEXADECIMAL VALUE", hex, hex);
            exit(1);
    }
}