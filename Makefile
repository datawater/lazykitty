include config.mk

LAZYKITTY_SOURCE_FILES = $(wildcard src/*.c)
LAZYKITTY_OBJECT_FILES = $(patsubst %.c,%.o,$(LAZYKITTY_SOURCE_FILES))

.PHONY: main
main: check_error lazykitty

.PHONY: test
test: workshy
	make -C ./src/tests

lazykitty: $(LAZYKITTY_OBJECT_FILES)
	$(CC) $(CFLAGS) $^ -o $@

liblazykitty.a: $(LAZYKITTY_OBJECT_FILES)
	ar -crs $@ $^

workshy:
	make -C ./src/workshy

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: check_error
check_error:
ifeq ($(IS_ERROR),1)
	$(info $(ERROR_TEXT))
else
endif

.PHONY: clean
clean:
	-find . -type f -name "*.o" -delete
	-rm lazykitty
	-rm *.a

	-make -C ./src/workshy clean
	-make -C ./src/tests clean