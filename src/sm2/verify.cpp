
#include <botan/ecdsa.h>
#include <botan/ec_group.h>
#include <botan/pubkey.h>
#include <botan/hex.h>
#include <botan/sm2.h>
#include <botan/pk_algs.h>
#include <botan/pkcs8.h>
#include <botan/x509_key.h>
#include <botan/point_gfp.h>
#include "ckb_syscalls.h"

int main()
{

    std::string text("This is a tasty burger!");
   std::vector<uint8_t> data(text.data(),text.data()+text.length());


    //Botan::EC_Group ecgrp("sm2p256v1");
    Botan::EC_Group ecgrp(Botan::OID({1,2,156,10197,1,301}));

    std::string pubkey_s = "039DBCCE0D6A94BC702037D9C593391ED2B2168E5482DE7593CAE3E3BE86317189";
    std::string signature_s = "29F00228BFBF38178AEDFD67075D0CAAC977EA2C310817D8A4F52E9C4ACF57AE02B3230BB120364A92ED1ACE065FCB0729532DE5DDA77A09CA48167A5EADE171";


    Botan::PointGFp pub_p = ecgrp.OS2ECP(Botan::hex_decode(pubkey_s));

    Botan::SM2_PublicKey pub_k(ecgrp,pub_p);

    Botan::PK_Verifier pkVerifier(pub_k,"EMSA1(SM3)");
    pkVerifier.update(data);

    int result = pkVerifier.check_signature(Botan::hex_decode(signature_s));
//std::cout << "is " << (re? "valid\n" : "invalid\n") << std::endl;

    if(result){
        ckb_exit (0);
    } else
        ckb_exit (1);

}
