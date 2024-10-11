include ../../config.mk

WORKSHY_SOURCE_FILES = $(wildcard ./*.c)
WORKSHY_OBJECT_FILES = $(patsubst %.c,%.o,$(WORKSHY_SOURCE_FILES))

CFLAGS += -Wno-unused-variable -Wno-pedantic

main: check_error libworkshy.a

libworkshy.a: $(WORKSHY_OBJECT_FILES)
	ar -crs $@ $^

./%.o: ./%.c
	$(CC) $(CFLAGS) -fPIE -c $< -o $@

check_error:
ifeq ($(IS_ERROR),1)
	$(info $(ERROR_TEXT))
else
endif

clean:
	-find . -type f -name "*.o" -delete
	-rm libworkshy.a