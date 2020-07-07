# Verify on chain

We provide `ed25519, sm2(sm3), r1, rsa2048` verification algorithms. The `/botan_riscv` directory is the riscv compileable code of the botan password library. We have modified it to make the static library under the riscv tool chain. It is not recommended to use the `./configure.py` script to re-extract the source code to generate a `Makefile`, and make it directly in the directory to generate a static library.
