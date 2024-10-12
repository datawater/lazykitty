#include <assert.h>
#include <string.h>
#include "board.h"
#include "utils.h"

bitboard_t mirror_bitboard_horizontally(bitboard_t x) {
    u64 k1 = 0x5555555555555555ULL;
    u64 k2 = 0x3333333333333333ULL;
    u64 k4 = 0x0f0f0f0f0f0f0f0fULL;
    x = ((x >> 1) & k1) | ((x & k1) << 1);
    x = ((x >> 2) & k2) | ((x & k2) << 2);
    x = ((x >> 4) & k4) | ((x & k4) << 4);
    return x;
}

board_t new_board(void) {
    board_t board;
    memset(&board, 0, sizeof(board));

    board.en_passant_square = -1;

    return board;
}

board_t new_board_from_fen(char* fen) {
    assert(fen != NULL);

    lazykitty_todo("Implement FEN parsing to board_t");

    return (board_t) {0};
}

char* board_to_string(board_t* board) {
    assert(board != NULL);

    char* string = (char*) malloc(sizeof(char) * 256);

    sprintf(string, BOARD_T_FMT, BOARD_T_CSTR(*board));
    return string;
}

char* board_to_debug_string(board_t* board) {
    UNUSED(board);

    lazykitty_todo("TODO: Implement board to char piece string");

    return NULL;
}

char* bitboard_to_debug_string(bitboard_t bitboard) {
    char* strings[64];
    
    for (u8 x = 0; x < 64; x++) {
        strings[x] = malloc(sizeof(char) * 2);
        assert(strings[x] != NULL);
        memset(strings[x], 0, 2);
    }

    bitboard = mirror_bitboard_horizontally(bitboard);

    for (u8 x = 0; x < 64; x++) {
        char last_char = ' ';
        if ((x + 1) % 8 == 0) {
            last_char = '\n';
        }
        
        strings[x][0] = (((1 << x) & bitboard) == 0) ? '.' : 'x';
        strings[x][1] = last_char;
    }

    char* string = malloc(sizeof(char) * 129);
    assert(string != NULL);
    memset(string, 0, sizeof(char) * 129);

    for (u8 x = 0; x < 64; x++) {
        string[x * 2 + 0] = strings[x][0];
        string[x * 2 + 1] = strings[x][1];

        free(strings[x]);
    }

    return string;
}

char* bitboard_to_string(bitboard_t bitboard) {
    char* string = malloc(sizeof(char) * 67);
    assert(string != NULL);
    memset(string, 0, sizeof(char) * 67);

    sprintf(string, "0b" PRINTF_BINARY_PATTERN_INT64, PRINTF_BYTE_TO_BINARY_INT64(bitboard));

    return string;
}
