This the repo for a Two-Stage Instruction Decoder I wrote as a solution to the assignment described below.

## Introduction

The assignment is to design a simple processor based on the simplified 2-step instruction cycle. You will be
creating two functions in software, one to simulate the fetch next instruction cycle, `fetchNextInstruction()`, and
one to simulate the execute instruction cycle, `executeInstruction()`. Neither of these functions will have parameters
nor will they return values. They will operate on global data meant to simulate the registers and memory of the
processor.

This simulated machine consists of four registers that will be represented in your software with
four global variables:

- **PC** -- Program Counter (16 bit) used to hold the address of the next instruction to executire. It is initialized
  to zero.
- **IR** -- Instruction Register (8 bit) used to hold the current instruction being executred.
- **MAR** -- Memory Address Register (16 bit) used to hold an address being used as a pointer, i.e., an indirect
  reference to data in memory.
- **ACC** -- Accumulator (8 bit) used to operate on the data.

Memory will be simulated with an array `memory[65536]`.
The function fetchNextInstruction() will perform the following steps:

1. Use the Program Counter (PC) as an index to retrieve an instruction from the array `memory[]`.
2. Store the retrieved instruction to the Instruction Register (IR).
3. Determine from the instruction how much to incrememnt PC so that it points to the next instruction in `memory[]`
   and perform the increment.

The function `executeInstruction()` will examine IR to determine which operation to perform and perform it on the
data contained in the registers and in the array `memory[]`.

---

## Instruction (Opcode) Set

The following is a break-down of the opcodes of the simple machine for which you are designing a simulator. The data
(operands) for each instruction will follow the opcode immediately in memory. It is important to note that when
using a 16-bit operand (data or memory address), the byte immediately following the opcode is the most significant
byte of the address and the byte 2 following that is the least significant. This is referred to as "Big Endian". The
opcode for this machine will always be 8 bits. This means that the size of an instruction along with its data could
be 1 byte (an opcode that doesn't need an operand), 2 bytes (an opcode that uses 8-bit immediate data, i.e., a
constant), or 3 bytes (an opcode that uses an address as its operand or 16-bit immediate data).

![OpcodeSizes](https://github.com/djefts/InstructionSetComputer/assets/30559436/10f4e415-487b-4cb8-a4dc-1f816dd3f0d3)

### Mathematical or Logical Operations:

If the most significant bit of the opcode is `1`, then the opcode represents a mathematical or logical function. The
opcode may be followed by 0, 1, or 2 bytes of operands.

![OpcodeSet](https://github.com/djefts/InstructionSetComputer/assets/30559436/57dd9b4e-db03-427c-837e-b89feb0c6270)

\* -- The constant is passed to the processor as an 8- or 16-bit operand following the opcode.  
** -- The memory address is passed to the processor as a 16-bit operand following the opcode

### Memory Operations:

If the most significant four bits are `0000`, then the opcode represents a memory or data transfer operation. When the 
“Method” bit is equal to `00`, the opcode is followed by a 16-bit operand that serves as the memory address. When the 
“Method” bit is equal to `01`, the opcode is followed by an operand that serves as a constant (8 bits for ACC and 16 
bits for MAR). Otherwise, the value contained in index register MAR is used as the memory address.

![MemOps](https://github.com/djefts/InstructionSetComputer/assets/30559436/9d323835-4abb-4f28-8e24-109060fe1015)

### Branches/Jumps:

If the most significant five bits are `00010`, then the opcode represents an unconditional or conditional branch or 
jump. The opcode is ***always*** followed by a 16-bit operand that serves as the memory address.

![BranchOps](https://github.com/djefts/InstructionSetComputer/assets/30559436/2bdd8513-73f2-4036-8b1f-1934e46ece09)

### Special Opcodes:

There are two additional opcodes included in the instruction set that represent special operations not included in 
the list above. None of the special opcodes require operands.
- `00011000` – NOP (No operation. `fetchNextInstruction()` should simply increment PC by one to the next instruction)
- `00011001` – Halt (Stops processor)

---

## Sample Framework

The code below represents a basic framework for the simulator. It includes the prototypes for
`fetchNextInstruction()` and `executeInstruction()` along with the global definitions for each of the
machine's registers. Note that the numeric types `char` and `int` differ across different platforms, so
be sure to perform a bit-wise `AND` after every mathematical operation to clear the unused bits,
i.e., `AND` `ACC` with `0xff` and `MAR` with `0xffff` to clear upper bits. The loop below continuously
calls `fetchNextInstruction()` and `executeInstruction()` until the PC register points at a `HALT`
instruction.

```c
#define HALT_OPCODE 0x19

void fetchNextInstruction(void);
void executeInstruction(void);

unsigned char memory[65536];
unsigned char ACC=0;
unsigned char IR=0;
unsigned int MAR=0;
unsigned int PC=0;

int _tmain(int argc, _TCHAR* argv[]) {
    // Execution loop. Continue fetching and executing until PC points to a HALT instruction
    while(memory[PC] != HALT_OPCODE) {
        fetchNextInstruction();
        executeInstruction();
    }
    return 0;
}
```
