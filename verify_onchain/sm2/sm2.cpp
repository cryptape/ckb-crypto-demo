

#include <botan/ec_group.h>
#include <botan/pubkey.h>
#include <botan/hex.h>
#include <botan/sm2.h>
#include <botan/point_gfp.h>

extern "C" {
    #include "../include/ckb_syscalls.h"
}


int main()
{

    std::string text("This is a tasty burger!");
    std::vector<uint8_t> data(text.data(),text.data()+text.length());


    Botan::EC_Group ecgrp("sm2p256v1");
    //Botan::EC_Group ecgrp(Botan::OID({1,2,156,10197,1,301}));

    std::string pubkey_s = "041F90B612ED65E84A642F515EB43CAA6327F1A317F2F45724FBCFBBFBBF24B7C8A84CCA828AD1045C93C69D19342FA5E6051CC2B3B3F9D4031D49504BAA549F13";
    std::string signature_s = "8EE3608A3979BA75A0ADEBE59EF2AF3E77AC19101E95017AA4AEE00ACE2B86A96680711148EB024CFC73D73E5EAEAD07F479DBAC8CE5CD23C363E8F8BB0ABEB4";

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
