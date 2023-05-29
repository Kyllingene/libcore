alias b := static

CC := "gcc"
CCFLAGS := "-c -m"

arch := `uname -m | grep -o "64" || echo "32"`

# Build libcore as a static library.
static target=arch:
    rm -rf temp
    
    mkdir -p temp/malloc
    mkdir -p build

    {{CC}} {{CCFLAGS}}{{target}} src/malloc/brk{{target}}.s -o temp/malloc/brk{{target}}.o
    {{CC}} {{CCFLAGS}}{{target}} src/malloc/malloc.c -o temp/malloc/malloc.o

    ar rcs build/libcore{{target}}.a temp/**/*.o

# Run test/test.c; use for dev purposes only!
test target=arch: (static target)
    {{CC}} test/test.c -o test/test -Lbuild -lcore{{arch}}
    test/test

clean:
    rm -rf build temp test/test
