include ../config.mk

TEST_SOURCE_FILES = $(wildcard ./*.c)
TEST_OBJECT_FILES = $(patsubst %.c,%.o,$(TEST_SOURCE_FILES))
WORKSHY_PATH = ../workshy -Wno-unused-variable
CFLAGS += -L$(WORKSHY_PATH) -L./ -L../

.PHONY: main
main: check_error run_tests

.PHONY: run_tests
run_tests: libworkshy.a compile_tests

.PHONY: compile_tests
compile_tests: libtests.a
	$(CC) $(CFLAGS) $^ -o run_tests -lworkshy -ltests $(LIBS)

libworkshy.a:
	make -C ../

libtests.a: $(TEST_OBJECT_FILES)
	ar -crs $@ $^

./%.o: ./%.c
	$(CC) $(CFLAGS) $< -o $@ -c -fPIC

.PHONY: check_error
check_error:
ifeq ($(IS_ERROR),1)
	$(info $(ERROR_TEXT))
else
endif

.PHONY: clean
clean:
	-find . -type f -name "*.o" -delete
	-rm *.out
	-rm run_tests
	-rm *.a