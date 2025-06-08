#include <stdio.h>
#include "testing_repl.h"

int main(int argc, char** argv) {

    // If no arguments were given, start a testing REPL for lexing, parsing, and assembling the CCA code to binary
    if (argc == 1) {
        start_testing_repl();
    } else {
        // A program was given, assemble that to CCBytecode

        // Todo: Read the program from file as string
        // Todo: Use lexical analyzer to tokenize the program
        // Todo: Apply preprocessor on lexes array
        // Todo: Parse lexes array to list of instructions
        // Todo: Transform list of instructions to output bytecode
        // Todo: Write raw bytecode to .bcc file in order to be ran by the CCVM
    }

    return 0;
}

