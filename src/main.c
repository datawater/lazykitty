#include "utils.h"
#include "board.h"

int main(int argc, char** argv) {

    UNUSED(argc);
    UNUSED(argv);

    board_t board = new_board_from_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    char* debug_string = board_to_debug_string(&board);
    printf("%s\n", debug_string);

    return 0;
}
