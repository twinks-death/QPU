# QPU
A custom 8-bit RISC CPU emulator.

All this is still a massive WIP, I'll complete the readme once I have more free time.  
Any contributions: optimisations, a better way to write something, ideas etc. are welcome! Cos I barely know what I'm doing!
---

## Basic architecture

**QPU** is a cpu inspired by early x86, 32-bit ARM, RISC-V and most notably the 8008/8080 for the HL register pair used as a pointer.  
It has 8 GP registers, R0 to R7, where each of the bits in F (R5) is a cpu flag set either by specialised instructions, or after ALU operations.
---

#### Registers:

```
Z (R0) - Always 0, writes ignored  
A (R1) - GP, Accumulator  
B (R2) - GP, Base (for indexing)  
C (R3) - GP, Counter  
D (R4) - GP, For IO  
F (R5) - GP, Flags  
L (R6) - GP, Temporary, Low 8 bits of an address / low 8 bits of mul product  
H (R7) - GP, Temporary, High 8 bits of an address / high 8 bits of mul product
```

---

#### Flags:

```
7 (K): Privilege (0/1 - user/kernel)  
6 (I): Interrupts (0/1 - disabled/enabled)  
5 (V): Overflow  
4 (S): Sign  
3 (A): Auxiliary carry  
2 (P): Parity  
1 (C): Carry  
0 (Z): Zero
```

---

#### AUX Registers:

```
SP   - Stack pointer   (10 bits)  
BP   - Base pointer    (10 bits)  
MASK - Interrupt mask  (8 bits)  
PC   - Program counter (16 bits)         
```

---

## Building and using

#### Prerequisites

- A C compiler: gcc or clang (MSVC won't work with flags in cmakelists)
- [CMake](https://cmake.org/) (Requires version 3.31.6 or newer)
- A generator like [Ninja](https://ninja-build.org/) that works with CMake
- On windows, I'd recommend [MSys2](https://https://www.msys2.org/),  
  then install gcc or clang in either UCRT64 (for gcc) or CLANG64 (for clang) shells using pacman, as well as cmake and a cmake-friendly generator

---  

#### Building

Clone the repo and compile with cmake:

```sh
git clone https://github.com/twinks-death/QPU.git
cd QPU
cmake -S . -B build 
cmake --build build
./build/qpu8_emu /assembly/lexer_test.s
```

To uninstall:

```sh
rm -rf QPU
```L