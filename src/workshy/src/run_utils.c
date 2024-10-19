#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "run_utils.h"

static FILE* __workshy_stdout;
static FILE* __workshy_stderr;

void swap_with_dev_null(FILE** x, FILE** x_backup) {
    (void) x_backup;

    // TODO: workshy: think of an another way of to block std(out/err), get rid of /dev/null
    FILE* dev_null = fopen("/dev/null", "w");

    if (dev_null == NULL) {
        fprintf(stderr, "[workshy_err] Couldn't open '/dev/null'. error: %s\n", strerror(errno));
        abort();
    }

    *x_backup = *x;
    *x = dev_null;
}

// TODO: workshy: Add flag to disallow stdout blocking
void __workshy_block_stdout() {
    swap_with_dev_null(&stdout, &__workshy_stdout);
}

void __workshy_block_stderr() {
    swap_with_dev_null(&stderr, &__workshy_stderr);
}

void __workshy_unblock_stdout() {
    if (__workshy_stdout) {
        stdout = __workshy_stdout;
        __workshy_stdout = NULL;
    }
}

void __workshy_unblock_stderr() {
    if (__workshy_stderr) {
        stderr = __workshy_stderr;
        __workshy_stderr = NULL;
    }
}