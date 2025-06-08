#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool list_includes_string(const char* list[], char* str_a) {
    for (int i = 0; list[i] != NULL; i++) {
        const char* str_b = list[i];

        if (strcmp(str_a, str_b) == 0) {
            return true;
        }
    }

    return false;
}