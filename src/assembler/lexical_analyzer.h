#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "ldw_list.h"
#include "ldw_string.h"

#include "language.h"
#include "helpers.h"

typedef enum {
    TT_INT_LITERAL,
    TT_STRING_LITERAL,
    TT_INSTRUCTION,
    TT_PREPROCESSOR_COMMAND,
    TT_REGISTER,
    TT_IDENTIFIER,
    TT_UNKNOWN
} TokenType;

const char* stringify_token_type(TokenType tt) {
    if (tt == TT_INT_LITERAL)
        return "INTEGER";

    if (tt == TT_STRING_LITERAL)
        return "STRING";

    if (tt == TT_INSTRUCTION)
        return "INSTRUCTION";

    if (tt == TT_PREPROCESSOR_COMMAND)
        return "PREPROCESSOR_COMMAND";

    if (tt == TT_REGISTER)
        return "REGISTER";

    return "UNKNOWN";
}

typedef struct {
    char* value;      // Pointer to a string containing the value of this token
    u_int32_t line;     // The line at which this token is found in the source code
    u_int32_t col;      // The column at which this token is found in the source code
    TokenType token_type; // The type of the token
} Token;

typedef struct {
    Token* tokens;
    u_int32_t token_count;
} TokenizationResult;

TokenType determine_token_type(string token_value) {

    // Check if its a bad string
    if (token_value == NULL || token_value[0] == '\0')
        return TT_UNKNOWN;

    // Check if its a number
    if (token_value[0] >= '0' && token_value[0] <= '9') {
        return TT_INT_LITERAL;
    }

    // Check if its an instruction
    if (list_includes_string(instruction_list, token_value)) {
        return TT_INSTRUCTION;
    }

    // Check if its a register
    if (list_includes_string(register_list, token_value)) {
        return TT_REGISTER;
    }

    // Check if its a PP Command
    if (token_value[0] == '#') {
        bool found_illegal_char = false;
        for (int i = 1; token_value[i] != '\0'; i++) {
            char c = token_value[i];

            // Character may be a-z or A-Z or _
            // can also be a number
            if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' || (c >= '0' && c <= '9' && c >= 2))) {
                found_illegal_char = true;
            }
        }

        if (!found_illegal_char) {
            return TT_PREPROCESSOR_COMMAND;
        }
    }

    // TODO: Check if its an identifier

    return TT_UNKNOWN;
}

TokenizationResult tokenize_code(char* code) {
    // Dynamic list containing tokens
    Token* tokens = create_list_of(Token, tokens, 100);

    // Dynamic list containing current token value
    string token_value = create_list_of(char, token_value, 100);
    
    u_int32_t reading_index = 0;
    bool string_mode = false;
    bool comment_mode = false;

    while (reading_index < strlen(code)) {
        char current_char = code[reading_index++];

        if (string_mode) {
            if (current_char == '"') {
                // Get the final token value
                string final_token_value = strndup(token_value, token_value_count);

                // Create the new token
                Token new_token = {
                    .value = final_token_value,
                    .col = 0,
                    .line = 0,
                    .token_type = TT_STRING_LITERAL
                };

                // Insert new token in array
                insert_at_end(Token, tokens, new_token);

                // Reset the token value
                empty_list(char, token_value);
                
                string_mode = false;
                continue;
            }

            // Add to the token and continue to next char
            insert_at_end(char, token_value, current_char);
            continue;
        }

        if (comment_mode) {
            if (current_char == '\n') {
                comment_mode = false;
            }

            continue;
        }

        else {
            if (current_char == ';') {
                if (token_value_count > 0) {

                    // Get the final token value
                    string final_token_value = strndup(token_value, token_value_count);

                    // Create the new token
                    Token new_token = {
                        .value = final_token_value,
                        .col = 0,
                        .line = 0,
                        .token_type = determine_token_type(final_token_value)
                    };

                    // Insert new token in array
                    insert_at_end(Token, tokens, new_token);

                    // Reset the token value
                    empty_list(char, token_value);
                }

                comment_mode = true;
                continue;
            }

            if (current_char == '"') {
                if (token_value_count > 0) {

                    // Get the final token value
                    string final_token_value = strndup(token_value, token_value_count);

                    // Create the new token
                    Token new_token = {
                        .value = final_token_value,
                        .col = 0,
                        .line = 0,
                        .token_type = determine_token_type(final_token_value)
                    };

                    // Insert new token in array
                    insert_at_end(Token, tokens, new_token);

                    // Reset the token value
                    empty_list(char, token_value);
                }

                string_mode = true;
                continue;
            }

            if (current_char == ' ' || current_char == '\t' || current_char == '\n') {
                if (token_value_count > 0) {

                    // Get the final token value
                    string final_token_value = strndup(token_value, token_value_count);

                    // Create the new token
                    Token new_token = {
                        .value = final_token_value,
                        .col = 0,
                        .line = 0,
                        .token_type = determine_token_type(final_token_value)
                    };

                    // Insert new token in array
                    insert_at_end(Token, tokens, new_token);

                    // Reset the token value
                    empty_list(char, token_value);
                }

                continue;
            }

            // Add to the token and continue to next char
            insert_at_end(char, token_value, current_char);
        }
    }

    return (TokenizationResult) {
        .tokens = tokens,
        .token_count = tokens_count
    };
}

void print_tokens(TokenizationResult tr) {
    for (int i = 0; i < tr.token_count; i++) {
        Token t = tr.tokens[i];

        printf("Token::%s[%s]\n", stringify_token_type(t.token_type), t.value);
    }

    puts("");
}
