#include "benches.h"
#include "../board.h"

// NOTE: this benchmark isn't really needed and will probably get deleted later.
//       it is needed as a test case for workshy
void bench_printing_bitboards(void) {
    bitboard_t board = 0x55aa55aa55aa55aa;

    WORKSHY_BLACK_BOX({
        volatile char* debug_string = bitboard_to_debug_string(board);
    });    
}