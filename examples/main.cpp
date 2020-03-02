
#define CKB_VM


#include <cstdio>
#include <cstdint>
# include <cstring>

#include "sha256.h"


# ifdef CKB_VM
#include "ckb_syscalls.h"

#endif




int main(int argc, char* argv[]) {
    if (argc < 2) {
        ckb_debug("argv not enough");
        return 76;
    }

    char* msg = argv[1];
    uint8_t  out[32];



    sha256(msg,out);

    char format[64];

    for (int i=0;i<32;i++){
        sprintf(&format[2*i],"%02x",(char*)out[i]);
    }

    // 本地跑、ckb跑

    # ifndef CKB_VM

    //printf("%s",format);

    # else
    ckb_debug("HEllo \n");

    ckb_debug(format);

    #   endif



    if (strcmp(format,"9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08") == 0){
        return 0;

    }

    return 1;

}