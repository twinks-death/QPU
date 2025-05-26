#ifndef QPU_LIB_H
#define QPU_LIB_H

/*
QPU Rev1

8-bits, 16-bits address
==================================
Registers:  Z (R0)  -  Always 0, writes ignored
            A (R1)  -  GP, accumulator
            B (R2)  -  GP, base (for indexing)
            C (R3)  -  GP, counter
            D (R4)  -  GP, for IO
            F (FL)  -  GP, flags
            L (LO)  -  GP, lo 8 bits of an address / lo 8 bits of mul product
            H (HI)  -  GP, hi 8 bits of an address / hi 8 bits of mul product

AUX Regs:   SP      -  Stack pointer (10 bits)
            BP      -  Base pointer (10 bits)
            MASK    -  Interrupt mask (8 bits)
            PC      -  Program counter (16 bits)

Mnemonic	        Byte 1	    Byte 2	    Byte 3	    Pseudocode
STR Rs, addr	    00000 SSS	AAAA AAAA	AAAA AAAA	mem[addr] = Rs
STR Rs, [HL]	    00001 SSS			                mem[HL] = Rs
STR Rs, addr+B	    00010 SSS	AAAA AAAA	AAAA AAAA	mem[addr+B] = Rs
STR Rs, [HL]+B	    00011 SSS			                mem[HL+B] = Rs
LOD Rd, addr	    00100 DDD	AAAA AAAA	AAAA AAAA	Rd = mem[addr]
LOD Rd, [HL]	    00101 DDD			                Rd = mem[HL]
LOD Rd, addr+B	    00110 DDD	AAAA AAAA	AAAA AAAA	Rd = mem[HL+B]
LOD Rd, [HL]+B	    00111 DDD			                Rd = mem[HL+B]
PUSH Rs	            01000 SSS			                mem[SP] = Rs
POP RD	            01001 DDD                           Rd = mem[SP]
JMP addr	        0101L CCC	AAAA AAAA	AAAA AAAA   C? PC = addr : pass
JMP [HL]	        0110L CCC                           C? PC = HL : pass
INT id	            0111 CCC0	IIII IIII
IRET	            0111 CCC1
CALL addr	        1000 CCC0	AAAA AAAA	AAAA AAAA
CALL [HL]	        1000 CCC1
RET	                10010 CCC
ADD Rd, Rs, Rs	    10011 DDD	SSS sss 00
ADC Rd, Rs, Rs	    10011 DDD	SSS sss 01
SUB Rd, Rs, Rs	    10011 DDD	SSS sss 10
SBB Rd, Rs, Rs	    10011 DDD	SSS sss 11
AND Rd, Rs, Rs	    10100 DDD	SSS sss 00
NOR Rd, Rs, Rs	    10100 DDD	SSS sss 01
XOR Rd, Rs, Rs	    10100 DDD	SSS sss 10
NEG Rd	            10100 DDD	XXX 000 11
SHL Rd, Amnt	    10100 DDD	AAA 001 11
SHR Rd, Amnt	    10100 DDD	AAA 010 11
ROL Rd, Amnt	    10100 DDD	AAA 011 11
ROR Rd, Amnt	    10100 DDD	AAA 100 11
SAL Rd, Amnt	    10100 DDD	AAA 101 11
SAR Rd, Amnt	    10100 DDD	AAA 110 11
ABS Rd	            10100 DDD	XXX 111 11
ADI Rd, Rd + Imm8	10101 DDD	IIII IIII
LDI Rd, Imm8	    10101 DDD	IIII IIII
SBI Rd, Rd + Imm8	10110 DDD	IIII IIII
INC Rd	            10110 DDD
DEC Rd	            10111 DDD
MASK Imm8	        11000 CCC	IIII IIII
WFI	                11001 CCC
MUL Rs, Rs	        11010 CCC	SSS SSS 00
IMUL Rs, Rs	        11010 CCC	SSS SSS 01
DIV Rs, Rs	        11010 CCC	SSS SSS 10
IDIV Rs, Rs	        11010 CCC	SSS SSS 11
MLI Rs, Imm8	    11011 SSS	IIII IIII
IMLI Rs, Imm8	    11100 SSS	IIII IIII
DVI Rs, Imm8	    11101 SSS	IIII IIII
IDVI Rs, Imm8	    11110 SSS	IIII IIII
Halt	            1111 1111
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


// Memory map:
// 0x0000 - 0x3FFF: Not banked (Low ram)
// 0x4000 - 0x7FFF: Banked (High ram)
// 0x8000 - 0xDFFF: Kernel/OS (Ram, privileged access)
// 0xE000 - 0xFFFF: BIOS (Rom, privileged access + write protected)

// Definitions
// TODO: implement ts later
#define ADDRESS_SPACE   0x10000
#define REGISTER_COUNT  8
#define BIOS_START      0xE000

#define STACK_SIZE      0x1000
#define LOW_RAM_SIZE    0x4000  // 16 KB
#define HIGH_RAM_SIZE   0x4000  // 16 KB
#define KERNEL_RAM_SIZE 0x6000 // 24 KB
#define BIOS_SIZE       0x2000  // 8 KB

// Types
typedef uint8_t byte;
typedef uint16_t word;

// Addressable memory
typedef struct {
    byte memory[ADDRESS_SPACE];
} MEMORY;

// Emulator flags
struct {
    bool assemble;
    bool disassemble;
    bool test;
    byte speed;
} emu_flags = { false, false, false, 2};


#endif //QPU_LIB_H
