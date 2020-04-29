# docker pull nervos/ckb-riscv-gnu-toolchain:xenial-full-20191209
docker run --rm -v /Users/timfan/Work/ckb_crypto/code/crypto:/code nervos/ckb-riscv-gnu-toolchain:xenial-full-20191209  bash -c "cd /code/build && cmake -DCMAKE_TOOLCHAIN_FILE=../CMakeRiscvToolchain.txt  -DCMAKE_BUILD_TYPE=debug ../ && make"
bundle exec ./tx-mock.rb ../build/blsverify


