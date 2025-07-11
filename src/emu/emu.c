/*==============================================================================
 Copyright (c) 2025 Twink's Death
 SPDX-License-Identifier: BSD-3-Clause
 See the LICENSE file in repo's root for details.

 qpu8_emu: emu.c
 =============================================================================*/

// Project headers
#include "emulator/emu.h"
#include "assembler/asm.h"
#include "machine/qpu8.h"

// Help string
const char* help = "\nFormat: qpu [-d] [-s] [-t] [-h] [asm/bin file location]"
    "\n    [The default settings are: no disassembly, 10mhz speed]"
    "\nFlags: "
    "\n-d - disassemble"
    "\n    [creates a copy of the binary loaded with '_disasm' postfix in /asm]"
    "\n-s - speed selection"
    "\n    [-s0 - stepped,"
    "\n     -s1 - 1mhz,"
    "\n     -s2 - 10mhz, (default)"
    "\n     -s3 - 100mhz,"
    "\n     -s4 - no restrictions]"
    "\n-t - test"
    "\n    [ignores all binaries, .s and runs specified tests to make sure"
    "\n     that cpu actually works. If expected result (e.g. a value stored"
    "\n     in a register) doesn't match actual result, test is marked as 'failed',"
    "\n     then asks if user wants to use stepped mode and shows expected result"
    "\n     and actual result for each cycle. Cpu also runs at full speed, that the"
    "\n     host pc can handle. (ignores -s flag and specified speed) ]"
    "\n-h - help"
    "\n    [ignores all other flags and prints allat]\n";

// Takes in arguments from ** argv and sets emu_flags based on them:
// disassemble if -d flag present
// assemble    if input_file is .s
// unit tests  if -t flag present
// speed (mhz) if -s flag present, AND has a number from 0 to 4 inclusive after it
// print usage if -h flag present and quit
void
parse_flags ( int argc, char** argv, emu_flags_t* emu_flags )
{
    int option;
    while ((option = getopt(argc, argv, "dts:h")) != -1) {
        switch (option) {
            case 'd': emu_flags->disassemble = 1;
                break;
            case 't': emu_flags->test = 1;
                break;
            case 's': char* end;
                byte val = strtol(optarg, &end, 10);
                if (*end || val > 4) {
                    fprintf(stderr, "Invalid speed: '%s'\n", optarg);
                    exit(1);
                }
                emu_flags->speed = val;
                break;
            case 'h': printf(help);
                exit(0);
            case '?': printf(help);
                exit(1);
            default: fprintf(stderr, "What happened here?: %s:%d", __FILE__, __LINE__); // Mystery
                exit(1);
        }
    }

    // If there's another argument after flags
    if (optind < argc) {
        FILE* file = fopen(argv[optind], "r");
        if (!file) {
            perror(argv[optind]);
            exit(1);
        }
        fclose(file); // File exists, proceed

        // Check file extension
        // If ends with .s - enable assembler, if .bin - do nothing, else - throw error
        if (strcasecmp(argv[optind] + strlen(argv[optind]) - strlen(".s"), ".s") == 0) {
            emu_flags->assemble = 1;
        } else if (strcasecmp(argv[optind] + strlen(argv[optind]) - strlen(".bin"), ".bin") == 0) {
            ; // Pass
        } else {
            fprintf(stderr, "\n'%s' isn't a .s or .bin!\n", argv[optind]);
            exit(1);
        }
    } else {
        fprintf(stderr, "\nNo bin or asm file provided\n");
        exit(1);
    }

    // Fallback: if the only arguments are executable name and file path - no flags specified
    if (argc == 2)
        printf("\nNo flags specified! The emulator will run under default settings:"
            "\n[No disassembly, 10mhz speed]");


    printf("\nFound %s!\n", argv[optind]); // Success! Todo: remove later
    emu_flags->input_file = argv[optind]; // the first argv after the flags is the valid file path
}

int
main ( int argc, char* argv[] )
{
    // Default flags - no assembly, no disassembly, no tests, 10mhz clock speed, no file input nullptr
    emu_flags_t emu_flags = {false, false, false, 2, NULL};

    // Populate emu_flags, (dis)assemble based on them
    parse_flags(argc, argv, &emu_flags);
    if (emu_flags.assemble) assemble(emu_flags.input_file);
    else if (emu_flags.disassemble) disassemble(emu_flags.input_file);
    else {
        fprintf(stderr, "What happened here?: %s:%d", __FILE__, __LINE__); // Mystery
        exit(1);
    }

    return 0;
}
