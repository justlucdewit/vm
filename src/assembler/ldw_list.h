// C list library
// written by Luke_

#include <stdlib.h>

#ifndef LDW_LIST
#define LDW_LIST

#define create_list_of(TYPE, identifier, capacity) (TYPE*) malloc(sizeof(TYPE) * capacity);u_int32_t identifier##_count = 0; u_int32_t identifier##_capacity = 100;
#define empty_list(TYPE, identifier) identifier = malloc(sizeof(TYPE) * identifier##_capacity); identifier##_count = 0;
#define scale_capacity(TYPE, identifier) resize_if_needed((void**)&identifier, &identifier##_capacity, identifier##_count + 1, sizeof(TYPE))
#define insert_at_end(TYPE, identifier, value) scale_capacity(TYPE, identifier); identifier[identifier##_count++] = value

void resize_if_needed(void** ptr, uint32_t* capacity, uint32_t length, size_t elem_size) {
    if (length >= *capacity - 1) {
        uint32_t new_capacity = (*capacity) * 3;
        *capacity = new_capacity;
        *ptr = realloc(*ptr, elem_size * new_capacity);
    }
}

#endif