
#include <botan/hex.h>
#include <botan/auto_rng.h>
#include <botan/pubkey.h>
#include <botan/ecdsa.h>
#include <botan/ec_group.h>
#include <botan/ed25519.h>
#include <botan/sm2.h>
#include <botan/point_gfp.h>
#include <botan/rsa.h>
#include <unistd.h>
#include <iostream>

using namespace std;
int ed25519(string sig_text)
{
    // Generate Ed255119 private key
    Botan::AutoSeeded_RNG rng;
    std::vector<uint8_t> m_public;
    Botan::secure_vector<uint8_t> m_private;

    const Botan::secure_vector<uint8_t> seed = rng.random_vec(32);
    m_public.resize(32);
    m_private.resize(64);
    Botan::ed25519_gen_keypair(m_public.data(), m_private.data(), seed.data());

    std::cout <<  "ed25519 sign: " << sig_text << std::endl;
    // sign msg
    std::string text = sig_text;
    std::vector<uint8_t> m_msg(text.data(),text.data()+text.length());

    //Botan::secure_vector<uint8_t> sig(64);
    std::vector<uint8_t> sig(64);
    // Sign the message
    Botan::ed25519_sign(sig.data(),m_msg.data(),m_msg.size(),m_private.data(), nullptr,0);

    std::cout << "sig is :" << std::endl << Botan::hex_encode(sig) << std::endl;

    std::cout << "pri is :" << std::endl << Botan::hex_encode(m_private) << std::endl;

    std::cout << "pub is :" << std::endl << Botan::hex_encode(m_public) << std::endl;

    bool judge = Botan::ed25519_verify(m_msg.data(),m_msg.size(),sig.data(),m_public.data(),nullptr,0);
    //std::cout << judge << std::endl;
    if (judge)
    {
        std::cout << "verify sig valid" << std::endl;
        return 0;
    }
    return -1;
}

int ed25519_verify()
{
    std::vector<uint8_t> m_public;

    m_public.resize(32);

    // sign msg
    std::string text("This is a tasty burger!");
    std::vector<uint8_t> m_msg(text.data(),text.data()+text.length());

    std::vector<uint8_t> sig(64);
    // Sign the message

    std::string pubkey_s = "847A68C01E5278464D8D1A8F6DDE30B149AEBE5BEB459EA15C331311BC45EBCC";
    std::string sig_s = "37783892FA0794E84C8CC9C606A26F14E98F600D38E8504E7D036011B16FD22BCEAB3313E391355ECE86FFBB0C9123AAED2F9BAFC94EDB3F79D825F0C80F6802";

    sig = Botan::hex_decode(sig_s);
    m_public = Botan::hex_decode(pubkey_s);

    bool judge = Botan::ed25519_verify(m_msg.data(),m_msg.size(),sig.data(),m_public.data(),nullptr,0);
    //std::cout << judge << std::endl;
    if (judge)
    {
        printf("\n");
        std::cout << "1" << std::endl;
        return 0;
    }
    return -1;
}

int sm2(string sig_text)
{
    Botan::AutoSeeded_RNG rng;
    // Generate ECDSA keypair
    //Botan::ECDSA_PrivateKey key(rng, Botan::EC_Group("sm2p256v1"));
    Botan::SM2_PrivateKey key(rng,Botan::EC_Group("sm2p256v1"));

    std::cout <<  "sm2 sign: " << sig_text << std::endl;
    std::string text = sig_text;
    std::vector<uint8_t> data(text.data(),text.data()+text.length());

    std::cout << "pubkey:" << std::endl << Botan::hex_encode(key.public_key_bits()) << std::endl;
    std::cout << "prikey:" << std::endl << Botan::hex_encode(key.private_key_bits()) << std::endl;

    // sign data
    Botan::PK_Signer signer(key, rng, "EMSA1(SM3)");
    signer.update(data);

    std::vector<uint8_t> signature = signer.signature(rng);
    std::cout << "Signature:" << std::endl << Botan::hex_encode(signature);

    // verify signature

    Botan::PK_Verifier verifier(key, "EMSA1(SM3)");
    verifier.update(data);
    std::cout << std::endl << "verify sig is " << (verifier.check_signature(signature)? "valid" : "invalid");

    return 0;
}

int sm2_verify()
{
    std::string text("This is a tasty burger!");
    std::vector<uint8_t> data(text.data(),text.data()+text.length());

    Botan::EC_Group ecgrp("sm2p256v1");

    std::string pubkey_s = "04B01614EBC1F3660B4E23BFDD959080974D26EBF6A9240FBAD160B2430BBCA0C137597155455F39A78570A39E967A879909150D09DDE44D4326FBA850512D3031";
    std::string signature_s = "1C8B7F50C5B0BA81A9BD105315B876E10EE32FA9AF8429FD8E7F9496325ED9C0841A4F76D88D464D22F74C5512932840329CEA566CCE899DA7E9414B626E5E5D";

    Botan::PointGFp pub_p = ecgrp.OS2ECP(Botan::hex_decode(pubkey_s));

    Botan::SM2_PublicKey pub_k(ecgrp,pub_p);

    Botan::PK_Verifier pkVerifier(pub_k,"EMSA1(SM3)");
    pkVerifier.update(data);

    int re = pkVerifier.check_signature(Botan::hex_decode(signature_s));
    std::cout << "is " << (re? "valid\n" : "invalid\n") << std::endl;

    printf("%d\n", re);

    return re;
}


int r1(string sig_text)
{
    Botan::AutoSeeded_RNG rng;
    // Generate ECDSA keypair
    Botan::ECDSA_PrivateKey key(rng, Botan::EC_Group("secp256r1"));

    std::cout <<  "secp256r1 sign :" << sig_text << std::endl;
    std::string text = sig_text;
    std::vector<uint8_t> data(text.data(),text.data()+text.length());

    std::cout << "pubkey : " << std::endl << Botan::hex_encode(key.public_key_bits()) << std::endl;
    std::cout << "prikey : " << std::endl << Botan::hex_encode(key.private_key_bits()) << std::endl;

    // sign data
    Botan::PK_Signer signer(key, rng, "EMSA1(SHA-256)");
    signer.update(data);
    std::vector<uint8_t> signature = signer.signature(rng);
    std::cout << "Signature:" << std::endl << Botan::hex_encode(signature) << std::endl;

    // verify signature
    Botan::PK_Verifier verifier(key, "EMSA1(SHA-256)");
    verifier.update(data);
    std::cout << "verify is " << (verifier.check_signature(signature)? "valid" : "invalid");
    return 0;
}

int r1_verify()
{
    Botan::EC_Group ecgrp("secp256r1");

    std::string text("This is a tasty burger!");
    std::vector<uint8_t> data(text.data(),text.data()+text.length());

    std::string signature_s = "BC097C37E693D46CFC4AE1BD38C8854B84513CFFAD0A17E63F4741BEEFC98B5FE811932293241C4B829A7C18AB08A03DC770B9A9FE501DA6DC93E413710E4FCA";
    std::string pubkey_s = "04AF62CE672F2F1DDF542D31C13A307CB88C4DE2C515DE3FFDB6CBBFA27EB1131D5B1B378A08B75B172744FF27CACEEC5199B73D5FAB4F6D19716744293091136F";
    Botan::PointGFp pub_p = ecgrp.OS2ECP(Botan::hex_decode(pubkey_s));
    Botan::ECDSA_PublicKey pub_k(ecgrp,pub_p);

    // verify signature
    Botan::PK_Verifier verifier(pub_k, "EMSA1(SHA-256)");
    verifier.update(data);

    //int result = verifier.check_signature(Botan::hex_decode(signature_s));
    std::cout << std::endl << "is " << (verifier.check_signature(Botan::hex_decode(signature_s))? "valid" : "invalid");
    return 0;
}

int rsa(string sig_text)
{
    Botan::AutoSeeded_RNG rng;
    Botan::RSA_PrivateKey key(rng,2048);

    std::cout <<  "rsa sign :" << sig_text << std::endl;
    std::string text = sig_text;
    std::vector<uint8_t> data(text.data(),text.data()+text.length());

    std::cout << "prikey: " << std::endl << Botan::hex_encode(key.private_key_bits()) << std::endl;
    std::cout << "pubkey n: " << std::endl << key.get_n().to_hex_string() << std::endl;
    std::cout << "pubkey e: " << std::endl << key.get_e().to_hex_string() << std::endl;

    // sign data
    Botan::PK_Signer signer(key, rng, "EMSA1(SHA-256)");
    signer.update(data);
    std::vector<uint8_t> signature = signer.signature(rng);

    std::cout << "Signature:" << std::endl << Botan::hex_encode(signature) << std::endl;

    // verify signature
    Botan::PK_Verifier verifier(key, "EMSA1(SHA-256)");
    verifier.update(data);
    std::cout  << "verify is " << (verifier.check_signature(signature)? "valid" : "invalid");
    return 0;
}

int rsa_verify()
{
    std::string text("This is a tasty burger!");
    std::vector<uint8_t> data(text.data(),text.data()+text.length());

    //std::cout << "Signature:" << std::endl << Botan::hex_encode(signature) << std::endl;
    std::string sig_s = "3FAB58CB4804B8E37FD76FDCAA2F2ABFA075427E585211D88A20113827AE2FCFB3CF665CABC5CC9B90F255F74EAB2AFC0938EA2D4B95B2C524CC1625E127E5FDA2586F6A8AB04F825482EF7152F92296DB36D40BA1577C30CD6BAED15427AD3C73E28B6B98A14AF70EC0AB16BFD61D11D2461B2E4ABED639C755A76DF5D11148595451A03FF75C16AC7D15C6F485A834E31699618003F211968FCE5B70655F5B027945E272CAB3A80FA814B5B69366EB0A0814B5D2879745484D1EF9B52F3159567417EAB46EBB5ED842474D62ABAAD6E9D5841A6A9F142D17D04DC532A7B2DB0A214AFA76A039E4C01E81481D6FE3C892BC90E9B07BF38C37751CC724530EF6";

    std::string n_s = "C170C5ED60242323026D27C2A18834615102525AAEE332B698387CD3D539A8B96070BE281A68205459184FDDED2B8C57D4A46592B17163656ABB7FE52C50FB50EA38721746D966396B75DEB05507ADC7187BBB0955E404600D4FAC2173C87D749A93F622CB996C27F82C0C743C8158BD6D57585D03886356898F0062DF72A708AE959D3E5749C7CB79CA8F538B63673E2C0EDADE55DF23660117B28974E8C0B421B0026F8F5499FD1FE6C903ABF13952DF38E6F7256E7C45F889B2806AF72D2126AABFEF2BC534E5CAF3D3488C4942D639D9B9A0B2955A420B33EA23FE605D4014AAE28196338A0363BED759E65F60D1CA17F03D184E380B4FA4ABEB235BC6E5";
    std::string e_s = "010001";

    Botan::BigInt pub_n(Botan::hex_decode(n_s));
    Botan::BigInt pub_e(Botan::hex_decode(e_s));
    Botan::RSA_PublicKey pub_key(pub_n,pub_e);

    // verify signature
    Botan::PK_Verifier verifier(pub_key, "EMSA1(SHA-256)");
    verifier.update(data);
    std::cout << std::endl << "is " << (verifier.check_signature(Botan::hex_decode(sig_s))? "valid" : "invalid");
    return 0;
}

int main(int argc, char *argv[])
{
    //ed25519();
    //ed25519_verify();

    //sm2();
    //sm2_verify();

    //r1();
    //r1_verify();

    //rsa();
    //rsa_verify();

    if (argc <= 3 ){
        std::cout << "Usage: " << argv[0];
        std::cout << " [ed25519 sign_text] [sm2 sign_text] [r1 sign_text] [rsa sign_text] "
                     "[-h help] arglist ... " << std::endl;
        return 0;
    } else
    {
        std::string alg = argv[1];
        std::string text;
        for (int i = 2; i < argc; ++i) {
            if(i==2)
                text = text + argv[i];
            else
                text = text + ' ' + argv[i];
        }
        //std::cout << text << std::endl;
        if (!alg.find("ed25519"))
            ed25519(text);
        if (!alg.find("sm2"))
            sm2(text);
        if (!alg.find("r1"))
            r1(text);
        if (!alg.find("rsa"))
            rsa(text);
    }

    return 0;
}








