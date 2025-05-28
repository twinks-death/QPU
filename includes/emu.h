#ifndef EMU_H
#define EMU_H

// Help string
const char* help = "\nFormat: qpu [-d] [-s] [-h] [asm/bin file location]"
                   "\n    [The default settings are:"
                          "no disassembly, 10mhz speed]"
                   "\nFlags: "
                   "\n-d - disassemble"
                   "\n    [creates a copy of the binary loaded with '_disasm' postfix in /asm]"
                   "\n-s - speed selection"
                   "\n    [-s0 - stepped,"
                   "\n     -s1 - 1mhz,"
                   "\n     -s2 - 10mhz, (default)"
                   "\n     -s3 - 100mhz,"
                   "\n     -s4 - no restrictions]"
                   "\n-h - help"
                   "\n    [ignores all other flags and prints allat]\n";

// Types
typedef uint8_t byte;
typedef uint16_t word;

// Emulator flags
typedef struct {
    bool assemble;
    bool disassemble;
    bool test;
    byte speed;
    char *input_file;
} emu_flags_t;

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
// Modifies: struct emu_flags ( declared in main() )
void
parse_flags (int argc, char ** argv, emu_flags_t * emu_flags)
{
    int option;

    // Parsing flags...
    while ((option = getopt(argc,  argv, "dts:h")) != -1)
    {
        switch (option)
        {
            // Disassemble
            case 'd': emu_flags->disassemble = 1; break;

            // Run tests
            case 't': emu_flags->test = 1; break;

            // Speed selection
            case 's':
                char *end;
                byte val = strtol(optarg, &end, 10);
                if (*end || val < 0 || val > 4) {
                    fprintf(stderr, "Invalid speed: '%s'\n", optarg);
                    exit(1);
                }
                emu_flags->speed = val; break;

            // Print help string
            case 'h': printf(help); exit(0);

            // Unknown option
            case '?':
                printf(help); exit(1);

            // Mystery
            default:
                assert(0 && "parse flags went wrong!"); // Mystery
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
            emu_flags->assemble = 1;
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

    // If the only arguments are executable name and file path - no flags specified
    if ( argc == 2 )
        printf ("\nNo flags specified! The emulator will run under default settings:"
                "\n[No disassembly, 10mhz speed]");
    else
        printf("\nFound %s!\n", argv[optind]); // Success!

    emu_flags->input_file = argv[optind];
}

#endif //EMU_H
