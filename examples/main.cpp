
#define CKB_VM


#include <cstdio>
#include <cstdint>
# include <cstring>

#include "sha256.h"

# ifdef CKB_VM
#include "ckb_syscalls.h"
#include "protocol.h"

#endif

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


int main(){
    uint64_t inputlen = 31312;
    char intputarg[inputlen] ;
    int ret;
    uint64_t len = 0;
    unsigned char temp[TEMP_SIZE];
    unsigned char lock_bytes[SIGNATURE_SIZE];
    uint8_t  out[32];
    char format[64];

    /* Load args */
    unsigned char script[SCRIPT_SIZE];
    len = SCRIPT_SIZE;
    ret = ckb_load_script(script, &len, 0);
    if (ret != CKB_SUCCESS) {
        return ret;
    }
    if (len > SCRIPT_SIZE) {
        return ret;
    }
    mol_seg_t script_seg;
    script_seg.ptr = (uint8_t *)script;
    script_seg.size = len;

    if (MolReader_Script_verify(&script_seg, false) != MOL_OK) {
        return ret;
    }

    mol_seg_t args_seg = MolReader_Script_get_args(&script_seg);
    mol_seg_t args_bytes_seg = MolReader_Bytes_raw_bytes(&args_seg);


    /* load witness */
    ckb_load_witness(intputarg, &inputlen,  0,
                             0,  1);
    
    if (ret != 0){
        ckb_debug("ckb_load_input_by_field return not 0\n");
        return(ret);
    }

    sha256(intputarg,out);

    uint8_t tmp[88];
    memcpy(tmp,args_seg.ptr,36);



    for (int i=0;i<32;i++){
        if(out[i] != tmp[i+4]){
            return -1;
        }
    }


    return(0);
        
}
