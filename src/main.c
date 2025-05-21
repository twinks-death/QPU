#include "..\asm\assembler\asm.c"
#include "qpu.c"

const char* help = "\nFormat: qpu [-a] [asm file location] [-d] [binary location] [-t] [-s] [-h]"
                   "\n    [The default setting are: /programs/placeholder as binary, "
                                             "no disassembly, 10mhz speed, no tests.]"
                   "\nFlags: "
                   "\n-a - assemble"
                   "\n    [location of .s to be assembled]"
                   "\n    [creates a binary with '_bin' postfix in /programs]"
                   "\n-d - disassemble"
                   "\n    [creates a copy of the binary loaded with '_disasm' postfix in /asm]"
                   "\n    [ignored if binary not specified]"
                   "\n[location of the binary to be run.]"
                   "\n If not specified, defaults to placeholder in /programs]"
                   "\n-t - test"
                   "\n    [ignores all binaries, .s and runs specified tests to make sure"
                   "\n     that cpu actually works. If expected result (e.g. a value stored"
                   "\n     in a register) doesn't match actual result, test is marked as 'failed',"
                   "\n     then asks if user wants to use stepped mode and shows expected result"
                   "\n     and actual result for each cycle. Cpu also runs at full speed, that the"
                   "\n     host pc can handle. (ignores -s flag and specified speed)"
                   "\n-s - speed selection"
                   "\n    [-s0 - stepped,"
                   "\n     -s1 - 1khz,"
                   "\n     -s2 - 1mhz,"
                   "\n     -s3 - 10mhz, (default)"
                   "\n     -s4 - 100mhz,"
                   "\n     -s5 - no restrictions]"
                   "\n-h - help"
                   "\n    [ignores all other flags and prints allat]";

// Clears the terminal.
// If platform is Windows - uses system cls,
// Otherwise              - uses system clear.
void clear_terminal(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main(int argc, char * argv[]) {

    // handle arguments
    if (argc == 1)
        printf("\nNo arguments specified! The cpu will run under default settings!");

    else if (argc > 1 || argc < 9)
        for (int i = 0; i < argc; i++)
        {
            // assemble
            if (strcmp(argv[i], "-a") == 0)
            {
                emu_flags.assemble = true;

                if (i + 1 >= argc || argv[i + 1][0] == '-')
                    fprintf(stderr, "\nError: -a requires a file path\n");
                    return 1;
                emu_flags.assemble_file = argv[++i];

                // Try to open the file to check if it exists
                FILE *file = fopen(emu_flags.assemble_file, "r");
                if (file == NULL)
                    fprintf(stderr, "\nError opening file %s\n", emu_flags.assemble_file);
                    return 1;
                fclose(file);
            }

            else if (strcmp(argv[i], "-d") == 0)
            {
                emu_flags.disassemble = true;

                if (i + 1 >= argc || argv[i + 1][0] == '-')
                    fprintf(stderr, "\nError: -d requires a file path\n");
                return 1;
                emu_flags.disassemble_output = argv[++i];

                // Try to open the file to check if it exists
                FILE *file = fopen(emu_flags.disassemble_output, "r");
                if (file != NULL) {
                    printf("\nFile %s already exists! Overwrite? (y/n) ", emu_flags.disassemble_output);
                }
                fclose(file);
            }
        }

    // so shit won't close
    while (getchar() != '\n');
    clear_terminal();
    return 0;
}