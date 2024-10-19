#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "board.h"
#include "pieces.h"
#include "utils.h"

board_t new_board_from_fen(char* fen) {
    assert(fen != NULL);

    static const piece_e char_to_piece['r' + 1] = {
        ['P'] = white_pawn,
        ['N'] = white_knight,
        ['B'] = white_bishop,
        ['R'] = white_rook,
        ['Q'] = white_queen,
        ['K'] = white_king,

        ['p'] = black_pawn,
        ['n'] = black_knight,
        ['b'] = black_bishop,
        ['r'] = black_rook,
        ['q'] = black_queen,
        ['k'] = black_king,
    };

    u8 rank = 7;
    u8 file = 0;
    board_t b = new_board();

    for (size_t i = 0; i < strlen(fen); i++) {
        char c = fen[i];

        if (c == '/') {
            rank--;
            file = 0;
            continue;
        }

        if (isdigit(c)) {
            u8 as_number = c - '1';
            file += as_number;
            continue;
        }

        if (c == ' ') {
            i++;

            b.side = fen[i++] == 'w' ? white : black;

            i++;

            while (fen[i] != ' ' && i < strlen(fen)) {
                if (fen[i] == '-')
                    break;

                if (fen[i] == 'K') b.can_castle[white_kingside]  = true;
                if (fen[i] == 'Q') b.can_castle[white_queenside] = true;
                if (fen[i] == 'K') b.can_castle[black_kingside]  = true;
                if (fen[i] == 'Q') b.can_castle[black_queenside] = true;

                i++;
            }

            i++;

            if (fen[i] != '-')
                b.en_passant_square = (fen[i + 1] - '1') * 8 + (fen[i] - 'a');
            
            break;
        }

        if (isalpha(c)) {
            bitboard_t square = 1ULL << (rank * 8 + file);

            b.pieces[char_to_piece[(int) c]]  |= square;
            b.side_pieces[white + islower(c)] |= square;
            b.all_pieces                      |= square; 
        }

        file++;
    }

    return b;
}

char* board_to_debug_string(board_t* board) {
    static const char piece_to_char[none_piece] = {
        [white_pawn]   = 'P',
        [white_knight] = 'N',
        [white_bishop] = 'B',
        [white_rook]   = 'R',
        [white_queen]  = 'Q',
        [white_king]   = 'K',

        [black_pawn]   = 'p',
        [black_knight] = 'n',
        [black_bishop] = 'b',
        [black_rook]   = 'r',
        [black_queen]  = 'q',
        [black_king]   = 'k',
    };

    char strings[64][3] = {0};
    for (u8 x = 0; x < 64; x++)
        strcpy(strings[x], ". ");

    for (u8 i = 0; i < 64; i++) {
        if ((i + 1) % 8 == 0)
            strings[i][1] = '\n';       
    }

    for (piece_e i = white_pawn; i < none_piece; i++) {
        bitboard_t bitboard = board->pieces[i];

        for (u8 x = 0; x < 64; x++) {
            strings[x][0] = ((LK_POPCNT_N_TO_SQUARE_BB(x) & bitboard) == 0) ? 
                strings[x][0] : piece_to_char[i];    
        }
    }

    char* string = malloc(sizeof(char) * 129);
    assert(string != NULL);
    memset(string, 0, sizeof(char) * 129);

    for (u8 x = 0; x < 64; x++) {
        string[x * 2 + 0] = strings[x][0];
        string[x * 2 + 1] = strings[x][1];
    }

    return string;
}

char* bitboard_to_debug_string(bitboard_t bitboard) {
    char* strings[64];

    for (u8 x = 0; x < 64; x++) {
        strings[x] = malloc(sizeof(char) * 2);
        assert(strings[x] != NULL);
        memset(strings[x], 0, 2);
    }

    for (u8 x = 0; x < 64; x++) {
        char last_char = ' ';
        if ((x + 1) % 8 == 0) {
            last_char = '\n';
        }
        
        strings[x][0] = ((LK_POPCNT_N_TO_SQUARE_BB(x) & bitboard) == 0) ? '.' : 'x';
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