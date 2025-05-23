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
    if (argc == 1)
        printf( "\nNo arguments specified! The cpu will run under default settings!"

                "\n[The default setting are: /programs/placeholder as binary, "
                            "no disassembly, 10mhz speed, no tests.]"               );
    else
    {
        int arg_start = 1; // ugly but necessary

        // First argument MIGHT be a file path
        if (argv[1][0] != '-')
        {
            // Try to open file to see if it exists
            const FILE *file = fopen(argv[1], "r");
            if (file == NULL)
            {
                fprintf(stderr, "\nError opening file %s", argv[1]);
                return 1;
            }
            arg_start = 2;
            printf("\nI've found %s!", argv[1]);
        }

        // First argument isn't a file path
        for (int i = arg_start; i < argc; i++)
        {
            // Set emulator flags based on argv
            if ( strcmp(argv[i], "-d") == 0 )
                emu_flags.disassemble = true;
            else if ( strcmp(argv[i], "-t") == 0 )
                emu_flags.test = true;
            else if ( strncmp(argv[i], "-s", 2) == 0 )
                emu_flags.speed = argv[i][2];
            else if ( strcmp(argv[i], "-h") == 0 )
                printf(help);
            else
                printf("\n%s isn't a valid flag!\n%s", argv[i], help);
        }
    }

    // so shit won't close
    printf("\n%i %i %i %c", emu_flags.disassemble, emu_flags.assemble, emu_flags.test, emu_flags.speed);
    wait_for_enter();
    return 0;
}