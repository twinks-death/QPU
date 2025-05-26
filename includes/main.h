// Utilities for main.c

#ifndef MAIN_H
#define MAIN_H


// Help string
const char* help = "\nFormat: qpu [-d] [-t] [-s] [-h] [asm/bin file location]"
                   "\n    [The default settings are:"
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
                   "\n    [ignores all other flags and prints allat]\n";


// Clears the terminal
// If Windows - uses system cls,
// else       - uses system clear
void
clear_terminal( void )
{
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

// Parses strings from *argv[] and sets emu_flags based on them
// Modifies: struct emu_flags
// argv[optint] holds the valid file path after execution of function
void
parse_flags( int argc,  char **argv )
{
    // Parsing flags...
    int option;
    while ((option = getopt(argc,  argv, "dts:h")) != -1)
    {
        switch (option)
        {
            // Disassemble
            case 'd': emu_flags.disassemble = 1; break;

            // Run tests
            case 't': emu_flags.test = 1; break;

            // Speed selection
            case 's':
                char *end;
                byte val = strtol(optarg, &end, 10);
                if (*end || val < 0 || val > 4) {
                    fprintf(stderr, "Invalid speed: '%s'\n", optarg);
                    exit(1);
                }
                emu_flags.speed = val; break;

            // Print help string
            case 'h': printf(help); exit(0);

            // Unknown option
            case '?':
                printf(help); exit(1);

            // Mystery
            default:
                printf("what happened here?"); break;
        }
    }

    // If there's another argument after flags
    if (optind < argc) {
        // Check if it's a valid file path
        FILE *file = fopen(argv[optind], "r");
        if (!file) {
            perror(argv[optind]);
            exit(1); // It's not!
        }
        fclose(file); // It IS!

        // Check file extension
        // If ends with .s, enable assembler
        if (strcasecmp(argv[optind] + strlen(argv[optind]) - strlen(".s"), ".s") == 0)
        {
            emu_flags.assemble = 1;
        }
        // If ends with .bin, do nothing
        else if  (strcasecmp(argv[optind] + strlen(argv[optind]) - strlen(".bin"), ".bin") == 0)
        {
            ; // Pass
        }
        // Else - invalid file extension
        else
        {
            fprintf(stderr, "\n'%s' isn't a .s or .bin!\n", argv[optind]);
            exit(1);
        }

    }
    else
    {
        printf("\nNo bin or asm file provided\n"); exit(1);
    }

    // If we reached this, then its successful.
    printf("\nFound %s!\n", argv[optind]);
}

#endif //MAIN_H
