include config.mk

LAZYKITTY_SOURCE_FILES = $(wildcard src/*.c)
LAZYKITTY_OBJECT_FILES = $(patsubst %.c,%.o,$(LAZYKITTY_SOURCE_FILES))

main: check_error lazykitty
test: workshy
	make -C ./src/tests

lazykitty: $(LAZYKITTY_OBJECT_FILES)
	$(CC) $(CFLAGS) $^ -o $@

workshy:
	make -C ./src/workshy

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

check_error:
ifeq ($(IS_ERROR),1)
	$(info $(ERROR_TEXT))
else
endif

clean:
	-find . -type f -name "*.o" -delete
	-rm lazykitty

	-make -C ./src/workshy clean
	-make -C ./src/tests clean