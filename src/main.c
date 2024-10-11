#include "utils.h"
#include "board.h"

int main(int argc, char** argv) {

    UNUSED(argc);
    UNUSED(argv);

    bitboard_t board = 0x55aa55aa55aa55aa;
    printf("%s\n", bitboard_to_debug_string(board));

    return 0;
}