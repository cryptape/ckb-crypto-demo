#include <stdio.h>
#include <string.h>
#include <mcl/bn_c384_256.h>

int g_err = 0;
#define ASSERT(x) { if (!(x)) { printf("err %s:%d\n", __FILE__, __LINE__); g_err++; } }

int main()
{
	char buf[1600];
	const char *aStr = "123";
	const char *bStr = "456";
	int ret = mclBn_init(MCL_BLS12_381, MCLBN_COMPILED_TIME_VAR);
	if (ret != 0) {
		printf("err ret=%d\n", ret);
		return 1;
	}
	mclBnFr a, b, ab;
	mclBnG1 P, aP;
	mclBnG2 Q, bQ;
	mclBnGT e, e1, e2;

#define D2
#ifdef D1
//mclBn_setETHserialization(1);
	mclBnFr_setStr(&a, aStr, strlen(aStr), 10);
	mclBnFr_setStr(&b, bStr, strlen(bStr), 10);
	mclBnFr_mul(&ab, &a, &b);
	mclBnFr_getStr(buf, sizeof(buf), &ab, 10);
	printf("%s x %s = %s\n", aStr, bStr, buf);

	ASSERT(!mclBnG1_hashAndMapTo(&P, "this", 4));
	ASSERT(!mclBnG2_hashAndMapTo(&Q, "that", 4));
	ASSERT(mclBnG1_getStr(buf, sizeof(buf), &P, 2048));
	printf("P = %s\n", buf);
	ASSERT(mclBnG2_getStr(buf, sizeof(buf), &Q, 2048));
	printf("Q = %s\n", buf);

	mclBnG1_mul(&aP, &P, &a);
	mclBnG2_mul(&bQ, &Q, &b);

	mclBn_pairing(&e, &P, &Q);
	ASSERT(mclBnGT_getStr(buf, sizeof(buf), &e, 2048));
	printf("e = %s\n", buf);
	mclBnGT_pow(&e1, &e, &a);
	mclBn_pairing(&e2, &aP, &Q);
	ASSERT(mclBnGT_isEqual(&e1, &e2));

	mclBnGT_pow(&e1, &e, &b);
	mclBn_pairing(&e2, &P, &bQ);
	ASSERT(mclBnGT_isEqual(&e1, &e2));

#endif

#ifdef D2
    const char *cP="a491d1b0ecd9bb917989f0e74f0dea0422eac4a873e5e2644f368dffb9a6e20fd6e10c1b77654d067c0618f6e5a7f79a";
    char *cQ="b2a0bd8e837fc2a1b28ee5bcf2cddea05f0f341b375e51de9d9ee6d977c2813a5c5583c19d4e7db8d245eebd4e502163076330c988c91493a61b97504d1af85fdc167277a1664d2a43af239f76f176b215e0ee81dc42f1c011dc02d8b0a31e32";
    char *cR="";
    mclBn_setETHserialization(1);


    mclBnG2_setStr(&Q,cQ, strlen(cQ),2048);

    mclBnG2_getStr(buf, sizeof(buf),&Q,16);
    printf("%s \n",buf);
    mclBnG2_getStr(buf, sizeof(buf),&Q,2048);
    printf("%s \n",buf);

    mclBnG2_getStr(buf, sizeof(buf),&Q,2048);
    printf("%s \n",buf);


    mclBnG1_setStr(&P,cP, strlen(cP),2048);

    mclBnG1_getStr(buf, sizeof(buf),&P,16);
    printf("%s \n",buf);
    mclBnG1_getStr(buf, sizeof(buf),&P,2048);
    printf("%s \n",buf);

    mclBnG1_getStr(buf, sizeof(buf),&P,2048);
    printf("%s \n",buf);

#endif
	if (g_err) {
		printf("err %d\n", g_err);
		return 1;
	} else {
		printf("no err\n");
		return 0;
	}
}
