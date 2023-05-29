alias build := static
alias b := static
alias d := dynamic
alias t := test
alias a := all
alias c := clean

CC := "g++"
OBJFLAGS := "-ggdb -c -fPIC -m"
OUTFLAGS := "-ggdb -fPIC -m"

arch := `uname -m | grep -o "64" || echo "32"`

# Build libcore as a static library.
static target=arch: (build-temp target)
    rm -f build/libcore{{target}}.a
    ar rcs build/libcore{{target}}.a `find temp -type f -name "*.o"`

# Build libcore as a shared library.
dynamic target=arch: (build-temp target)
    rm -f build/libcore{{target}}.so
    {{CC}} {{OUTFLAGS}}{{target}} -fPIC -shared -o build/libcore{{target}}.so `find temp -type f -name "*.o"`

# Run test/test.cpp; use for dev purposes only, it's not git tracked!
test target=arch: (static target)
    {{CC}} -ggdb test/test.cpp -o test/test -static -Lbuild -lcore{{target}}
    test/test

build-temp target=arch:
    rm -rf temp
    mkdir -p build

    for file in `find src -type f -name "*.c*"`; do \
    mkdir -p "temp/`dirname $file`"; \
    name=`basename $file`; \
    {{CC}} {{OBJFLAGS}}{{target}} "$file" -o "temp/${file%.*}.o"; \
    done

    for file in `find src -type f -name "*{{target}}.s"`; do \
    mkdir -p "temp/`dirname $file`"; \
    name=`basename $file`; \
    {{CC}} {{OBJFLAGS}}{{target}} "$file" -o "temp/${file%.*}.o"; \
    done

# Build all targets, both static and dynamic.
all: (all-32) (all-64)

# Build static and dynamic for 32-bit.
all-32: (static "32") (dynamic "32")

# Build static and dynamic for 64-bit.
all-64: (static "64") (dynamic "64")

# Remove all build fragments.
clean:
    rm -rf build temp test/test **/*.o **/*.so **/*.a
