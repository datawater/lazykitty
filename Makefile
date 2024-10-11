CFLAGS = -Wall -Wextra -Werror -std=c11
PROFILE_DEBUG_CFLAGS := -ggdb -O0
PROFILE_RELEASE_CFLAGS := -O3 -s -flto -mtune=native -march=native -fgraphite-identity
PROFILE_SIZE_CFLAGS := -Oz -s
PROFILE ?=debug

IS_ERROR = 0
ERROR_TEXT = ok

SOURCE_FILES = $(wildcard src/*.c)
OBJECT_FILES = $(patsubst %.c,%.o,$(SOURCE_FILES))

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

main: check_error lazykitty

lazykitty: $(OBJECT_FILES)
	$(CC) $(CFLAGS) $^ -o $@

build/%.o: src/%.c
	@-mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

check_error:
ifeq ($(IS_ERROR),1)
	$(info $(ERROR_TEXT))
else
endif

clean:
	-find . -type f -name "*.o" -delete
	-rm lazykitty