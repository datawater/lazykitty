include ../../config.mk

TEST_SOURCE_FILES = $(wildcard ./*.c)
TEST_OBJECT_FILES = $(patsubst %.c,%.o,$(TEST_SOURCE_FILES))
WORKSHY_PATH = ../workshy -Wno-unused-variable
CFLAGS += -L$(WORKSHY_PATH) -L./

main: check_error run_tests

run_tests: libtests.a
	$(CC) $(CFLAGS) $^ -o $@ -lworkshy -ltests

libtests.a: $(TEST_OBJECT_FILES)
	ar -crs $@ $^

./%.o: ./%.c
	$(CC) $(CFLAGS) $< -o $@ -c -fPIC

check_error:
ifeq ($(IS_ERROR),1)
	$(info $(ERROR_TEXT))
else
endif

clean:
	-find . -type f -name "*.o" -delete
	-rm *.out
	-rm run_tests
	-rm *.a