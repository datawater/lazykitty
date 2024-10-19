#include "workshy.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

result_t new_result() {
    char* error = malloc(sizeof(char) * 256);
    assert(error != NULL);
    
    memset(error, 0, sizeof(char) * 256);

    result_t result = {0};
    result.result = unknown;
    result.error = error;

    return result;
}

result_t new_result_error(char* error) {
    result_t result = new_result();

    if (error != NULL)
        result.error = error;

    result.result = fail;
    return result;
}

result_t new_result_ok() {
    result_t result = new_result();
    result.result = ok;

    return result;
}

const char* workshy_result_to_string(result_e result) {
    static const char* result_to_string[] = {
        "ok", "error"
    };

    return result_to_string[result];
}