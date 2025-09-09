#include <stdio.h>
#include "testing_repl.h"

#include "lexical_analyzer.h"
#include "preprocess.h"
#include "file_loader.h"
#include "parser.h"
#include "assemble.h"

char* get_output_file_name(char* input_file_name) {
    char* dot_position = strrchr(input_file_name, '.');
    
    size_t base_name_length = (dot_position != NULL) ? (dot_position - input_file_name) : strlen(input_file_name);
    
    // Allocate memory for the output file name (base_name_length + ".ccb" + null terminator)
    char* output_file_name = (char*)malloc(base_name_length + 5);
    
    // Copy the base name
    strncpy(output_file_name, input_file_name, base_name_length);
    output_file_name[base_name_length] = '\0'; // Null-terminate the string
    
    // Append the new extension
    strcat(output_file_name, ".ccb");
    
    return output_file_name;
}

int main(int argc, char** argv) {

    // If no arguments were given, start a testing REPL for lexing, parsing, and assembling the CCA code to binary
    if (argc == 1) {
        start_testing_repl();
    } else {
        // A program was given, assemble that to CCBytecode
        char* file_name = argv[1];
        char* raw_code = load_file_contents(file_name);

        // Tokenize and pre-process
        TokenizationResult tokenizationResult = tokenize_code(raw_code);
        tokenizationResult = preprocess_tokens(tokenizationResult);

        // Parse and assemble
        ParserResult parserResult = parse(tokenizationResult);
        assemble_parseresult(parserResult, get_output_file_name(file_name));
    }

    return 0;
}

