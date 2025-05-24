#include "qpu.c"
#include "../includes/main.h"
#include "../asm/assembler/asm.c"

const char* help = "\nFormat: qpu [asm/bin file location] [-d] [-t] [-s] [-h]"
                   "\n    [The default setting are: /programs/placeholder as binary, "
                                             "no disassembly, 10mhz speed, no tests.]"
                   "\nFlags: "
                   "\n-d - disassemble"
                   "\n    [creates a copy of the binary loaded with '_disasm' postfix in /asm]"
                   "\n-t - test"
                   "\n    [ignores all binaries, .s and runs specified tests to make sure"
                   "\n     that cpu actually works. If expected result (e.g. a value stored"
                   "\n     in a register) doesn't match actual result, test is marked as 'failed',"
                   "\n     then asks if user wants to use stepped mode and shows expected result"
                   "\n     and actual result for each cycle. Cpu also runs at full speed, that the"
                   "\n     host pc can handle. (ignores -s flag and specified speed)"
                   "\n-s - speed selection"
                   "\n    [-s0 - stepped,"
                   "\n     -s1 - 1mhz,"
                   "\n     -s2 - 10mhz, (default)"
                   "\n     -s3 - 100mhz,"
                   "\n     -s4 - no restrictions]"
                   "\n-h - help"
                   "\n    [ignores all other flags and prints allat]";

int main(int argc, char * argv[])
{
    // Handle arguments
    if (argc != 1)
    {

    }



    // so shit won't close
    printf("\n%i %i %i %c", emu_flags.disassemble, emu_flags.assemble, emu_flags.test, emu_flags.speed);
    wait_for_enter();
    return 0;
}