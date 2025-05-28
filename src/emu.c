// Standart includes
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

// My own includes
#include "../includes/emu.h" // Always first! Includes typedefs for other dependencies
#include "../asm/assembler/asm.c"
#include "../asm/assembler/disasm.c"
#include "qpu8.c"

int main( int argc, char *argv[] )
{
    // Default flags - no assembly, no disassembly, no tests, 10mhz clock speed, no file input (nullptr)
    emu_flags_t emu_flags = { false, false, false, 2, nullptr };

    // Populate emu_flags, (dis)assemble based on them
    parse_flags( argc, argv, &emu_flags );
    if ( emu_flags.assemble )
        assemble(emu_flags.input_file);
    else if ( emu_flags.disassemble )
        disassemble(emu_flags.input_file);
    else
        assert(0 && "both assemble and dissasemble are false!"); // Mystery

    return 0;
}