#pragma once

#include "utils.h"
#include "pieces.h"
#include <stdint.h>

typedef u64 bitboard_t;

typedef struct board {
    bitboard_t pieces[12];
    bitboard_t side_pieces[2];
    bitboard_t all_pieces;

    bitboard_t attacks[2];

    bool can_castle[4];
    i8 en_passant_square;
} board_t;

board_t new_board();
char* board_to_string(board_t* board);
char* board_to_debug_string(board_t* board);
char* bitboard_to_string(bitboard_t bitboard);
char* bitboard_to_debug_string(bitboard_t bitboard);

bitboard_t mirror_bitboard_horizontally(bitboard_t x);

#define BITBOARD_FMT PRIu64
#define BOARD_T_FMT "board { pieces: [%lu, %lu, %lu, %lu, %lu, %lu, %lu, %lu, %lu, %lu, %lu, %lu], side_pieces: [%lu, %lu], all_pieces: %lu, attacks: [%lu, %lu], can_castle: [%d, %d, %d, %d], en_passant_square: %i }"
#define BOARD_T_CSTR(b) (b).pieces[0], (b).pieces[1], (b).pieces[2], (b).pieces[3], (b).pieces[4], (b).pieces[5], (b).pieces[6], (b).pieces[7], (b).pieces[8], (b).pieces[9], (b).pieces[10], (b).pieces[11], (b).side_pieces[0], (b).side_pieces[1], (b).all_pieces, (b).attacks[0], (b).attacks[1], (b).can_castle[0], (b).can_castle[1], (b).can_castle[2], (b).can_castle[3], (b).en_passant_square
