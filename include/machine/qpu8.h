/*==============================================================================
 Copyright (c) 2025 Twink's Death
 SPDX-License-Identifier: BSD-3-Clause
 See the LICENSE file in repo's root for details.

 qpu8_emu: qpu8.h
 =============================================================================*/

#ifndef QPU8_H
#define QPU8_H

// Project headers
#include "emulator/emu.h"

// Definitions
#define ADDRESS_SPACE   0x10000
#define REGISTER_COUNT  8
#define BIOS_START      0xE000

#define STACK_SIZE      0x1000  // 4  KB
#define LOW_RAM_SIZE    0x4000  // 16 KB
#define HIGH_RAM_SIZE   0x4000  // 16 KB
#define KERNEL_RAM_SIZE 0x6000  // 24 KB
#define BIOS_SIZE       0x2000  // 8  KB

// Addressable memory
typedef struct {
    byte memory[ADDRESS_SPACE];
} MEMORY;

// Memory map:
// 0x0000 - 0x3FFF: Not banked (Low ram)
// 0x4000 - 0x7FFF: Banked (High ram)
// 0x8000 - 0xDFFF: Kernel/OS (Ram, privileged access)
// 0xE000 - 0xFFFF: BIOS (Rom, privileged access + write protected)

/*
Mnemonic	        Byte 1	    Byte 2	    Byte 3	    Pseudocode
STORE Rs, addr	    00000 SSS	AAAA AAAA	AAAA AAAA	mem[addr] = Rs
STORE Rs, [HL]	    00001 SSS			                mem[HL] = Rs
STORE Rs, addr+B	00010 SSS	AAAA AAAA	AAAA AAAA	mem[addr+B] = Rs
STORE Rs, [HL]+B	00011 SSS			                mem[HL+B] = Rs
LOAD Rd, addr	    00100 DDD	AAAA AAAA	AAAA AAAA	Rd = mem[addr]
LOAD Rd, [HL]	    00101 DDD			                Rd = mem[HL]
LOAD Rd, addr+B	    00110 DDD	AAAA AAAA	AAAA AAAA	Rd = mem[HL+B]
LOAD Rd, [HL]+B	    00111 DDD			                Rd = mem[HL+B]
PUSH Rs	            01000 SSS			                ram[SP] = Rs, SP++
POP RD	            01001 DDD			                Rd = ram[SP], SP--
JUMP addr	        0101L CCC	AAAA AAAA	AAAA AAAA	if (C) PC = addr
JUMP [HL]	        0110L CCC			                if (C) PC = HL
INT id	            01110 CCC 	IIII IIII		        if (C) PUSH PC, FLAGS, JMP INTVEC
IRET	            01111 CCC 			                if (C) POP FLAGS, PC
CALL addr	        10000 CCC 	AAAA AAAA	AAAA AAAA	if (C) PUSH PC+3, JMP addr
CALL [HL]	        10001 CCC 			                if (C) PUSH PC+3, JMP HL
RET	                10010 CCC			                if (C) POP PC
ADD Rd, Rs, Rs	    10011 DDD	SSS sss 00		        Rd = Rs + Rs
ADDC Rd, Rs, Rs	    10011 DDD	SSS sss 01		        Rd = Rs + Rs + C
SUB Rd, Rs, Rs	    10011 DDD	SSS sss 10		        Rd = Rs - Rs
SUBB Rd, Rs, Rs	    10011 DDD	SSS sss 11		        Rd = Rs - Rs - B
AND Rd, Rs, Rs	    10100 DDD	SSS sss 00		        Rd = Rs && Rs
NOR Rd, Rs, Rs	    10100 DDD	SSS sss 01		        Rd = !(Rs || Rs)
XOR Rd, Rs, Rs	    10100 DDD	SSS sss 10		        Rd = Rs ^ Rs
NEG Rd	            10100 DDD	XXX 000 11		        Rd = -Rd
SHL Rd, Amnt	    10100 DDD	AAA 001 11		        Rd <<= A
SHR Rd, Amnt	    10100 DDD	AAA 010 11		        Rd >>= A
ROL Rd, Amnt	    10100 DDD	AAA 011 11		        Rd = (Rd << A) || (Rd >> (8 - A))
ROR Rd, Amnt	    10100 DDD	AAA 100 11		        Rd = (Rd >> A) || (Rd << (8 - A))
SAL Rd, Amnt	    10100 DDD	AAA 101 11		        signed Rd <<= A
SAR Rd, Amnt	    10100 DDD	AAA 110 11		        signed Rd >>= A
ABS Rd	            10100 DDD	XXX 111 11		        Rd = Abs(Rd)
ADDI Rd, Rd + Imm8	10101 DDD	IIII IIII		        Rd += Imm8
LOADI Rd, Imm8	    10110 DDD	IIII IIII		        Rd = Imm8
SUBI Rd, Rd + Imm8	10111 DDD	IIII IIII		        Rd -= Imm8
INC Rd	            11000 DDD			                Rd++
DEC Rd	            11001 DDD			                Rd--
WFI	                11010 000			                while (IRQ||NMI) {sleep}
SET	                11010 001	IIII IIII		        flags = flags || imm8
CLEAR	            11010 010	IIII IIII		        flags = flags && !imm8
MASK	            11010 011	IIII IIII		        mask = imm8
CPC	                11010 100			                HL = PC
CSP	                11010 101			                HL = SP
CBP	                11010 110			                HL = BP
LOOP	            11010 111	AAAA AAAA	AAAA AAAA	while (R3 != 0) { jmp mem[addr]; R3-- }
MUL Rs, Rs	        11011 CCC	SSS SSS 00		        if (C) HL = Rs * Rs
IMUL Rs, Rs	        11011 CCC	SSS SSS 01		        if (C) HL = Rs * Rs // signed
DIV Rs, Rs	        11011 CCC	SSS SSS 10		        if (C) Hi = Rs / Rs; Lo = Rs % Rs
IDIV Rs, Rs	        11011 CCC	SSS SSS 11		        if (C) Hi = Rs / Rs; Lo = Rs % Rs // signed
MLI Rs, Imm8	    11100 SSS	IIII IIII		        HL = Rs * imm8
IMULI Rs, Imm8	    11101 SSS	IIII IIII		        HL = Rs * imm8 // signed
DIVI Rs, Imm8	    11110 SSS	IIII IIII		        Hi = Rs / imm8; Lo = Rs % imm8
IDIVI Rs, Imm8	    11111 SSS	IIII IIII		        Hi = Rs / imm8; Lo = Rs % imm8 // signed
Halt	            11111 111			                else if (SSS == 7) quit()
*/

#endif //QPU8_H
