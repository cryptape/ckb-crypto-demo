//
// Created by jialiang fan on 2020/4/8.
//

#include <bls/bls384_256.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char* argv[])
{

    blsSecretKey sec;
    blsPublicKey pub;
    char buf[2000];
    if (argc < 2) {
        printf("Please enter pravite key\n");
        return 0;
    }

    char *secC = argv[1];
    if (strlen(secC) != 64){
        printf("Please check pravite key length, should be 64, input is %d\n",strlen(secC));
        return 0;
    }



    int ret = blsInit(MCL_BLS12_381, MCLBN_COMPILED_TIME_VAR);
    if (ret) {
        printf("err %d\n", ret);
        return 1;
    }
    blsSetETHmode( BLS_ETH_MODE_LATEST);

    blsSecretKeySetHexStr(&sec,secC,64);
    ret = mclBnFr_isValid(&sec.v); //sec.v 是Fr

    if(ret != 1){
        printf("Invalid  pravite key\n");
        return 0;
    }

    blsGetPublicKey(&pub, &sec);
    blsPublicKeyGetCompressedStr(buf,2000,&pub);
    printf("Pubkey: %s\n",buf);
    return 0;
}
