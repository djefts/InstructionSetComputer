//
// Created by David Jefts on 2019-11-21.
//

#ifndef INSTRUCTIONSETCOMPUTER_PARSING_FUNCTIONS_H
#define INSTRUCTIONSETCOMPUTER_PARSING_FUNCTIONS_H
void parse_instruction(char *opcode, char *data);
int num_data_bits(char *opcode);
unsigned char hex_char_to_int(unsigned char hex);
void hex_byte_to_binary(unsigned char hex, char *byte);
char *nibble_to_binary(unsigned char hex);

#endif //INSTRUCTIONSETCOMPUTER_PARSING_FUNCTIONS_H
