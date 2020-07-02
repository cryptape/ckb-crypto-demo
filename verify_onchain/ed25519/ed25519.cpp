
#include <botan/hex.h>
#include <botan/ed25519.h>


int main()
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
    if (judge)
    {
        return 0;
    }
    return 1;
}






