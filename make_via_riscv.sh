
BASE_DIR=`pwd`
BUILD_DIR=$BASE_DIR/build

DEBUG_FLAGS="--with-debug-info --debug-mode --no-optimizations"
RELEASE_FLAGS="--optimize-for-size"

CROSSDOMPILE_FLAGS="--cpu=riscv64 --ar-command=/riscv/bin/riscv64-unknown-elf-gcc-ar --cc-bin=/riscv/bin/riscv64-unknown-elf-g++"

# Build and install botan lib
cd deps/botan_riscv
./configure.py --prefix=$BUILD_DIR   $CROSSDOMPILE_FLAGS --cc-abi-flags='-O3 -Wl,-static -fdata-sections -ffunction-sections -Wl,--gc-sections' --build-targets=static  --without-os-feature=threads,thread_local,posix1,filesystem,getauxval   --minimized-build  --disable-shared-library --link-method=copy --enable-modules=sm2,sm3,ecdsa
make && make install

cd $BUILD_DIR && cmake -DCMAKE_TOOLCHAIN_FILE=$BASE_DIR/CMakeRiscvToolchain.txt  $BASE_DIR && make

# riscv64-unknown-elf-objcopy --strip-all --strip-debug target

