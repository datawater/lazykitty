#pragma once

#include "utils.h"
#include "pieces.h"
#include <stdint.h>
#include <string.h>

// MACROS

#define BITBOARD_FMT PRIu64
#define BOARD_T_FMT "board { pieces: [%lu, %lu, %lu, %lu, %lu, %lu, %lu, %lu, %lu, %lu, %lu, %lu], side_pieces: [%lu, %lu], all_pieces: %lu, attacks: [%lu, %lu], can_castle: [%d, %d, %d, %d], en_passant_square: %i }"
#define BOARD_T_CSTR(b) (b).pieces[0], (b).pieces[1], (b).pieces[2], (b).pieces[3], (b).pieces[4], (b).pieces[5], (b).pieces[6], (b).pieces[7], (b).pieces[8], (b).pieces[9], (b).pieces[10], (b).pieces[11], (b).side_pieces[0], (b).side_pieces[1], (b).all_pieces, (b).attacks[0], (b).attacks[1], (b).can_castle[0], (b).can_castle[1], (b).can_castle[2], (b).can_castle[3], (b).en_passant_square

#define LK_STRING_SQUARE_TO_N(x)    ((x)[0] - 'a' + (7 - (x)[1] + '1') * 8)
#define LK_STRING_SQUARE_TO_BB(x)   (UINT64_C(1) << LK_STRING_SQUARE_TO_N((x)))
#define LK_POPCNT_N_TO_NATIVE_N(x)  ((x % 8) + ((7 - ((x) / 8)) * 8))
#define LK_POPCNT_N_TO_SQUARE_BB(x) (UINT64_C(1) << LK_POPCNT_N_TO_NATIVE_N((x)))

#define EMPTY_BB UINT64_C(0)
#define BB(x) (UINT64_C(x))

#define LK_STARTING_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
#define LK_EMPTY_FEN "8/8/8/8/8/8/8/8 w - - 0 1"

// TYPES

typedef u64 bitboard_t;

typedef struct board {
    bitboard_t pieces[12];
    bitboard_t side_pieces[2];
    bitboard_t all_pieces;

    bitboard_t attacks[2];

    bool can_castle[4];
    i8 en_passant_square;

    color_e side;
} board_t;

// FUNCTION DECLERATIONS

board_t new_board_from_fen(char* fen);
char* board_to_debug_string(board_t* board);
char* bitboard_to_debug_string(bitboard_t bitboard);

// INLINE FUNCTIONS

static inline int board_cmp(board_t* rhs, board_t* lhs) {
    return memcmp(lhs, rhs, sizeof(board_t));
}

static inline board_t new_board(void) {
    board_t board;
    memset(&board, 0, sizeof(board));

    board.en_passant_square = -1;

    return board;
}

static inline char* board_to_string(board_t* board) {
    assert(board != NULL);

    char* string = (char*) malloc(sizeof(char) * 512);

    sprintf(string, BOARD_T_FMT, BOARD_T_CSTR(*board));
    return string;
}

static inline char* bitboard_to_string(bitboard_t bitboard) {
    char* string = (char*) malloc(sizeof(char) * 67);
    assert(string != NULL);
    memset(string, 0, sizeof(char) * 67);

    sprintf(string, "0b" PRINTF_BINARY_PATTERN_INT64, PRINTF_BYTE_TO_BINARY_INT64(bitboard));

    return string;
}

static inline board_t new_starting_board(void) {
    return (board_t) {
        .pieces = {
            [white_pawn]   = BB(0xff000000000000),
            [white_knight] = BB(0x4200000000000000),
            [white_bishop] = BB(0x2400000000000000),
            [white_rook]   = BB(0x8100000000000000),
            [white_queen]  = BB(0x800000000000000),
            [white_king]   = BB(0x1000000000000000),

            [black_pawn]   = BB(0xff00),
            [black_knight] = BB(0x42),
            [black_bishop] = BB(0x24),
            [black_rook]   = BB(0x81),
            [black_queen]  = BB(0x8),
            [black_king]   = BB(0x10),
        },
        
        .side_pieces = {
            [white] = BB(0xffff000000000000), 
            [black] = BB(0xffff)
        },

        .all_pieces = BB(0xffff00000000ffff),
        // ! TODO
        .attacks = {0},
        .side = white,
        .can_castle = {
            [white_kingside]  = true,
            [white_queenside] = true,

            [black_kingside]  = true,
            [black_queenside] = true
        }
    };
}