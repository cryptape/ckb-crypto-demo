basedir=`pwd`

docker run --rm -v `pwd`:/code nervos/ckb-riscv-gnu-toolchain:xenial-full-20191209  bash -c "cd /code && ./target.sh"
cd tx-verify
bundle exec ./tx-mock.rb ../build/sm2
ckb-cli --url http://127.0.0.1:8116 mock-tx  verify --tx-file=tx-mocked.json