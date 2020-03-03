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

## example

Assume `X=sha256(x)`  

- Code function  
    Take __X__ as argument of lock script .If someone can give x in unlock script, he can pass the script validate i.e. he can unlock the script.

- Parameters  
    Code takes script `args` as X, `Winesses` as x.

- On chain location
    Binary code located in tx `0x748d98f5f8f811efd8d2a32514e5a819838b07fac82b15981879ab8d561fb0c4`.  

- Transcation Example
    In tx `0x80cb1f45c0b731cc6394873540230485febf647d97b840b3998dcc4d74a71265`, 
    X = Input.args, x = Witnesses[0] = "test" ,
    sha256("test") = `0x9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08`
