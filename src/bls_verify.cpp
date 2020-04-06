#include <bls/bls384_256.h>
#include <string.h>
#include <stdio.h>

#include <bls/bls.hpp>






int main()
{
	blsPublicKey pub;
	blsSignature sig;


	u_int8_t msg[32];
    memset(&msg,0xabab,32);



	char *sigchar = "869cbfaf75f017fd0dc801c4972298e7b33fbd8966be2b355d3618145ccdd677038c638bbfefa677bcb9c4f028d3292706ea4c33015db46340bf7cc67c4a9dab4211cb02c407ad847dcac9dd73b3ee7cc4f92e239a83a2bc79eaa5aed093475d";
	char *pubchar = "b53d21a4cfd562c469cc81514d4ce5a6b577d8403d32a394dc265dd190b47fa9f829fdd7963afdf972e5e77854051f6f";



    const size_t msgSize = 32;
	int ret = blsInit(MCL_BLS12_381, MCLBN_COMPILED_TIME_VAR);
	if (ret) {
		printf("err %d\n", ret);
		return 1;
	}
    blsSetETHmode(BLS_ETH_MODE_LATEST);
    //mclBn_setETHserialization(1);
    blsSignatureSetCompressedStr(&sig,sigchar,strlen(sigchar));
	blsPublicKeySetCompressedStr(&pub,pubchar,strlen(pubchar));

	char buf[2000];
    blsPublicKeyGetCompressedStr(buf,2000,&pub);
    printf("%s\n",buf);

    blsSignatureGetCompressedStr(buf,2000,&sig);
    printf("%s\n",buf);

	/*
	char buf[1600];

    mclBn_setETHserialization(1);

    mclBnG1_setStr(&pub.v,pubchar,strlen(pubchar),2048);

    mclBnG1_getStr(buf,strlen(buf),&pub.v,2048);

    printf("pub : %s \n",buf);

	ret = mclBnG2_setStr(&sig.v,sigchar, strlen(sigchar),2048);

    mclBnG2_getStr(buf,strlen(buf),&(sig.v),2048);
    printf("sig : %s \n",buf);
    */
	printf("verify %d\n", blsVerify(&sig,&pub,msg,32));


}
