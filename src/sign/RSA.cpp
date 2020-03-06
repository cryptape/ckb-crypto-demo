//
// Created by Maellys on 2020/3/5.
//

#include <ctime>
#include <cstdio>
#include <cstring>
#include <iostream>
#include "bignum.h"
#include "sha256.h"


#define MAXPRIMECOUNT 1000 // max value for count
unsigned int nSmallPrimes[MAXPRIMECOUNT][2]; // 小素数数组
unsigned int nPrimeCount = 0; // 寻找素数的次数
CBigNumString strMod, strPubKey, strPriKey; // 初始化大数字符变量
// 寻找小素数
void MakeSmallPrimes()
{
    unsigned int n;
    unsigned int j;
    nPrimeCount = 3;


    // 首先定义几个小素数
    nSmallPrimes[0][0] = 2;
    nSmallPrimes[1][0] = 3;
    nSmallPrimes[2][0] = 5;
    nSmallPrimes[0][1] = 4;
    nSmallPrimes[1][1] = 9;
    nSmallPrimes[2][1] = 25;
    // 开始寻找素数
    for (n=7; nPrimeCount < MAXPRIMECOUNT; n+=2)
    {
        for (j=0; nSmallPrimes[j][1] < n; j++)
        {
            if (j>= nPrimeCount) // 如果大于当前素数组标号，则返回
            {
                return;
            }
            if (n % nSmallPrimes[j][0]==0)  // 如果不是素数，则退出循环
            {
                break;
            }
        }
        // 找到素数，设置素数
        if (nSmallPrimes[j][1] > n)
        {
            nSmallPrimes[nPrimeCount][0] = n;
            nSmallPrimes[nPrimeCount++][1] = n*n;
        }
    }
}

// 生成随机大数
CBigNum GenerateBigRandomNumber(unsigned short nBytes)
{
    CBigNum Result=0U; // 初始化大数
    int i;
    clock_t ctStart;
    unsigned long ctr=0;

    // 设置时间间隔
    clock_t ctInterval = CLOCKS_PER_SEC / 50 + 1;

    for (i=0; i<nBytes*2; i++)
    {
        ctStart = clock();
        // 等到大于时间间隔再开始
        while (clock() - ctStart < ctInterval)
            ctr++;

        ctr = (ctr % 33) & 0xF;

        Result <<= 4U; // 大数左移4位
        Result |= ctr; // 做或运算
    }
    putchar('\n');
    return Result; // 返回大数
}

CBigNum FindABigPrime(unsigned short nBytes)
{
    CBigNum nBig, nBig2;
    DWORD j;
    DWORD nTestCount = 0;
    DWORD nLehmanCount = 0;
    clock_t ctStartTime = clock(); // 记录开始时间
    DWORD nOffset=0;
    bool bPrime=false; // 素数标志位

    // 开始寻找对应位数的大素数
    for (nBig = GenerateBigRandomNumber(nBytes) | 1U; !bPrime; nBig+=2U, nOffset+=2)
    {
        nTestCount++;
        for (j=0; j<nPrimeCount; j++)
        {
            // 如果不是大素数，则退出循环
            if (nBig % nSmallPrimes[j][0] == 0)
            {
                break;
            }
        }

        if (j<nPrimeCount)
            continue;
        nLehmanCount++;
        nBig2 = (nBig - 1U) / 2U;
        // 设置一些随机的素数
        DWORD arnLehmanPrimes[] = { 89, 5179, 25981, 25439, 25013, 25667, 27397 };
        // 初始化大数组
        CBigNum LehmanResults[sizeof(arnLehmanPrimes) / sizeof(arnLehmanPrimes[0])];
        nBig2 = nBig - 1U;
        bPrime = true;
        for (j=0; j<sizeof(arnLehmanPrimes) / sizeof(arnLehmanPrimes[0]); j++)
        {
            // 开始生成大素数
            LehmanResults[j] =
                    CBigNum(arnLehmanPrimes[j]).PowMod(nBig2, nBig, CLOCKS_PER_SEC);
            if (LehmanResults[j] == nBig2)
            {
            }
            else if (LehmanResults[j] == 1U)
            {
            }
            else // 不是大素数
            {
                bPrime = false;
                break;
            }
        }
        // 找到大素数
        if (bPrime)
        {
            break;
        }
    }
    return nBig; // 返回大素数
}

// 生成公钥和私钥 n,e,d
void GenKeyPair(CBigNum &PublicMod, CBigNum &PublicKey, CBigNum &PrivateKey, CBigNum &P, CBigNum &Q, unsigned int nByteCount)
{
    if (0U==(P | Q))
    {
        P=FindABigPrime(nByteCount); // 生成nByteCount位的大素数
        Q=FindABigPrime(nByteCount); // 生成nByteCount位的大素数
        PublicKey=GenerateBigRandomNumber(nByteCount) | 1U;
    } else {
        PublicKey |= 1U;
    }
    PrivateKey = (P-1U) * (Q-1U); // 初始化私钥 phi(n)
    while (PublicKey > PrivateKey)
        PublicKey=GenerateBigRandomNumber(nByteCount-1) | 1U;
    while(CBigNum::gcd(PublicKey,PrivateKey) != 1U)
        PublicKey+=2; // 累加直至互素得到公钥 e
    PrivateKey = PublicKey.Inverse(PrivateKey); // 求得e关于r的模反元素，生成私钥 d

    PublicMod = P*Q; // 公钥n的生成
}


// 生成特定格式的公钥和私钥 n,b,a
void GenerateKeys(CBigNumString &PublicMod, CBigNumString &PublicKey, CBigNumString &PrivateKey, unsigned short nBytes)
{
    CBigNum PubMod, PubKey, PriKey, PriP, PriQ;
    MakeSmallPrimes();
    GenKeyPair(PubMod, PubKey, PriKey, PriP, PriQ, nBytes); // 生成公钥和私钥
    // 将公钥和私钥转换成16进制形式
    PublicMod = PubMod.ToHexString();
    PublicKey = PubKey.ToHexString();
    PrivateKey = PriKey.ToHexString();
}


// RSA加密函数 E(x)=x^b mod n
void RSAEncrypt(char *publickey,char *publicmod, char *output, unsigned int *outputlen, char *input, unsigned int inputlen)
{
    CBigNum Transform;
    CBigNum PubMod, PubKey;
    CBigNumString strTransform;
    // 将公钥转换成大数
    PubMod = CBigNum::FromHexString(publicmod);
    PubKey = CBigNum::FromHexString(publickey);

    // 转换输入的明文
    Transform = Transform.FromByteString(input);
    // 使用RSA加密明文
    Transform = Transform.PowMod(PubKey,PubMod);
    // 将密文转换成16进制的字符
    strTransform = Transform.ToHexString();

    // 输出密文长度
    *outputlen = strlen((const char*)strTransform)+1;
    // 输出密文
    memcpy(output,(const char*)strTransform,(*outputlen)+1);
}

// RSA解密 D(y)=y^a mod n
void RSADecrypt(char *output, unsigned int *outputlen, char *input, unsigned int inputlen)
{
    CBigNum Transform;
    CBigNum PubMod,PriKey;
    CBigNumString strTransform;
    // 将私钥转换成大数
    PubMod = CBigNum::FromHexString((const char*)strMod);
    PriKey = CBigNum::FromHexString((const char*)strPriKey);
    // 转换输入的密文
    Transform = Transform.FromHexString(input);
    // 使用RSA对密文进行解密
    Transform = Transform.PowMod(PriKey,PubMod);
    // 将解密文转换成字节字符串
    strTransform = Transform.ToByteString();

    // 输出解密文长度
    *outputlen = strlen((const char*)strTransform)+1;
    // 输出解密文
    memcpy(output,(const char*)strTransform,(*outputlen)+1);


}
/*// RSA 签名 s=E(H(m))
void RSASign(char *publickey,char *publicmod, char *sig, unsigned int *siglen, char *input)
{
    uint8_t digest[300];
    char digest_str[300];
    // 计算摘要
    sha256(input,digest);
    hexdigest(digest,digest_str);
    printf("Digest:\n");
    printf("%s\n\n\n",digest_str);
    // 使用 RSA 加密消息摘要，得到签名
    RSAEncrypt(publickey,publicmod,sig,siglen,digest_str, sizeof(digest_str));
    printf("Signature:\n");
    printf("%s\n\n\n",sig);
}
// RSA 验签
void RSAVerify(char * decrypt,char * sig, unsigned int siglen)
{
    uint8_t new_digest[300];
    char new_digest_str[300];
    char dec_sig[300];
    unsigned int dec_sig_len;
    // 对解密文计算摘要
    sha256(decrypt,new_digest);
    hexdigest(new_digest,new_digest_str);
    printf("Recalculated digest:\n");
    printf("%s\n\n\n",new_digest_str);
    // 解密签名恢复原摘要
    RSADecrypt(dec_sig,&dec_sig_len,sig,siglen);
    printf("Recovered digest:\n");
    printf("%s\n\n\n",dec_sig);
    if(strcmp(dec_sig,new_digest_str)==0){
        printf("Signature verified!\n\n\n");
    }else{
        printf("Signature not verified!\n\n\n");
    }
}
 */
int main(int argc, char* argv[])
{
    char pubkey[300]; // 公钥
    char pubmod[300]; // 公钥
    char encrypt_text[300]; // 输出的密文
    char decrypt_text[300]; // 输出的解密文
    //char signature[300];// 签名

    unsigned int encrypt_len;
    unsigned int decrypt_len;
    //unsigned int signature_len;
    char plain_text[50];
    strcpy(plain_text,"A message less than 32 chars~");
    // 产生公钥和私钥
    GenerateKeys(strMod,strPubKey,strPriKey,16);
    // 设置公钥字符串
    memcpy(pubkey,(const char*)strPubKey,strlen((const char*)strPubKey)+1);
    memcpy(pubmod,(const char*)strMod,strlen((const char*)strMod)+1);

    RSAEncrypt(pubkey,pubmod,encrypt_text,&encrypt_len,plain_text,sizeof(plain_text));
    RSADecrypt(decrypt_text,&decrypt_len,encrypt_text,encrypt_len);


    printf("public key n :  %s\n",pubmod);
    printf("public key e :  %s\n",pubkey);
    printf("Plain text:\n");
    printf("%s\n\n\n",plain_text);
    printf("cipher:\n");
    printf("%s\n\n\n",encrypt_text);

    //RSASign(pubkey,pubmod,signature,&signature_len,plain_text);

    //RSAVerify(decrypt_text,signature,signature_len);
    printf("output for decryption:\n");
    printf("%s\n\n\n",decrypt_text);
    return 0;
}



