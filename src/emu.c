#include "qpu8.c"
#include "../includes/emu.h"
#include "../asm/assembler/asm.c"

int main( int argc, char *argv[] )
{
    check_flags(parse_flags(argc, argv));
    return 0;
}