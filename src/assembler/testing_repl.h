#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "lexical_analyzer.h"
#include "preprocess.h"
#include "file_loader.h"

void start_testing_repl() {
    printf("CC Assembler REPL - Written by Luke_\n\n");
    char* loaded_code = NULL;

    while (1) {
        char input[900];
        char command[100];
        char arg_1[100];

        printf("> ");
        fgets(input, sizeof(input), stdin);

        // Get the command
        int arg_count = sscanf(input, "%99s %99s", command, arg_1) - 1;
        
        if (strcmp(command, "exit") == 0) {
            break;
        }

        else if (strcmp(command, "clear") == 0) {
            printf("\033[2J\033[H");
            fflush(stdout);
        }

        else if (strcmp(command, "load") == 0) {
            if (arg_count == 1) {
                free(loaded_code);
                loaded_code = load_file_contents(arg_1);

                printf("\n");
            }
            
            else {
                printf("Usage: load <filename>\n\n");
            }
        }

        else if (strcmp(command, "code") == 0) {
            printf("%s\n\n", loaded_code);
        }

        else if (strcmp(command, "lex") == 0) {
            TokenizationResult TokenizationResult = tokenize_code(loaded_code);
            print_tokens(TokenizationResult);   
        }

        else if (strcmp(command, "pp") == 0) {
            // Tokenize the code
            TokenizationResult TokenizationResult = tokenize_code(loaded_code);

            // Preprocess the tokens
            TokenizationResult = preprocess_tokens(TokenizationResult);

            // Print the tokens for debugging
            print_tokens(TokenizationResult);   
        }

        else if (strcmp(command, "help") == 0) {
            printf("exit\tExit the REPL\n");
            printf("clear\tWipe the terminal clear\n");
            printf("help\tShow this help message\n");
            printf("load\tLoad the file given as the first parameter\n");
            printf("code\tShow what code was loaded\n");
            printf("lex\tLexically analyze the given code\n\n");
            printf("pp\tPreProcess the given code\n\n");
        }

        else {
            printf("Error: unknown command: '%s'\n\n", command);
        }


    }
}