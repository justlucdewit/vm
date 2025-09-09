#pragma once

#include "lexical_analyzer.h"

typedef enum {
    IT_MOV_REG_INT,
    IT_MOV_REG_REG,
    IT_ADD_REG_REG,
    IT_SYSCALL,
    IT_EXIT,
} InstructionType;

typedef struct {
    InstructionType type;
    char* arguments[4];
} Instruction;

typedef struct {
    uint32_t instruction_count;
    Instruction* instructions;
} ParserResult;

ParserResult parse(TokenizationResult tokens) {
    Instruction* instructions = create_list_of(Instruction, instructions, 100);

    for (int i = 0; i < tokens.token_count; i++) {
        Token t = tokens.tokens[i++];

        if (!(t.token_type == TT_INSTRUCTION)) {
            printf("[error] Expected instruction token, got %s", stringify_token_type(t.token_type));
        }

        // Mov instruction
        if (strcmp(t.value, "mov") == 0) {
            Token arg1 = tokens.tokens[i++];
            Token arg2 = tokens.tokens[i++];

            if (arg1.token_type == TT_REGISTER && arg2.token_type == TT_INT_LITERAL) {
                Instruction instruction = {
                    .type = IT_MOV_REG_INT,
                    .arguments = { arg1.value, arg2.value }
                };

                insert_at_end(Instruction, instructions, instruction);
            }
        }
    }

    return (ParserResult) {
        instructions_count = instructions_count,
        instructions = instructions
    };
}

void print_instruction(Instruction inst) {
    if (inst.type == IT_MOV_REG_INT) {
        printf("MOV %s, %s\n", inst.arguments[0], inst.arguments[1]);
    }
}

void print_parse_result(ParserResult res) {
    puts("Parsed Instructions:");
    printf("Instruction Count: %d\n\n", res.instruction_count);
    
    for (int i = 0; i < res.instruction_count; i++) {
        Instruction inst = res.instructions[i];

        print_instruction(inst);
    }

    puts("");
}