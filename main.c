#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "Headers/instruction_set.h"
#include "Headers/parsing_functions.h"

void fetchNextInstruction();
void executeInstruction();
void fileInput();
void fileOutput();


unsigned char memory[65536];    // main memory is 2^16 BYTES
unsigned char ACC = 0x0;        // accumulator
char IR[9];                     // instruction register - 8 bit string plus null char
int MAR = 0;                    // memory address register
unsigned long PC = 0;           // program counter

int main(int argc, char *argv[]) {
    printf("Starting program...\n");
    
    /* FILE INPUT */
    fileInput();
    
    // print contents of memory
    printf("\nStarting memory state (%lu bytes):\n[ ", sizeof(memory));
    unsigned long s = 0;
    for(s = 0; s < sizeof(memory) - 1; s++) {
        if(s > 0 && s % 32 == 0) {
            printf("\n  ");
        }
        printf("%02x, ", memory[s]);
    }
    printf("%02x  ]\n\n", memory[s]);
    
    /* INSTRUCTION FETCHING AND EXECUTION */
    PC = 0;
    while(PC < sizeof(memory)) {
        fetchNextInstruction();
        
        if(strcmp(IR, "00011001") == 0) {
            printf("\n\n--------------------------------------------------\n");
            printf("END OF PROGRAM.\n");
            printf("THANK YOU FOR COMING. BYE.\n");
            break;
        }
        
        executeInstruction();
    }
    
    /* FILE OUTPUT */
    fileOutput();
    
    /*// print contents of memory
    printf("\nFinal memory state (%lu bytes):\n[ ", sizeof(memory));
    unsigned long e = 0;
    for(e = 0; e < sizeof(memory) - 1; e++) {
        if(e > 0 && e % 32 == 0) {
            printf("\n  ");
        }
        printf("%x, ", memory[e]);
    }
    printf("%x\t]\n", memory[e]);*/
}

void fetchNextInstruction() {
    printf("Fetching next instruction...\n");
    /* get opcode and put it into the instruction register */
    unsigned char b = memory[PC];
    PC++;
    
    hex_byte_to_binary(b, IR);  // 8 bits + null terminator
    // printf("Bytes: %s\n", byte);
    
    //print new PC and current opcode
    printf("PC: %lu \n", PC);
    printf("IR: %02x = %s \n", b, IR);
}

void executeInstruction() {
    printf("Executing instruction %s\n", IR);
    if(strcmp(IR, "00011000") == 0) {
        printf("\tNOP(e). Nothing to see here, move along.\n\n");
        return;  // Nothing to see here, move along.
    }
    
    /* figure out how many more bytes we need to grab */
    int mo_bits = num_data_bits(IR);
    
    char *data = calloc(mo_bits, sizeof(char));
    printf("\tExtracting %i bits (%i bytes) from memory into data.\n", mo_bits, mo_bits / 8);
    for(int i = 0; i < mo_bits / 8; i++) {
        unsigned char next_byte = memory[PC];
        PC++;
        
        char binary_byte[9];
        hex_byte_to_binary(next_byte, binary_byte);
        printf("\t%02x = %s\n", next_byte, binary_byte);
        snprintf(data, (i + 1) * 8 + 1, "%s%s", data, binary_byte);
    }
    printf("  Full instruction: %s %s\n\n", IR, data);
    
    /* execute the instruction */
    // parse_instruction(IR, data);
}

void fileInput() {
    printf("\nReading mem.in into memory...\n");
    FILE *file = fopen("mem_in.txt", "rb");
    unsigned char mem[65536];
    for(unsigned long i = 0; i < sizeof(mem); i++) {
        mem[i] = '0';
    }
    
    /* READ FILE IN */
    char *buffer = 0;
    long length;
    
    if(file) {
        fseek(file, 0, SEEK_END);
        length = ftell(file);
        fseek(file, 0, SEEK_SET);
        buffer = malloc(length);
        if(buffer) {
            fread(buffer, 1, length, file);
        }
        fclose(file);
    } else {
        printf("Unable to open file!");
        return;
    }
    
    if(buffer) {
        int pc = 0;
        for(long i = 0; i < length; i++) {
            unsigned char byte = buffer[i];  // every character in buffer
            if(byte != ' ' && byte != '\n' && byte != '\r') {
                mem[pc] = byte;
                pc++;
            }
        }
    }
    
    // convert local mem to hex values and set global memory
    int i = 0;
    PC = 0;
    printf("\nConverting local mem nibbles to global memory bytes:\n[ ");
    for(i = 0; i < sizeof(mem); i = i + 2) {
        printf("%c%c, ", mem[i], mem[i + 1]);  // converting from
        /* EACH BYTE IS TWO NIBBLES */
        memory[PC] = hex_char_to_int(mem[i]) * 16;  // converted to
        memory[PC] += hex_char_to_int(mem[i + 1]);  // converted to
        PC++;
    }
    printf("%c ]\n", mem[i]);
    
    fclose(file);
}

void fileOutput() {
    printf("\nWriting memory into mem.out...\n");
    FILE *file = fopen("mem_out.txt", "wb");
    
    /* READ FILE IN */
    if(file) {
        for(PC = 0; PC < sizeof(memory); PC++) {
            if(PC > 0 && PC % 10 == 0) {
                fprintf(file, "\n");
            }
            fprintf(file, "%02x ", memory[PC]);
        }
        fclose(file);
    } else {
        printf("Unable to open file!");
        return;
    }
    
    fclose(file);
}
