#include <stdio.h>
#include <string.h>
#include <mcl/bn_c384_256.h>

int g_err = 0;
#define ASSERT(x) { if (!(x)) { printf("err %s:%d\n", __FILE__, __LINE__); g_err++; } }


#include <stdio.h>
#include <string.h>
#include <mcl/bn_c384_256.h>

int main()
{
    char buf[1600];

    int ret = mclBn_init(MCL_BLS12_381, MCLBN_COMPILED_TIME_VAR);
    if (ret != 0) {
        printf("err ret=%d\n", ret);
        return 1;
    }


    char * g2c = "1 24aa2b2f08f0a91260805272dc51051c6e47ad4fa403b02b4510b647ae3d1770bac0326a805bbefd48056c8c121bdb8 13e02b6052719f607dacd3a088274f65596bd0d09920b61ab5da61bbdc7f5049334cf11213945d57e5ac7d055d042b7e ce5d527727d6e118cc9cdc6da2e351aadfd9baa8cbdd3a76d429a695160d12c923ac9cc3baca289e193548608b82801 0606c4a02ea734cc32acd2b02bc28b99cb3e287e85a763af267492ab572e99ab3f370d275cec1da1aaa9075ff05f79be";
    mclBnG2 g2;
    mclBnG2_setStr(&g2,g2c,strlen(g2c),16);
    mclBnG2_getStr(buf,1600,&g2, 16|128);
    mclBnGT Gt;
    printf("G2 input : %s \n",g2c);
    printf("G2 output: %s \n",buf);

}
