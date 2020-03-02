# Ctypto-demo

## About 
Demo for CKB crypto lib


# build on local

**comment secondline in example/main.cpp**
like `//#define CKB_VM`

```
cd build  && rm -rf ./
cmake ../
make
make test
```

## build example on riscv

```
./make_via_riscv.sh
```

## usage
`sha256 <string>`   
or  
`sha256_riscv_example  <string>`
