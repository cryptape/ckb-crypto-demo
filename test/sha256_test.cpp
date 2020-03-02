//
// Created by tim on 2020/2/28.
//


#include <cstdint>
#include <cstdio>
#include <cstring>
# include "sha256.h"
# include "sha256_test.h"



void hexdigest(uint8_t* from,char * to){
    for (int i=0;i<32;i++){
        sprintf(&to[2*i],"%02x",(char*)from[i]);
    }
}

int main(){



    uint8_t out[32];
    char format[64];

    for (int i=0;i<505;i++){

        sha256(testlist[i].in,out);
        hexdigest(out,format);
        if (strcmp(format,testlist[i].out) == 0){
            printf("Case %d passed \n",i);
        }
        else {
            printf("Case %d failed \n",i);
            //return -1;
        }
    }
    printf("Test complete \n");


}
