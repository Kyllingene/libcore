alias build := static
alias b := static
alias d := dynamic
alias t := test
alias a := all
alias c := clean

CC := "g++"
OBJFLAGS := "-c -fPIC -m"
OUTFLAGS := "-fPIC -m"

arch := `uname -m | grep -o "64" || echo "32"`

# Build libcore as a static library.
static target=arch: (build-temp target)
    rm -f build/libcore{{target}}.a
    ar rcs build/libcore{{target}}.a temp/**/*.o

# Build libcore as a shared library.
dynamic target=arch: (build-temp target)
    rm -f build/libcore{{target}}.so
    {{CC}} {{OUTFLAGS}}{{target}} -fPIC -shared -o build/libcore{{target}}.so temp/**/*.o

# Run test/test.c; use for dev purposes only!
test target=arch: (static target)
    {{CC}} test/test.cpp -o test/test -static -Lbuild -lcore{{target}}
    test/test

build-temp target=arch:
    rm -rf temp
    
    mkdir -p temp/malloc
    mkdir temp/io
    mkdir temp/str
    mkdir temp/mem
    mkdir -p build

    {{CC}} {{OBJFLAGS}}{{target}} src/malloc/brk{{target}}.s -o temp/malloc/brk{{target}}.o
    {{CC}} {{OBJFLAGS}}{{target}} src/malloc/malloc.cpp -o temp/malloc/malloc.o
    {{CC}} {{OBJFLAGS}}{{target}} src/mem/mem.cpp -o temp/mem/mem.o
    {{CC}} {{OBJFLAGS}}{{target}} src/io/print{{target}}.s -o temp/io/print{{target}}.o
    {{CC}} {{OBJFLAGS}}{{target}} src/io/print.cpp -o temp/io/print.o
    {{CC}} {{OBJFLAGS}}{{target}} src/str/str.cpp -o temp/str/str.o

# Build all targets, both static and dynamic.
all: (all-32) (all-64)

# Build static and dynamic for 32-bit.
all-32: (static "32") (dynamic "32")

# Build static and dynamic for 64-bit.
all-64: (static "64") (dynamic "64")

# Remove all build fragments.
clean:
    rm -rf build temp test/test **/*.o **/*.so **/*.a
