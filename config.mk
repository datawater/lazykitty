CFLAGS_WARNINGS = -Wall -Wextra -Werror -pedantic -Wstrict-aliasing -Wno-pointer-arith -Wno-variadic-macros -Wno-unused-command-line-argument
CFLAGS = $(CFLAGS_WARNINGS) -std=c11
PROFILE_DEBUG_CFLAGS := -ggdb -O0
PROFILE_RELEASE_CFLAGS := -O3 -s -flto -mtune=native -march=native -fgraphite-identity
PROFILE_SIZE_CFLAGS := -Oz -s
PROFILE ?=debug

IS_ERROR = 0
ERROR_TEXT = ok

ifeq ($(PROFILE),debug)
	CFLAGS += $(PROFILE_DEBUG_CFLAGS)
else
	ifeq ($(PROFILE),release)
		CFLAGS += $(PROFILE_RELEASE_CFLAGS)
	else
		ifeq ($(PROFILE),size)
			CFLAGS += $(PROFILE_SIZE_CFLAGS)
		else
			IS_ERROR =1
			ERROR_TEXT = [ERROR] Unknown profile "$(PROFILE)".
		endif
	endif
endif
