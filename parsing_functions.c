//
// Created by David Jefts on 2019-11-21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <mach/boolean.h>
#include "Headers/parsing_functions.h"
#include "Headers/instruction_set.h"

void parse_instruction(char *opcode, unsigned int data, u_int8_t *memory, u_int8_t *ACC, u_int16_t *MAR,
                       unsigned long *PC) {
    /**
     * Parse and execute instructions passed in through `opcode`
     *
     * @param opcode: 8-character string with the opcode
     * @param data: 1- or 2-byte operand
     * @param memory: pointer to the memory array
     * @param ACC: pointer to the 1-byte accumulator register
     * @param MAR: pointer to the 2-byte memory address register
     * @param PC: pointer to the program counter -- needed for branching instructions
     *
     * @return: when the instruction is executed or there is an error
     */
    
    printf("Executing Instruction %s 0x%x/%d\n", opcode, data, data);
    if(strcmp(opcode, "00011000") == 0) {
        /* NOOP */
        return;
    }
    
    if(strcmp(opcode, "00011001") == 0) {
        /* HALT */
        return;
    }
    
    if(opcode[0] == '0') {
        /* MEMORY / BRANCH OPERATIONS */
        char instr[4];
        memcpy(instr, &opcode[1], 3);
        instr[3] = '\0';
        
        if(strcmp(instr, "000") == 0) {
            /* MEMORY OPERATIONS */
            printf("\tMemory Operation - ");
            
            char method[3];
            memcpy(method, &opcode[6], 2);
            method[2] = '\0';
            
            /* PERFORM THE OPERATION */
            if(opcode[4] == '0') {
                /* STORE OPERATION */
                printf("Store\n\t\t");
                
                if(opcode[5] == '0') {
                    // STORE FROM ACC
                    printf("Register: ACC(0x%02x) --> ", *ACC);
                    
                    if(strcmp(method, "00") == 0) {
                        // INDIRECT ADDRESSING MODE
                        // Operand (data) is used as address
                        printf("memory[%d]\n", data);
                        printf("\tSETTING: memory[%d] = %02x\n", data, *ACC);
                        memory[data] = *ACC;
                    } else if(strcmp(method, "01") == 0) {
                        // DIRECT ADDRESSING MODE
                        // Operand is used as a constant
                        printf("\n\nERROR- CAN'T STORE ACC INTO A CONSTANT. opcode = \"%s\"", opcode);
                        exit(42);
                    } else if(strcmp(method, "10") == 0) {
                        // REGISTER INDIRECT ADDRESSING MODE
                        // Indirect (MAR used as pointer)
                        printf("memory[%d]\n", *MAR);
                        printf("\tSETTING: memory[%d] to %02x\n", *MAR, *ACC);
                        memory[*MAR] = *ACC;
                    } else {
                        printf("\n\nERROR PARSING MEMORY SOURCE \"%s\" IS AN INVALID MEMORY OPERATIONS METHOD",
                               method);
                        exit(42);
                    }
                } else if(opcode[5] == '1') {
                    // STORE FROM MAR
                    printf("Register: MAR(0x%04x) --> ", *MAR);
                    
                    if(strcmp(method, "00") == 0) {
                        // INDIRECT ADDRESSING MODE
                        // Operand (data) is used as address
                        printf("memory[%d, %d]\n", data, data + 1);
                        printf("\tSETTING: memory[%d] to (%02x, %02x)\n", data, (*MAR >> 8), (*MAR & 0x00FF));
                        memory[data] = (*MAR >> 8);
                        memory[data + 1] = (*MAR & 0x00FF);
                    } else if(strcmp(method, "01") == 0) {
                        // DIRECT ADDRESSING MODE
                        // Operand is used as a constant
                        printf("\nERROR- CAN'T STORE MAR INTO A CONSTANT. opcode = \"%s\"\n", opcode);
                        exit(42);
                    } else if(strcmp(method, "10") == 0) {
                        // REGISTER INDIRECT ADDRESSING MODE
                        // Indirect (MAR used as pointer)
                        printf("memory[%d]\n", *MAR);
                        printf("\tSETTING: memory[%d] to (%02x, %02x)\n", *MAR, (*MAR >> 8), (*MAR & 0x00FF));
                        memory[*MAR] = (*MAR >> 8);
                        memory[*MAR + 1] = (*MAR & 0x00FF);
                    } else {
                        printf("ERROR PARSING MEMORY SOURCE \"%s\" IS AN INVALID MEMORY OPERATIONS METHOD",
                               method);
                        exit(42);
                    }
                }
                return;
            } else if(opcode[4] == '1') {
                /* LOAD OPERATION */
                printf("Load to register %c\n\t\t", opcode[5]);
                
                if(opcode[5] == '0') {
                    // LOAD TO ACC
                    printf("Register: ACC(0x%02x) <-- ", *ACC);
                    
                    if(strcmp(method, "00") == 0) {
                        // INDIRECT ADDRESSING MODE
                        // Operand (data) is used as address
                        printf("memory[%d]\n", data);
                        printf("\tSETTING: ACC = 0x%02x\n", memory[data]);
                        *ACC = memory[data];
                        printf("\t\tACC = 0x%02x\n", *ACC);
                    } else if(strcmp(method, "01") == 0) {
                        // DIRECT ADDRESSING MODE
                        printf("0x%02x\n", data);
                        *ACC = data;
                        printf("\t\tACC = 0x%02x\n", *ACC);
                    } else if(strcmp(method, "10") == 0) {
                        // REGISTER INDIRECT ADDRESSING MODE
                        // Indirect (MAR used as pointer)
                        printf("memory[%d]\n", *MAR);
                        printf("MAR = 0x%02x\n", memory[*MAR]);
                        *ACC = memory[*MAR];
                        printf("\t\tACC = 0x%02x\n", *ACC);
                    } else {
                        printf("\n\nERROR PARSING MEMORY SOURCE \"%s\" IS AN INVALID MEMORY OPERATIONS METHOD",
                               method);
                        exit(42);
                    }
                } else if(opcode[5] == '1') {
                    // LOAD TO MAR
                    printf("Register: MAR(0x%04x) <-- ", *MAR);
                    
                    if(strcmp(method, "00") == 0) {
                        // INDIRECT ADDRESSING MODE
                        // Operand (data) is used as address
                        printf("memory[%d] + memory[%d]\n", data, data + 1);
                        printf("\tSETTING: MAR = 0x%02x%02x\n", memory[data], memory[data + 1]);
                        *MAR = (memory[data] << 8) | memory[data + 1];
                        printf("\t\tMAR = 0x%04x\n", *MAR);
                    } else if(strcmp(method, "01") == 0) {
                        // DIRECT ADDRESSING MODE
                        printf("0x%04x\n", data);
                        *MAR = data;
                        printf("\t\tMAR = 0x%04x\n", *MAR);
                    } else if(strcmp(method, "10") == 0) {
                        // REGISTER INDIRECT ADDRESSING MODE
                        // Indirect (MAR used as pointer)
                        printf("memory[%d] + memory[%d]\n", *MAR, *MAR + 1);
                        printf("MAR = 0x%02x%02x\n", memory[*MAR], memory[*MAR + 1]);
                        *MAR = (memory[*MAR] << 8) | memory[*MAR + 1];
                        printf("\t\tMAR = 0x%04x\n", *MAR);
                    } else {
                        printf("\n\nERROR PARSING MEMORY SOURCE \"%s\" IS AN INVALID MEMORY OPERATIONS METHOD",
                               method);
                        exit(42);
                    }
                }
                return;
            }
        } else if(strcmp(instr, "001") == 0 && opcode[4] == '0') {
            /* BRANCHING OPERATIONS */
            
            printf("\tBranching Operation - ");
            char branch_type[4];
            memcpy(branch_type, &opcode[5], 3);
            branch_type[3] = '\0';
    
            if(strcmp(branch_type, "000") ==  0) {
                // UNCONDITIONAL BRANCH
                printf("Unconditional\n\t\t");
                BRA(PC, data);
            } else if(strcmp(branch_type, "001") ==  0) {
                // BRANCH IF ACC == 0
                printf("Branch if ACC == 0\n\t\t");
                BRZ(PC, ACC, data);
            } else if(strcmp(branch_type, "010") ==  0) {
                // BRANCH IF ACC != 0
                printf("BRANCH IF ACC != 0\n\t\t");
                BNE(PC, ACC, data);
            } else if(strcmp(branch_type, "011") ==  0) {
                // BRANCH IF ACC < 0
                printf("BRANCH IF ACC < 0\n\t\t");
                BLT(PC, ACC, data);
            } else if(strcmp(branch_type, "100") ==  0) {
                // BRANCH IF ACC ≤ 0
                printf("BRANCH IF ACC ≤ 0\n\t\t");
                BLE(PC, ACC, data);
            } else if(strcmp(branch_type, "101") ==  0) {
                // BRANCH IF ACC > 0
                printf("BRANCH IF ACC > 0\n\t\t");
                BGT(PC, ACC, data);
            } else if(strcmp(branch_type, "110") ==  0) {
                // BRANCH IF ACC ≥ 0
                printf("BRANCH IF ACC ≥ 0\n\t\t");
                BGE(PC, ACC, data);
            } else {
                printf("\n\nINVALID BRANCHING OPERATION CODE \"%s\"", branch_type);
                exit(42);
            }
        }
        
    } else if(opcode[0] == '1') {
        /* MATHEMATICAL OR LOGICAL OPERATIONS */
        printf("\tMathematical Operation -\n\t\t");
        char instr[4];
        memcpy(instr, &opcode[1], 3);
        instr[3] = '\0';
        
        /* DETERMINE DESTINATION */
        int is_mar = 0;
        u_int8_t *destination;
        char dest[3];
        memcpy(dest, &opcode[4], 2);
        dest[2] = '\0';
        if(strcmp(dest, "00") == 0) {
            // REGISTER INDIRECT ADDRESSING MODE
            // Indirect (MAR used as pointer)
            destination = &memory[*MAR];
            printf("Destination: &memory[*MAR] = memory[%02x]\n", *MAR);
        } else if(strcmp(dest, "01") == 0) {
            // REGISTER ADDRESSING MODE - ACC
            destination = ACC;
            printf("Destination: ACC (currently) = 0x%02x\n", *destination);
        } else if(strcmp(dest, "10") == 0) {
            // REGISTER ADDRESSING MODE - MAR
            is_mar = 1;
            destination = NULL;
            printf("Destination: MAR (currently) = 0x%04x\n", *MAR);
        } else if(strcmp(dest, "11") == 0) {
            // INDIRECT ADDRESSING MODE
            // Operand (data) is used as address
            destination = &memory[data];
            printf("Destination: &memory[data] = memory[%d]\n", data);
        } else {
            printf("\nINVALID DESTINATION VALUE. SOMETHING IS WRONG. DESTINATION CODE: \'%s\'", dest);
            exit(42);
        }
        
        /* DETERMINE SOURCE */
        u_int8_t *source;
        char src[3];
        memcpy(src, &opcode[6], 2);
        dest[2] = '\0';
        if(strcmp(src, "00") == 0) {
            // REGISTER INDIRECT ADDRESSING MODE
            // Indirect (MAR used as pointer)
            source = &memory[*MAR];
            printf("\t\tSource: memory[*MAR] = memory[0x%d]\n", *MAR);
        } else if(strcmp(src, "01") == 0) {
            // REGISTER ADDRESSING MODE - ACC
            source = ACC;
            printf("\t\tSource: ACC (currently) = 0x%02x\n", *source);
        } else if(strcmp(src, "10") == 0) {
            // DIRECT ADDRESSING MODE
            // Operand is used as a constant
            source = malloc(sizeof(data));
            *source = data;
            printf("\t\tSource: data = 0x%x\n", *source);
        } else if(strcmp(src, "11") == 0) {
            // INDIRECT ADDRESSING MODE
            // Operand (data) is used as address
            source = &memory[data];
            printf("\t\tSource: memory[data] = memory[%d] = 0x%02x\n", data, memory[data]);
        } else {
            printf("\nINVALID SOURCE VALUE. SOMETHING IS WRONG. SOURCE CODE: \'%s\'", src);
            exit(42);
        }
        
        /* PERFORM THE OPERATION */
        if(strcmp(instr, "000") == 0) {
            // AND
            if(is_mar == 0) {
                AND(source, destination);
            } else {
                AND_MAR(source, MAR);
            }
            return;
        } else if(strcmp(instr, "001") == 0) {
            // OR
            if(is_mar == 0) {
                OR(source, destination);
            } else {
                OR_MAR(source, MAR);
            }
            return;
        } else if(strcmp(instr, "010") == 0) {
            // XOR
            if(is_mar == 0) {
                XOR(source, destination);
            } else {
                XOR_MAR(source, MAR);
            }
            return;
        } else if(strcmp(instr, "011") == 0) {
            // ADD
            if(is_mar == 0) {
                ADD(source, destination);
            } else {
                ADD_MAR(source, MAR);
            }
            return;
        } else if(strcmp(instr, "100") == 0) {
            // SUB
            if(is_mar == 0) {
                SUB(source, destination);
            } else {
                SUB_MAR(source, MAR);
            }
            return;
        } else if(strcmp(instr, "101") == 0) {
            // INC
            if(is_mar == 0 && &*source == &*destination) {
                INC(destination);
            } else if(is_mar == 1) {
                INC_MAR(MAR);
            } else {
                printf("INCREMENT OPERATION SOURCE IS NOT THE SAME AS DESTINATION. %p ≠ %p\n", &*source,
                       &*destination);
                exit(42);
            }
        } else if(strcmp(instr, "110") == 0) {
            // DEC
            if(is_mar == 0 && &*source == &*destination) {
                DEC(destination);
            } else if(is_mar == 1) {
                DEC_MAR(MAR);
            } else {
                printf("INCREMENT OPERATION SOURCE IS NOT THE SAME AS DESTINATION. %p ≠ %p\n", &*source,
                       &*destination);
                exit(42);
            }
        } else if(strcmp(instr, "111") == 0) {
            // NOT
            if(is_mar == 0 && &*source == &*destination) {
                NOT(destination);
            } else if(is_mar == 1) {
                NOT_MAR(MAR);
            } else {
                printf("INCREMENT OPERATION SOURCE IS NOT THE SAME AS DESTINATION. %p ≠ %p\n", &*source,
                       &*destination);
                exit(42);
            }
        } else {
            printf("\nINVALID MEMORY INSTRUCTION. SOMETHING IS WRONG \'%s\'", instr);
            exit(42);
        }
    } else {
        printf("There is no such thing as a number not equal to 0 or 1. \'%c\' - \"%s\"", opcode[0], opcode);
        exit(42);
    }
}

int get_num_data_bits(char *opcode) {
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
                    exit(42);
                }
            } else if(strcmp(instr, "001") == 0) {
                /* BRANCHING OPERATION */
                // The opcode is always followed by a 16-bit operand that serves as the memory address.
                printf("\tBranching Operation - \n");
                return 16;
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
            exit(42);
        }
    }
    
    printf("\n\n--------------------------\n");
    printf("FAILED TO PARSE THE OPCODE\n");
    printf("--------------------------\n\n\n");
    return -1;
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
            exit(42);
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
            exit(42);
    }
}

int binary_to_decimal(char *binary) {
    int decimal = 0;
    for(int i = 0; i < sizeof(binary); i++) {
        if(binary[i] == '1') {
            decimal += (int)pow(2, i);
        }
    }
    return decimal;
    /*if(strcmp(binary, "0000") == 0 || strcmp(binary, "000") == 0) {
        return 0;
    } else if(strcmp(binary, "0001") == 0) {
        return 1;
    } else if(strcmp(binary, "0010") == 0) {
        return 2;
    } else if(strcmp(binary, "0011") == 0) {
        return 3;
    } else if(strcmp(binary, "0100") == 0) {
        return 4;
    } else if(strcmp(binary, "0101") == 0) {
        return 5;
    } else if(strcmp(binary, "0110") == 0) {
        return 6;
    } else if(strcmp(binary, "0111") == 0) {
        return 7;
    } else if(strcmp(binary, "1000") == 0) {
        return 8;
    } else if(strcmp(binary, "1001") == 0) {
        return 9;
    } else if(strcmp(binary, "1010") == 0) {
        return 10;
    } else if(strcmp(binary, "1011") == 0) {
        return 11;
    } else if(strcmp(binary, "1100") == 0) {
        return 12;
    } else if(strcmp(binary, "1101") == 0) {
        return 13;
    } else if(strcmp(binary, "1110") == 0) {
        return 14;
    } else if(strcmp(binary, "1111") == 0) {
        return 15;
    } else {
        printf("ERROR IN BINARY STRING TO HEX NIBBLE METHOD\n");
        printf("\"%s\" IS NOT A VALID BINARY STRING VALUE", binary);
        exit(42);
    }*/
}