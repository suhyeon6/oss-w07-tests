CC = gcc
CPPFLAGS = -Iinclude -Ivendor/stb
CFLAGS = -std=c11 -Wall -Wextra -g -O0
LDLIBS = -lm
.PHONY: all check unit-test batch-test clean
all: bin/image-lab
bin/image-lab: build/main.o build/filters.o build/image_io.o
	mkdir -p bin
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
build/main.o: src/main.c include/filters.h include/image_io.h
	mkdir -p build
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
build/filters.o: src/filters.c include/filters.h
	mkdir -p build
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
build/image_io.o: src/image_io.c include/image_io.h vendor/stb/stb_image.h vendor/stb/stb_image_write.h
	mkdir -p build
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
bin/test_filters: tests/test_filters.c build/filters.o include/filters.h
	mkdir -p bin
	$(CC) $(CPPFLAGS) $(CFLAGS) tests/test_filters.c build/filters.o -o $@
unit-test: bin/test_filters
	./bin/test_filters
batch-test: bin/image-lab
	bash tests/test_batch.sh
check: unit-test batch-test
clean:
	rm -f build/main.o build/filters.o build/image_io.o bin/image-lab bin/test_filters
