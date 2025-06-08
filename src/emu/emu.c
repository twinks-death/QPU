/*==============================================================================
 qpu8_emu: emu.c, 2025-06-08, Sun 21:06+0100

 Copyright (C) 2025 Twink's Death

 This software is provided 'as-is', without any express or implied
 warranty. In no event will the authors be held liable for any damages
 arising from the use of this software.

 Permission is granted to anyone to use this software for any purpose,
 including commercial applications, and to alter it and redistribute it
 freely, subject to the following restrictions:

 1. The origin of this software must not be misrepresented; you must not
    claim that you wrote the original software. If you use this software
    in a product, an acknowledgment in the product documentation would be
    appreciated but is not required.
 2. Altered source versions must be plainly marked as such, and must not be
    misrepresented as being the original software.
 3. This notice may not be removed or altered from any source distribution.
 =============================================================================*/

// Project headers
#include "emulator/emu.h"
#include "assembler/asm.h"
#include "machine/qpu8.h"

// Help string
const char* help = "\nFormat: qpu [-d] [-s] [-t] [-h] [asm/bin file location]"
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
    "\n-t - test"
    "\n    [ignores all binaries, .s and runs specified tests to make sure"
    "\n     that cpu actually works. If expected result (e.g. a value stored"
    "\n     in a register) doesn't match actual result, test is marked as 'failed',"
    "\n     then asks if user wants to use stepped mode and shows expected result"
    "\n     and actual result for each cycle. Cpu also runs at full speed, that the"
    "\n     host pc can handle. (ignores -s flag and specified speed) ]"
    "\n-h - help"
    "\n    [ignores all other flags and prints allat]\n";

// Takes in arguments from *argv[] and sets emu_flags based on them:
// disassemble if -d flag present
// assemble    if input_file is .s
// unit tests  if -t flag present
// usage       if -h flag present
// speed (mhz) if -s flag present, AND has a number from 0 to 4 inclusive after it
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
        // Open the file and check if it exists
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

    // If the only arguments are executable name and file path - no flags specified
    if (argc == 2)
        printf("\nNo flags specified! The emulator will run under default settings:"
            "\n[No disassembly, 10mhz speed]");
    else printf("\nFound %s!\n", argv[optind]); // Success!

    emu_flags->input_file = argv[optind]; // the first argv after the flags is the valid file path
}

int
main ( int argc, char* argv[] )
{
    // Default flags - no assembly, no disassembly, no tests, 10mhz clock speed, no file input (nullptr)
    emu_flags_t emu_flags = {false, false, false, 2, nullptr};

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
