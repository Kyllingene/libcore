alias build := static
alias b := static
alias d := dynamic
alias t := test
alias a := all
alias c := clean

CC := "g++"
OBJFLAGS := "-c -fPIC -m"

arch := `uname -m | grep -o "64" || echo "32"`

# Build as a static library.
static target=arch: (build-temp target)
    rm -f build/libcore{{target}}.a
    gcc-ar rcs build/libcore{{target}}.a `find temp -type f -name "*.o"`

# Build as a shared library.
dynamic target=arch: (build-temp target)
    rm -f build/libcore{{target}}.so
    {{CC}} -m{{target}} -fPIC -shared -o build/libcore{{target}}.so `find temp -type f -name "*.o"`

# Run test/test.cpp; use for dev purposes only, it's not git tracked!
test target=arch: (static target)
    {{CC}} -m{{target}} -ggdb test/test.cpp -o test/test -static -Lbuild -lcore{{target}}
    test/test

# Build all intermediary files. Use a different build command.
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

# Build static and dynamic libs for 32-bit.
all-32: (static "32") (dynamic "32")

# Build static and dynamic libs for 64-bit.
all-64: (static "64") (dynamic "64")

# Install the dynamic library to /usr/lib. Requires sudo.
install target=arch: (dynamic target)
    sudo cp build/libcore{{target}}.so /usr/lib/

# Remove all build fragments and outputs.
clean:
    rm -rf build temp test/test **/*.o **/*.so **/*.a
