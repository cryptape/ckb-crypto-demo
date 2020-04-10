#docker pull nervos/ckb-riscv-gnu-toolchain:xenial-full-20191209
docker run --rm -v `pwd`:/code nervos/ckb-riscv-gnu-toolchain:xenial-full-20191209  bash -c "cd /code/build && cmake -DCMAKE_TOOLCHAIN_FILE=../CMakeRiscvToolchain.txt  -DCMAKE_BUILD_TYPE=debug ../ && make"
