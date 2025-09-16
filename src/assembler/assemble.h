#pragma once

#include "parser.h"

// Converts a register like a b c or d to a byte value 0 1 2 3
uint8_t register_to_byte(char* r) {
    if (strcmp(r, "a") == 0) return 0x00;
    if (strcmp(r, "b") == 0) return 0x01;
    if (strcmp(r, "c") == 0) return 0x02;
    if (strcmp(r, "d") == 0) return 0x03;

    printf("[error] Unknown register %s\n", r);
    return 0xFF;
}

void assemble_parseresult(ParserResult parserResult, char* output_filename) {
    // Buffer to store the output bytes
    uint8_t* output_bytes = create_list_of(uint8_t, output_bytes, 100);

    uint8_t instruction_to_opcode_map[] = {};

    // MOV instructions
    instruction_to_opcode_map[IT_MOV_REG_INT] = 0x01;

    // Loop trough each instruction and convert to bytes
    for (uint32_t i = 0; i < parserResult.instruction_count; i++) {
        Instruction inst = parserResult.instructions[i];

        // Check what instruction it is
        if (inst.type == IT_MOV_REG_INT) { // 0x00 [register] [int32]
            // Opcode for MOV_REG_INT
            uint8_t opcode = instruction_to_opcode_map[IT_MOV_REG_INT];
            insert_at_end(uint8_t, output_bytes, opcode);

            // Register
            uint8_t reg_byte = register_to_byte(inst.arguments[0]);
            insert_at_end(uint8_t, output_bytes, reg_byte);

            // Integer (4 bytes, big endian)
            int32_t int_value = atoi(inst.arguments[1]);
            insert_at_end(uint8_t, output_bytes, (int_value >> 24) & 0xFF);
            insert_at_end(uint8_t, output_bytes, (int_value >> 16) & 0xFF);
            insert_at_end(uint8_t, output_bytes, (int_value >> 8) & 0xFF);
            insert_at_end(uint8_t, output_bytes, int_value & 0xFF);
        } else if (inst.type == IT_MOV_REG_REG) {
            // Opcode for MOV_REG_REG
            insert_at_end(uint8_t, output_bytes, inst.type);

            // Register
            uint8_t reg_byte = register_to_byte(inst.arguments[0]);
            insert_at_end(uint8_t, output_bytes, reg_byte);

            // Second Register
            reg_byte = register_to_byte(inst.arguments[1]);
            insert_at_end(uint8_t, output_bytes, reg_byte);
        } else {
            printf("[error] Unknown instruction type %d\n", inst.type);
        }
    }

    // Write the output bytes to a file
    FILE* output_file = fopen(output_filename, "wb");
    fwrite(output_bytes, sizeof(uint8_t), output_bytes_count, output_file);
    fclose(output_file);
}