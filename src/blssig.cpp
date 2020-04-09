#include <bls/bls384_256.h>
#include <string.h>
#include <stdio.h>

int main()
{
    blsSecretKey sec;
    blsPublicKey pub;
    blsSignature sig;
    char buf[2000];
    const char *msg = "abc";
    const size_t msgSize = strlen(msg);
    int ret = blsInit(MCL_BLS12_381, MCLBN_COMPILED_TIME_VAR);
    if (ret) {
        printf("err %d\n", ret);
        return 1;
    }
    blsSetETHmode(BLS_ETH_MODE_LATEST);
    char * secC = "212122345676543212345678";

    blsSecretKeySetHexStr(&sec,secC,strlen(secC));
    ret = mclBnFr_isValid(&sec.v);
    printf("%d\n",ret);
    blsSecretKeyGetCompressedStr(buf,2000,&sec);
    printf("sec : %s\n",buf);
    blsGetPublicKey(&pub, &sec);
    blsSign(&sig, &sec, msg, msgSize);

    blsPublicKeyGetCompressedStr(buf,2000,&pub);
    printf("pubkey: %s\n",buf);

    blsSignatureGetCompressedStr(buf,2000,&sig);
    printf("sig: %s\n",buf);
    printf("verify %d\n", blsVerify(&sig, &pub, msg, msgSize));
}
