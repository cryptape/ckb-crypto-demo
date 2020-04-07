/*
    finish SM3 hash in gcc
*/

#include <botan/hash.h>
#include <botan/hex.h>
#include <iostream>
#include <string>


int main (int argc, char* argv[])
{
    //static std::unique_ptr<HashFunction> create(const std::string &name)
    //Return a newly allocated hash function object, or nullptr if the name is not recognized.
    
    std::unique_ptr<Botan::HashFunction> hash1(Botan::HashFunction::create("SM3"));

    std::string s;
    s = argv[1];

    //void update(const std::string &input)
    //Updates the computation with input.

    hash1->update(s);

    //void final(uint8_t *out)
    // Finalize the calculation and place the result into out. 
    // For the argument taking an array, exactly output_length bytes will be written. 
    // After you call final, the algorithm is reset to its initial state, 
    // so it may be reused immediately.

    std::cout << "SM3 " << Botan::hex_encode(hash1->final()) << std::endl;

    return 0;
}
