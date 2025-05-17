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

#endif //QPU_LIB_H
