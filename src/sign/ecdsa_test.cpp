//
// Created by Maellys on 2020/3/21.
//
#include <cstdio>
#include <cstring>
#include <iostream>
#include "sha256.h"
#include "ecc.h"

int main(int argc, char* argv[]) {
    char plain_text[50];
    strcpy(plain_text,"This is a message from alice to bob.");
    //generate hash for plain text
    uint8_t digest[60];
    char digest_char[60];
    sha256(plain_text,digest);
    hexdigest(digest,digest_char);
    std::cout<<"digest:"<<std::endl<<digest_char<<std::endl;

    //generate ecc key-pair
    //ecc curve is set to secp256r1
    uint8_t publicKey[ECC_BYTES+1];
    uint8_t privateKey[ECC_BYTES];
    ecc_make_key(publicKey,privateKey);

    //sign and verify
    uint8_t signature[ECC_BYTES*2];
    char signature_char[ECC_BYTES*2];
    ecdsa_sign(privateKey,digest,signature);
    hexdigest(signature,signature_char);
    std::cout<<"signature:"<<std::endl<<signature_char<<std::endl;
    if(ecdsa_verify(publicKey,digest,signature)==1){
        printf("Signature valid!\n\n\n");
    }else{
        printf("Signature not valid!\n\n\n");
    }
}
