#pragma once

#include "lexical_analyzer.h"
#include "file_loader.h"
#include "lexical_analyzer.h"

TokenizationResult preprocess_tokens(TokenizationResult original_tokens) {
    Token* new_tokens = create_list_of(Token, new_tokens, 100);

    for (int i = 0; i < original_tokens.token_count; i++) {
        Token t = original_tokens.tokens[i];

        // Iterate trough the tokens, watching for a pre processor command
        if (t.token_type == TT_PREPROCESSOR_COMMAND) {
            if (strcmp(t.value, "#import") == 0) {
                
                // Get arguments
                Token arg1 = original_tokens.tokens[++i];

                // Argument type error checking
                if (arg1.token_type != TT_STRING_LITERAL) {
                    printf("[error] Found enexpected token. Usage for '#import': #import \"path/to/file.cca\"");
                    continue;
                }

                // Do the actual import
                //  - Load the file
                //  - Tokenize it
                //  - Preprocess it recursively
                char* module_contents = load_file_contents(arg1.value);
                TokenizationResult module_tokens = tokenize_code(module_contents);
                module_tokens = preprocess_tokens(module_tokens);

                // Add tokens to list
                for (int j = 0; j < module_tokens.token_count; j++) {
                    Token mt = module_tokens.tokens[j];
                    insert_at_end(Token, new_tokens, mt);
                }
            } else {
                printf("[error] Undefined preprocessor command '%s'\n", t.value);
            }
        }
        
        // If its not a PPC, just add it to the new list
        else {
            insert_at_end(Token, new_tokens, t);
        }
    }

    return (TokenizationResult) {
        .tokens = new_tokens,
        .token_count = new_tokens_count
    };
}