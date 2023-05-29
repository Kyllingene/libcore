alias build := static
alias b := static
alias d := dynamic
alias c := clean

CC := "gcc"
OBJFLAGS := "-c -fPIC -m"
OUTFLAGS := "-fPIC -m"

arch := `uname -m | grep -o "64" || echo "32"`

# Build libcore as a static library.
static target=arch: (build-temp target)
    ar rcs build/libcore{{target}}.a temp/**/*.o

# Build libcore as a shared library.
dynamic target=arch: (build-temp target)
    {{CC}} {{OUTFLAGS}}{{target}} -shared -o build/libcore{{target}}.so temp/**/*.o

# Run test/test.c; use for dev purposes only!
test target=arch: (static target)
    {{CC}} test/test.c -o test/test -Lbuild -lcore{{arch}}
    test/test

build-temp target=arch:
    rm -rf temp
    
    mkdir -p temp/malloc
    mkdir -p build

    {{CC}} {{OBJFLAGS}}{{target}} src/malloc/brk{{target}}.s -o temp/malloc/brk{{target}}.o
    {{CC}} {{OBJFLAGS}}{{target}} src/malloc/malloc.c -o temp/malloc/malloc.o

# Remove all build fragments.
clean:
    rm -rf build temp test/test **/*.o **/*.so **/*.a
