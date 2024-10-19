include config.mk

WORKSHY_SOURCE_FILES = $(wildcard ./src/*.c)
WORKSHY_OBJECT_FILES = $(patsubst %.c,%.o,$(WORKSHY_SOURCE_FILES))

CFLAGS += -Wno-unused-variable -Wno-pedantic

.PHONY: main
main: check_error libworkshy.a

libworkshy.a: $(WORKSHY_OBJECT_FILES)
	ar -crs $@ $^

src/%.o: src/%.c
	$(CC) $(CFLAGS) -fPIE -c $< -o $@

.PHONY: test
test:
	make -C ./examples

.PHONY: check_error
check_error:
ifeq ($(IS_ERROR),1)
	$(info $(ERROR_TEXT))
else
endif

.PHONY: clean
clean:
	-find . -type f -name "*.o" -delete
	-rm libworkshy.a

	make -C ./examples clean