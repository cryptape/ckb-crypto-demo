
#include <botan/ecdsa.h>
#include <botan/ec_group.h>
#include <botan/pubkey.h>
#include <botan/hex.h>
#include <botan/point_gfp.h>
#include "../include/ckb_syscalls.h"

int main()
{

   Botan::EC_Group ecgrp("secp256r1");

   std::string text("This is a tasty burger!");
   std::vector<uint8_t> data(text.data(),text.data()+text.length());

   std::string pubkey_s = "04AF62CE672F2F1DDF542D31C13A307CB88C4DE2C515DE3FFDB6CBBFA27EB1131D5B1B378A08B75B172744FF27CACEEC5199B73D5FAB4F6D19716744293091136F";
   std::string signature_s = "BC097C37E693D46CFC4AE1BD38C8854B84513CFFAD0A17E63F4741BEEFC98B5FE811932293241C4B829A7C18AB08A03DC770B9A9FE501DA6DC93E413710E4FCA";

   Botan::PointGFp pub_p = ecgrp.OS2ECP(Botan::hex_decode(pubkey_s));
   Botan::ECDSA_PublicKey pub_k(ecgrp,pub_p);

   // verify signature
   Botan::PK_Verifier verifier(pub_k, "EMSA1(SHA-256)");
   verifier.update(data);

   int result = verifier.check_signature(Botan::hex_decode(signature_s));
   if (result)
   {
      ckb_exit (0);
   }
   ckb_exit (1);
}
