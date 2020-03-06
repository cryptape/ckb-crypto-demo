#ifndef RSA_BIGNUM_H
#define RSA_BIGNUM_H
#endif //RSA_BIGNUM_H

typedef unsigned long DWORD;


class CBigNumString
{
public:
    CBigNumString();
    ~CBigNumString();
    operator const char *() const;
    void Realloc(unsigned int nByteCount);
    CBigNumString(const CBigNumString& rhs);
    char &operator [](unsigned int nIdx);
    const CBigNumString &operator=(const CBigNumString rhs);

private:
    char *m_szBuffer;
    unsigned int m_nSize;
};

class CBigNum
{
public:
    CBigNum();
    CBigNum(unsigned int);
    CBigNum(const CBigNum &copy);
    CBigNum(const char *szSourceVal);
    virtual ~CBigNum();

    CBigNum Pow(unsigned int rhs) const;
    CBigNum PowMod(CBigNum rhs, const CBigNum &mod, const clock_t ctShowSteps = 0) const;
    CBigNum Inverse(const CBigNum &mod) const;
    unsigned int operator&(unsigned int rhs);
    void Resize(unsigned int nNewSize);
    void Reduce();

    CBigNum &operator=(CBigNum rhs);
    CBigNum &operator=(const char *szSourceVal);
    CBigNum &operator=(unsigned int intVal);
    CBigNum &operator<<=(unsigned int rhs);
    CBigNum operator<<(unsigned int rhs) const;
    CBigNum &operator>>=(unsigned int rhs);
    CBigNum operator>>(unsigned int rhs) const;
    CBigNum &operator+=(const CBigNum &rhs);
    CBigNum &operator-=(const CBigNum &rhs);
    CBigNum &operator-=(const unsigned int rhs);
    CBigNum operator-(const unsigned int rhs) const;
    CBigNum operator+(const CBigNum &rhs) const;
    CBigNum operator+(const unsigned int) const;
    CBigNum operator*(unsigned int rhs) const;
    CBigNum operator*(const CBigNum &rhs) const;
    CBigNum &operator*=(unsigned int rhs);
    CBigNum &operator*=(const CBigNum &rhs);
    CBigNum operator/(const CBigNum &rhs) const;
    CBigNum operator/(const unsigned int rhs) const;
    CBigNum &operator/=(const CBigNum &rhs);
    CBigNum &operator/=(const unsigned int rhs);
    CBigNum operator%(const CBigNum &rhs) const;
    unsigned int operator%(const unsigned int rhs) const;
    CBigNum &operator%=(const CBigNum &rhs);
    unsigned int operator%=(const unsigned int rhs);
    CBigNum &operator&=(CBigNum rhs);
    CBigNum &operator|=(const CBigNum &rhs);
    CBigNum operator|(const CBigNum &rhs) const;
    CBigNum &operator|=(const unsigned int rhs);
    CBigNum operator|(const unsigned int rhs) const;
    CBigNum factorial() const;
    CBigNum sqrt() const;
    unsigned int log10() const;
    unsigned int log2() const;

    static CBigNum gcd(const CBigNum &x, const CBigNum &y);
    static CBigNum lcm(const CBigNum &x, const CBigNum &y);
    static CBigNum FromByteString(const char *szIn, const unsigned int nLength = 0);
    static CBigNum FromHexString(const char *szIn);
    static CBigNum FromBase64String(const char *szIn);

    bool operator<(const CBigNum &rhs) const;
    bool operator<=(const CBigNum &rhs) const;
    bool operator==(const CBigNum &rhs) const;
    bool operator!=(const CBigNum &rhs) const;
    bool operator>(const CBigNum &rhs) const;
    bool operator>=(const CBigNum &rhs) const;

    bool operator<(const unsigned int rhs) const;
    bool operator<=(const unsigned int rhs) const;
    bool operator==(const unsigned int rhs) const;
    bool operator!=(const unsigned int rhs) const;
    bool operator>(const unsigned int rhs) const;
    bool operator>=(const unsigned int rhs) const;

    operator bool() const;

    operator CBigNumString() const;
    operator const char *() const;

    CBigNumString ToByteString(bool bMakePrintable = true) const;
    CBigNumString ToHexString() const;
    //CBigNumString ToBase64String() const;

    static const char szBase64[];

private:
    void HandleCarry();
    unsigned int m_nSize;
    unsigned int * m_arVal;
};