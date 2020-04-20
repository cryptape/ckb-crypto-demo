#include <bls/bls384_256.h>
#include <string.h>
#include <stdio.h>

#define CKB_VM

#include "ckb_syscalls.h"



int main()
{
	blsSecretKey sec;
	blsPublicKey pub;
	blsSignature sig;
	const char *msg = "abc";
	const size_t msgSize = strlen(msg);
	int ret = blsInit(MCL_BLS12_381, MCLBN_COMPILED_TIME_VAR);
	if (ret) {
		printf("err %d\n", ret);
		return 1;
	}
    char * buf="47b8192d77bf871b62e87859d653922725724a5c031afeabc60bcef5ff665138";
    blsSecretKeySetHexStr(&sec,buf,strlen(buf));
	//blsSecretKeySetByCSPRNG(&sec);
	blsGetPublicKey(&pub, &sec);
	blsSign(&sig, &sec, msg, msgSize);
    ret = blsVerify(&sig, &pub, msg, msgSize);
    if(ret==1){
        printf("verify success");
        return(0);
    }
    else{
        printf("veriy failed");
        return(-1);
    }

	
}
