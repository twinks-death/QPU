# QPU
A custom 8-bit RISC CPU emulator.

All this is still a massive WIP, I'll complete the readme once I have more free time.
Any contributions: optimisations, a better way to write something, ideas etc. are welcome! Cos I barely know what I'm doing!
18/05

todo: style all of this later
QPU Rev1.2

8-bits, 16-bits address

Registers:  Z (R0)  - Always 0, writes ignored
A (R1)  - GP, Accumulator
B (R2)  - GP, Base (for indexing)
C (R3)  - GP, Counter
D (R4)  - GP, For IO
F (R5)  - GP, Flags
L (R6)  - GP, Temporary, Low 8 bits of an address / low 8 bits of mul product
H (R7)  - GP, Temporary, High 8 bits of an address / high 8 bits of mul product

Flags: 7: Privilege (0/1 - user/supervisor)
       6: Interrupts (0/1 - disabled/enabled)
       5: Overflow
       4: Sign
       3: Auxiliary carry
       2: Parity
       1: Carry
       0: Zero

AUX Regs: SP   - Stack pointer   (10 bits)
          BP   - Base pointer    (10 bits)
          MASK - Interrupt mask  (8 bits)
          PC   - Program counter (16 bits)        