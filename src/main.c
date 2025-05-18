#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "..\asm\assembler\asm.c"

const char* help = "\nFormat: qpu [-a] [asm file location] [-d] [binary location] [-t] [-s] [-h]"
                   "\n  The default setting are: /programs/placeholder as binary, no disassembly, 10mhz speed, no tests."
                   "\nFlags: "
                   "\n-a - assemble"
                   "\n    [location of .s to be assembled]"
                   "\n-d - disassemble"
                   "\n    [creates a copy of the binary loaded with '_disasm' postfix]"
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

// clear terminal macro
// if windows - uses system cls, otherwise - system clear.
void clear_terminal(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


int main(int argc, char *argv[]) {
    // handle arguments
    if (argc == 1)
        printf("No arguments specified! The cpu will run under default settings!"
             "\nAssemble? No! \nDisassemble? No! \nBinary location? ../programs/placeholder! \nTest? No! \nSpeed? 10mhz!"
             "\nPress enter to continue");
    else
        printf("\nHuh!");

    // so shit won't close
    while (getchar() != '\n');
    clear_terminal();
    return 0;
}