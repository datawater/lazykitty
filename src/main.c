#include "utils.h"
#include "board.h"
#include <signal.h>

static void handle_abort(int sig) {
    UNUSED(sig);
    printf("CAUGHT SIGABORT\n");

    exit(1);
}

int main(int argc, char** argv) {
    signal(SIGABRT, handle_abort);

    UNUSED(argc);
    UNUSED(argv);

    bitboard_t board = 0x55aa55aa55aa55aa;
    printf("%s\n", bitboard_to_debug_string(board));

    printf("raising SIGABRT\n");
    fflush(stdout);
    abort();

    return 0;
}