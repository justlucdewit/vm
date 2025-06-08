#pragma once

#include "stdio.h"
#include "stdlib.h"

char* load_file_contents(char* filepath) {
    char* file_contents;

    // Load the file into memory
    FILE* file = fopen(filepath, "rb");
    if (file == NULL) {
        printf("Error: Could not open file '%s'\n", filepath);
        return NULL;
    } else {
        printf("Loading file: '%s'\n", filepath);

        fseek(file, 0, SEEK_END);
        long filesize = ftell(file);
        rewind(file);

        file_contents = (char*) malloc(filesize + 1);
        fread(file_contents, 1, filesize, file);
        file_contents[filesize] = '\0';
        fclose(file);

        return file_contents;
    }
}