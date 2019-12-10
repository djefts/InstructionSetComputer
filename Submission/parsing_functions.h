//
// Created by David Jefts on 2019-11-21.
//

#ifndef INSTRUCTIONSETCOMPUTER_PARSING_FUNCTIONS_H
#define INSTRUCTIONSETCOMPUTER_PARSING_FUNCTIONS_H
void parse_instruction(char *opcode, unsigned int data, uint8_t *memory, uint8_t *ACC, uint16_t *MAR,
                       unsigned long *PC);
int get_num_data_bits(char *opcode);
unsigned char hex_char_to_int(unsigned char hex);
void hex_byte_to_binary(unsigned char hex, char *byte);
char *nibble_to_binary(unsigned char hex);
int binary_to_decimal(char *binary);

#endif //INSTRUCTIONSETCOMPUTER_PARSING_FUNCTIONS_H
