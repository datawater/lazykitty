#include <stdio.h>
#include "tests.h"

#include "../board.h"
#include <string.h>

result_t test_printing_bitboards(void) {
    bitboard_t board = 0x55aa55aa55aa55aa;

    char* debug_string = bitboard_to_debug_string(board);
    char* string = bitboard_to_string(board);

    char* expected_debug_string = 
        "x . x . x . x .\n"
        ". x . x . x . x\n"
        "x . x . x . x .\n"
        ". x . x . x . x\n"
        "x . x . x . x .\n"
        ". x . x . x . x\n"
        "x . x . x . x .\n"
        ". x . x . x . x\n";
    
    char* expected_string = "0b0101010110101010010101011010101001010101101010100101010110101010";

    bool debug_string_is_correct = strcmp(expected_debug_string, debug_string) == 0;
    bool string_is_correct = strcmp(expected_string, string) == 0;

    result_t result = new_result_error(NULL);

    // TODO: workshy: introduce a custom assert, so i don't have to manually write erorrs
    if (!debug_string_is_correct) {
        result.error = "debug_string is incorrect.";
        return result;
    }

    if (!string_is_correct) {
        result.error = "string is incorrect.";
        return result;
    }

    result.result = ok;

    return result;
}
