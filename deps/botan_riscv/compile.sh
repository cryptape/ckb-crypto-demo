
./configure.py --cpu=riscv64 --without-os-feature=threads,thread_local,posix1,filesystem,getauxval  --ar-command=/riscv/bin/riscv64-unknown-elf-gcc-ar --cc-bin=/riscv/bin/riscv64-unknown-elf-g++ --minimized-build  --disable-shared-library --link-method=copy --enable-modules=ed25519

sed -i "s/-pthread//g" Makefile

make
