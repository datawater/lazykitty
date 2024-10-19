#include "tests.h"
#include "../board.h"

result_t test_fen_parsing(void) {
    board_t starting_from_fen = new_board_from_fen(LK_STARTING_FEN);
    board_t starting_expected = new_starting_board();
    
    board_t blank_from_fen = new_board_from_fen(LK_EMPTY_FEN);
    board_t blank_expected = new_board();

    if (board_cmp(&starting_from_fen, &starting_expected) == 0) {
        return new_result_error("starting");
    }

    if (board_cmp(&blank_from_fen, &blank_expected) == 0) {
        return new_result_error("blank");
    }

    return new_result_ok();
}
