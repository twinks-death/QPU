#ifndef EMU_H
#define EMU_H

// Standard library
#include <assert.h>
#include <stdint.h>
#include <unistd.h>


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
    char* input_file;
} emu_flags_t;

// In emu.c
void parse_flags (int argc, char ** argv, emu_flags_t * emu_flags);

#endif //EMU_H
