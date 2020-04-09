
//#define CKB_VM



#define BLS_ETH //使用ETH的规范

# ifdef CKB_VM
#include "ckb_syscalls.h"
#include "common.h"
#include "protocol.h"

#else
#include <stdio.h>
#endif

#include <mcl/bn_c384_256.h>
#include <bls/bls.h>


#include <string.h>
#include <stdio.h>


#define BLAKE2B_BLOCK_SIZE 32
#define BLAKE160_SIZE 20
#define PUBKEY_SIZE 33
#define TEMP_SIZE 32768
#define RECID_INDEX 64
/* 32 KB */
#define MAX_WITNESS_SIZE 32768
#define SCRIPT_SIZE 32768
#define SIGNATURE_SIZE 65

#if (MAX_WITNESS_SIZE > TEMP_SIZE) || (SCRIPT_SIZE > TEMP_SIZE)
#error "Temp buffer is not big enough!"
#endif

void print(char *s){
#ifdef CKB_VM
    ckb_debug(s);
#else
    //ckb_debug(s);
     printf(s);
#endif
}

int main()
{
    #ifdef CKB_VM
    print("test in ckb\n");
    #endif


	blsPublicKey pub;
	blsSignature sig;

    char *msg = "abc";

	char *pubchar = "88820327e47cba8c3b4b2f32e8e8d06752a26f1ecec1afa2ac3b197e96e03dd315c9c3298dbf755355ed9ea9553ffc1a";
	char *sigchar = "a0daa6c644b92fb4cb5615befd63d283d8dcb47df89c4710e24b6d2c24247d837f9719ef1fd03fb61cf6cccec93c5a50050aa035712e835581e2b00b0bd877b0635ecaae9751e99190bca9b0a7438394070561366e26b84d52a9d7cb8845eee0";
    int ret;
    char buf[2000];
    size_t msgsize;

    ret = blsInit(MCL_BLS12_381, MCLBN_COMPILED_TIME_VAR);
    if (ret) {
        print("err init\n");

        #ifdef CKB_VM
        ckb_exit(ERROR_BLS_INIT_FAILED);
        #else
        return 1;
        #endif
    }
    blsSetETHmode(BLS_ETH_MODE_LATEST);

#ifdef CKB_VM
    uint64_t len = 0;
    uint8_t temp[TEMP_SIZE];
    unsigned char lock_bytes[SIGNATURE_SIZE];

      /* Load args */
      unsigned char script[SCRIPT_SIZE];
      len = SCRIPT_SIZE;
      ret = ckb_load_script(script, &len, 0);
      if (ret != CKB_SUCCESS) {
        return ERROR_SYSCALL;
      }
      if (len > SCRIPT_SIZE) {
        return ERROR_SCRIPT_TOO_LONG;
      }
      mol_seg_t script_seg;
      script_seg.ptr = (uint8_t *)script;
      script_seg.size = len;

      if (MolReader_Script_verify(&script_seg, false) != MOL_OK) {
        return ERROR_ENCODING;
      }

      mol_seg_t args_seg = MolReader_Script_get_args(&script_seg);
      mol_seg_t args_bytes_seg = MolReader_Bytes_raw_bytes(&args_seg);
      if (args_bytes_seg.size != BLAKE160_SIZE) {
        //ckb_exit(ERROR_ARGUMENTS_LEN);
      }



    /* Load witness of first input */
    uint64_t witness_len = MAX_WITNESS_SIZE;
    ret = ckb_load_witness(temp, &witness_len, 0, 0, CKB_SOURCE_GROUP_INPUT);
    if (ret != CKB_SUCCESS) {
        return ERROR_SYSCALL;
    }

    if (witness_len > MAX_WITNESS_SIZE) {
        return ERROR_WITNESS_SIZE;
    }


    /* load signature */
    mol_seg_t lock_bytes_seg;
    ret = extract_witness_lock(temp, witness_len, &lock_bytes_seg);
    if (ret != 0) {
        return ERROR_ENCODING;
    }

    if (lock_bytes_seg.size != SIGNATURE_SIZE) {
        //return ERROR_ARGUMENTS_LEN;
    }
    memcpy(lock_bytes, lock_bytes_seg.ptr, lock_bytes_seg.size);





    blsPublicKeyDeserialize(&pub,args_bytes_seg.ptr,args_bytes_seg.size);
    blsPublicKeyGetCompressedStr(buf,2000,&pub);

    print("pubkey: ");
    print(buf);
    print("\n");


    ret = blsSignatureDeserialize(&sig,lock_bytes,strlen(lock_bytes));
    if(ret == -1){
        print("Set  Signature failed\n");
        return -1;
    }

    blsSignatureGetCompressedStr(buf,2000,&sig);

    print("sig: ");
    print(buf);
    print("\n");



    ret = blsVerify(&sig,&pub,msg,strlen(msg));
    if(ret==1){
        print("verify success\n");
        ckb_exit(0);
        return -1;


    }
    else{
        print("verify failed\n");
        ckb_exit(-1);
    }
    ckb_exit(0);
    return 0;
#endif

    ret = blsSignatureSetCompressedStr(&sig,sigchar,strlen(sigchar));
    if(ret == -1){
        print("Set str to Signature failed\n");
        return -1;
    }
	ret = blsPublicKeySetCompressedStr(&pub,pubchar,strlen(pubchar));
    if(ret == -1){
        print("Set str to PublicKey failed\n");
        return -1;
    }


    blsPublicKeyGetCompressedStr(buf,2000,&pub);

    print("pubkey: ");
    print(buf);
    print("\n");


    blsSignatureGetCompressedStr(buf,2000,&sig);
    print("sig: ");
    print(buf);
    print("\n");


    msgsize =strlen(msg);
    int r = blsVerify(&sig,&pub,msg,3);
	if (r == 1){
        print("verify success\n");
        

        //ckb_exit(0);

        return 1;
        
    }
    else{
        print("verify failed\n");
        //ckb_exit(-1);
    }

}


