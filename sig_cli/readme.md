# Generate signature locally
 There are two directories for signature generation. The `botan` directory is the source code of the entire password library. We package the signature algorithm into a static library libbotan-2.a, and call the corresponding algorithm in `cli` to generate the signature and return pub/pri key.
## botan_x86
This directory contains all the source code of the botan library, and We made some modifications to the library source code, and the `Makefile` is written by us, and `libbotan-2.a` can be directly generated through the `Makefile`.
Of course, you can also customize to generate the desired plan, through the [./configure.py](https://botan.randombit.net/handbook/building.html) script. However, this is not recommended because the Makefile generated in that way will be much more complicated, and we have made it as lightweight as possible
```bash
$ cd botan_x86
$ make
```
## cli
The client calls for specific, input the original text and return the signature and key.
```$xslt
Usage: ./cli [ed25519 sign_text] [sm2 sign_text] [r1 sign_text] [rsa sign_text] [-h help] arglist ... 
```
```$xslt
$ cd cli
$ cmake . && make
```
For example, we want to call the sm2 algorithm to sign the text `"wow, you can really dance, and ckb is pretty cool"`
```
gqy@mbp-pro cli % ./cli sm2 wow, you can really dance, and ckb is pretty cool
sm2 sign: wow, you can really dance, and ckb is pretty cool
pubkey:
04790A59C39511EA933489F9C8408A14B52F8A4B3F9D48400E30246BCF1745B37BB7F7E527646F329957B6C394BF11321C8C74CDBB1CD5F07A928F14CA83DDD6E4
prikey:
306B0201010420C9F8C3435067FC11178CA595E81933F4314BD1FCFF4A5AB261B036063ECAE822A14403420004790A59C39511EA933489F9C8408A14B52F8A4B3F9D48400E30246BCF1745B37BB7F7E527646F329957B6C394BF11321C8C74CDBB1CD5F07A928F14CA83DDD6E4
Signature:
775C07E54F1B75452683B8E2CC30E44A24418F61E8B8B3FC2F74CABAB28F3950FAAD5087F227DE445B2CEF64892A52B29A6BD7B293B88B912827B566A2EB1D68
verify sig is valid                                                                                                                                  gqy@mbp-pro cli % 
```