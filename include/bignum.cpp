//
// Created by Maellys on 2020/3/5.
//

// BigNum.cpp: implementation of the CBigNum class.
//
//////////////////////////////////////////////////////////////////////
#ifndef RSA_BIGNUM_H
#define RSA_BIGNUM_H

#endif //RSA_BIGNUM_H
#include <cstring>
#include <cstdio>
#include <ctime>
#include "bignum.h"

const char CBigNum::szBase64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBigNum::CBigNum() : m_arVal(0), m_nSize(0)
{
}

CBigNum::CBigNum(unsigned int nValue) : m_arVal(0), m_nSize(0)
{
    if (m_arVal != NULL)
        delete[] m_arVal;

    m_nSize=2;
    m_arVal = new unsigned int[m_nSize];
    m_arVal[0] = nValue & 0xFFFF;
    m_arVal[1] = nValue >> 16;
}

CBigNum::~CBigNum()
{
    if (m_arVal != NULL)
    {
        delete[] m_arVal;
        m_arVal = NULL;
        m_nSize = 0;
    }

}

CBigNum::CBigNum(const char *szSourceVal) : m_arVal(0), m_nSize(0)
{
    *this=szSourceVal;
}

CBigNum & CBigNum::operator=(const char *szSourceVal)
{
    unsigned int nLen = strlen(szSourceVal);
    unsigned int nIdx;
    const char *pChar;
    CBigNum Pow10;

    operator=(0U);

    if (m_arVal != NULL)
    {
        Pow10 = 1;
        for (pChar = szSourceVal + nLen - 1, nIdx=0; pChar >= szSourceVal; pChar--, nIdx++)
        {
            operator+=(Pow10 * (unsigned int)(*pChar - '0'));
            Pow10*=10;
        }
    }
    return *this;
}


CBigNum &CBigNum::operator+=(const CBigNum &rhs)
{
    unsigned int nIdx;

    if (rhs.m_nSize > m_nSize)
        Resize(rhs.m_nSize);

    for (nIdx = 0; nIdx < rhs.m_nSize; nIdx++)
    {
        m_arVal[nIdx] += rhs.m_arVal[nIdx];
    }

    HandleCarry();
    return *this;
}

CBigNum &CBigNum::operator=(unsigned int intVal)
{
    unsigned int nIdx;

    for (nIdx = 0; nIdx < m_nSize; nIdx++)
    {
        m_arVal[nIdx] = 0;
    }

    if (m_nSize <= 0)
        Resize(1);

    m_arVal[0] = intVal;

    HandleCarry();
    return *this;
}

void CBigNum::HandleCarry()
{
    unsigned int nIdx;

    for (nIdx=0; nIdx < m_nSize; nIdx++)
    {
        if ((m_arVal[nIdx] & 0xFFFF0000) != 0)
        {
            if (nIdx >= m_nSize - 1)
            {
                Resize(nIdx + 2);
            }
            m_arVal[nIdx+1] += (m_arVal[nIdx] >> 16);
            m_arVal[nIdx] &= 0xFFFF;
        }
    }
}

void CBigNum::Resize(unsigned int nNewSize)
{
    unsigned int *pNewVal;
    unsigned int nIdx;

    if (nNewSize > 0)
        pNewVal = new unsigned int[nNewSize];
    else
        pNewVal = NULL;

    if (nNewSize < m_nSize)
        m_nSize = nNewSize;

    for (nIdx=0; nIdx < m_nSize; nIdx++)
    {
        pNewVal[nIdx] = m_arVal[nIdx];
    }

    for (;nIdx<nNewSize; nIdx++)
    {
        pNewVal[nIdx] = 0;
    }

    if (m_arVal)
        delete[] m_arVal;

    m_arVal = pNewVal;
    m_nSize = nNewSize;
}

CBigNum &CBigNum::operator>>=(unsigned int rhs)
{
    unsigned int nIdx;

    if (m_nSize)
    {
        while(rhs>=16)
        {
            for (nIdx=0; nIdx < m_nSize-1; nIdx++)
            {
                m_arVal[nIdx] = m_arVal[nIdx+1];
            }
            rhs-=16;
            m_arVal[nIdx] = 0;
        }
    }

    for (nIdx=0; nIdx < m_nSize-1; nIdx++)
    {
        m_arVal[nIdx] = (m_arVal[nIdx] >> rhs) | ((m_arVal[nIdx+1] << (16 - rhs)) & 0xFFFF);
    }

    if (nIdx < m_nSize)
        m_arVal[nIdx] >>= rhs;

    return *this;
}

CBigNum &CBigNum::operator<<=(unsigned int rhs)
{
    unsigned int nIdx;

    if (m_nSize)
    {
        while(rhs>=16)
        {
            if (m_arVal[m_nSize-1])
                Resize(m_nSize+1);
            for (nIdx = m_nSize-1; nIdx > 0; nIdx--)
            {
                m_arVal[nIdx] = m_arVal[nIdx-1];
            }
            rhs -=16;
            m_arVal[0] = 0;
        }

        if ((m_arVal[m_nSize - 1] << rhs) & 0xFFFF0000)
            Resize(m_nSize + 1);
    }

    if (m_nSize)
    {
        for (nIdx = m_nSize-1; nIdx > 0; nIdx--)
        {
            m_arVal[nIdx] = (m_arVal[nIdx] << rhs) | (m_arVal[nIdx-1] >> (16-rhs));
            m_arVal[nIdx] &= 0xFFFF;
        }
        m_arVal[0] <<= rhs;
        m_arVal[0] &= 0xFFFF;
    }

    return *this;
}

CBigNum CBigNum::operator<<(unsigned int rhs) const
{
    CBigNum result(*this);
    result <<= rhs;
    return result;
}

CBigNum CBigNum::operator>>(unsigned int rhs) const
{
    CBigNum result(*this);
    result >>= rhs;
    return result;
}

CBigNum::operator bool(void) const
{
    unsigned int nIdx;

    for (nIdx=0; nIdx < m_nSize; nIdx++)
        if (m_arVal[nIdx]) return true;

    return false;
}


CBigNum & CBigNum::operator&=(CBigNum rhs)
{
    unsigned int nIdx;
    unsigned int nMin;

    if (rhs.m_nSize < m_nSize)
        nMin = rhs.m_nSize;

    for (nIdx=0; nIdx < nMin; nIdx++)
        m_arVal[nIdx] &= rhs.m_arVal[nIdx];

    for (;nIdx < m_nSize; nIdx++)
        m_arVal[nIdx] = 0;

    return *this;
}

unsigned int CBigNum::operator&(unsigned int rhs)
{
    if (m_nSize)
        return m_arVal[0] & rhs;
    else
        return 0;
}

CBigNum &CBigNum::operator=(CBigNum rhs)
{
    if (rhs.m_arVal != m_arVal)
    {
        delete m_arVal;
        m_arVal = NULL;
        m_nSize=0;

        unsigned int nIdx;
        Resize(rhs.m_nSize);
        for (nIdx = 0; nIdx < m_nSize; nIdx++)
            m_arVal[nIdx] = rhs.m_arVal[nIdx];
    }
    return *this;
}

CBigNum CBigNum::Pow(unsigned int rhs) const
{
    CBigNum Result(1);
    CBigNum CurrentVal = *this;

    while (rhs)
    {
        if (rhs & 1U)
            Result *=(CurrentVal);
        rhs >>= 1;
        CurrentVal *= CurrentVal;
    }

    return Result;
}

CBigNum CBigNum::PowMod(CBigNum rhs, const CBigNum &mod, const clock_t ctShowSteps) const
{
    CBigNum Result(1);
    CBigNum CurrentVal = *this;
    int nSteps = rhs.log2();
    clock_t ctStart, ctCurrent;

    ctStart = ctCurrent = clock();

    while (rhs > 0U)
    {

        if (rhs.m_arVal[0] & 1U)
        {
            Result = (Result * CurrentVal) % mod;
            Result.Reduce();
        }
        rhs>>=1U;
        CurrentVal = (CurrentVal * CurrentVal) % mod;
        CurrentVal.Reduce();
        nSteps--;
        if (ctShowSteps)
        {
            if (clock() > ctCurrent + ctShowSteps)
            {

                ctCurrent = clock();
            }
        }
    }

    return Result;
}

bool CBigNum::operator==(unsigned int rhs) const
{
    if (m_nSize>=2)
        return ((m_arVal[0] == (rhs & 0xFFFF)) && ((m_arVal[1]<<16) == (rhs & 0xFFFF0000)));
    else if (m_nSize==1)
        return (m_arVal[0] == rhs);
    else
        return (rhs == 0);
}

bool CBigNum::operator!=(unsigned int rhs) const
{
    return !(operator==(rhs));
}

CBigNum CBigNum::operator *(const CBigNum &rhs) const
{
    CBigNum Result=0U;
    unsigned int i, j;

    if (Result.m_nSize != rhs.m_nSize + m_nSize)
        Result.Resize(rhs.m_nSize + m_nSize);
    for (i=0; i < m_nSize; i++)
    {
        for (j=0; j<rhs.m_nSize; j++)
            Result.m_arVal[i+j] += m_arVal[i] * rhs.m_arVal[j];
        Result.HandleCarry();
    }
    return Result;
}

CBigNum &CBigNum::operator *=(const CBigNum &rhs)
{
    return *this = *this * rhs;
}

CBigNum CBigNum::operator *(unsigned int rhs) const
{
    unsigned int nIdx;

    CBigNum result(*this);

    if (result.m_nSize==0)
    {
        return result;
    }

    for (nIdx = 0; nIdx < result.m_nSize; nIdx++)
    {
        result.m_arVal[nIdx] *= rhs;
    }
    result.HandleCarry();
    return result;
}

CBigNum::CBigNum(const CBigNum &copy) : m_nSize(0), m_arVal(0)
{
    unsigned int nIdx;

    Resize(copy.m_nSize);

    for (nIdx = 0; nIdx < m_nSize; nIdx++)
        m_arVal[nIdx] = copy.m_arVal[nIdx];
}

CBigNum &CBigNum::operator*=(unsigned int rhs)
{
    unsigned int nIdx;

    if (m_nSize <= 0)
    {
        operator=(0U);
    }
    else
    {
        for (nIdx = 0; nIdx < m_nSize; nIdx++)
        {
            m_arVal[nIdx] *= rhs;
        }
        HandleCarry();
    }
    return *this;
}

CBigNumString::CBigNumString() : m_szBuffer(NULL), m_nSize(0)
{
}

CBigNumString::~CBigNumString()
{
    if (m_szBuffer)
    {
        delete[] m_szBuffer;
        m_szBuffer = NULL;
        m_nSize = 0;
    }
}

void CBigNumString::Realloc(unsigned int nByteCount)
{
    if (m_szBuffer)
    {
        delete[] m_szBuffer;
        m_szBuffer = NULL;
    }
    m_szBuffer = new char[nByteCount];
    memset(m_szBuffer, 0, nByteCount);
    m_nSize = nByteCount;
}

CBigNumString::CBigNumString(const CBigNumString &rhs) : m_szBuffer(NULL), m_nSize(0)
{
    if ((rhs.m_szBuffer) && (rhs.m_nSize > 0))
    {
        m_szBuffer = new char[rhs.m_nSize];
        strcpy(m_szBuffer, rhs.m_szBuffer);
        m_nSize = rhs.m_nSize;
    }
}

CBigNumString::operator const char *() const
{
    return m_szBuffer;
}

CBigNum CBigNum::FromByteString(const char *szIn, const unsigned int nLength)
{
    CBigNum Result;
    unsigned int i, r;
    unsigned int nUseLength;

    if (!nLength)
        nUseLength = strlen(szIn);
    else
        nUseLength = nLength;

    Result.m_nSize = (nUseLength+1) >> 1;
    Result.m_arVal = new unsigned int[Result.m_nSize];

    for (i=0; i<nUseLength; i+=1)
    {
        r = nUseLength - 1 - i;
        if (i % 2)
            Result.m_arVal[i >> 1] |= ((unsigned int)szIn[r]) << 8;
        else
            Result.m_arVal[i >> 1] = szIn[r];
    }

    return Result;
}

CBigNum CBigNum::FromHexString(const char *szIn)
{
    CBigNum Result;
    unsigned int i, r;
    unsigned int nUseLength;
    unsigned int nPlaceVal;

    nUseLength = strlen(szIn);

    Result.m_nSize = (nUseLength+3) >> 2;
    Result.m_arVal = new unsigned int[Result.m_nSize];

    for (i=0; i<nUseLength; i+=1)
    {
        r = nUseLength - 1 - i;
        if ((szIn[r] >= '0') && (szIn[r] <= '9'))
            nPlaceVal = szIn[r] - '0';
        else if ((szIn[r] >= 'A') && (szIn[r] <= 'F'))
            nPlaceVal = szIn[r] - 'A' + 10;
        else if ((szIn[r] >= 'a') && (szIn[r] <= 'f'))
            nPlaceVal = szIn[r] - 'a' + 10;
        else
            nPlaceVal = 0;

        if (!(i % 4))
            Result.m_arVal[i >> 2] = nPlaceVal;
        else
            Result.m_arVal[i >> 2] |= nPlaceVal << ((i % 4) << 2);
    }
    return Result;
}

CBigNum CBigNum::FromBase64String(const char *szIn)
{
    CBigNum Result;
    int i, r;
    const char *pc;
    unsigned int nUseLength;
    unsigned int nByteCount;
    unsigned char szCharMap[255];
    unsigned char bin[4], bout;

    memset(szCharMap, 255, 255);
    for (i=0; i<sizeof(szBase64)-1; i++)
    {
        szCharMap[szBase64[i]] = i;
    }
    szCharMap['='] = 0;

    nUseLength = strlen(szIn);
    nByteCount = (nUseLength / 4) * 3;

    Result.Resize((nByteCount+1)/2);

    for (pc=szIn+nUseLength-1;((pc > szIn) && (255 == szCharMap[*pc]));pc--)
        ;
    for (r=0; r<4; r++)
    {
        bin[r] = *pc;
        while ((pc > szIn) && (255 == szCharMap[*(--pc)]))
            ;
    }

    i=0;
    if (bin[0] == '=')
        i=-1;
    if (bin[1] == '=')
        i=-2;

    while (true)
    {
        if ((i>=0) && ((unsigned)i>>1 < Result.m_nSize))
        {
            bout = szCharMap[bin[0]] | ((szCharMap[bin[1]] & 0x03) << 6);
            Result.m_arVal[i>>1] |= bout << ((i % 2) << 3);
        }
        i++;

        if ((i>=0) && ((unsigned)i>>1 < Result.m_nSize))
        {
            bout = ((szCharMap[bin[1]] & 0x3C) >> 2) | ((szCharMap[bin[2]] & 0x0F) << 4);
            Result.m_arVal[i>>1] |= bout << ((i % 2) << 3);
        }
        i++;

        if ((unsigned)i>>1 < Result.m_nSize)
        {
            bout = ((szCharMap[bin[2]] & 0x30) >> 4) | (szCharMap[bin[3]] << 2);
            Result.m_arVal[i>>1] |= bout << ((i % 2) << 3);
        }
        i++;

        if (pc <= szIn)
            break;

        for (r=0; r<4; r++)
        {
            bin[r] = *pc;
            while ((pc > szIn) && (255 == szCharMap[*(--pc)]))
                ;
        }
    }

    Result.Reduce();
    return Result;
}

CBigNumString CBigNum::ToByteString(bool bMakePrintable) const
{
    CBigNumString Result;
    unsigned int nOutSize = m_nSize * 2;
    unsigned int i, r;

    while ((nOutSize > 0) && !(m_arVal[(nOutSize-1) >> 1] & (0xFF << (((nOutSize-1) % 2) << 3))))
        nOutSize--;

    Result.Realloc(nOutSize+1);
    for (i=0; i<nOutSize; i++)
    {
        r = nOutSize - 1 - i;
        if (i % 2)
            Result[r] = (m_arVal[i >> 1] >> 8) & 0xFF;
        else
            Result[r] = m_arVal[i >> 1] & 0xFF;
        if (bMakePrintable)
        {
            switch (Result[r] & 0xE0)
            {
                case 0:
                    switch(Result[r])
                    {
                        case 10: // lf
                        case 13: // cr
                            break;
                        default:
                            Result[r] = '.';
                            break;
                    }
                    break;
                case 0x80:
                case 0xA0:
                case 0xC0:
                case 0xE0:
                    Result[r] = '.';
                    break;
                default:
                    break;
            }
        }
    }

    Result[nOutSize] = '\0';
    return Result;
}

CBigNumString CBigNum::ToHexString() const
{
    CBigNumString Result;
    unsigned int nOutSize = m_nSize * 4;
    unsigned int i, r;

    while ((nOutSize > 0) && !(m_arVal[(nOutSize-1) >> 2] & (0xF << (((nOutSize-1) % 4) << 2))))
        nOutSize--;

    Result.Realloc(nOutSize+1);
    for (i=0; i<nOutSize; i++)
    {
        r = nOutSize - 1 - i;
        switch((m_arVal[i >> 2] >> ((i % 4) << 2)) & 0xF)
        {
            case 0:
                Result[r] = '0';
                break;
            case 1:
                Result[r] = '1';
                break;
            case 2:
                Result[r] = '2';
                break;
            case 3:
                Result[r] = '3';
                break;
            case 4:
                Result[r] = '4';
                break;
            case 5:
                Result[r] = '5';
                break;
            case 6:
                Result[r] = '6';
                break;
            case 7:
                Result[r] = '7';
                break;
            case 8:
                Result[r] = '8';
                break;
            case 9:
                Result[r] = '9';
                break;
            case 10:
                Result[r] = 'A';
                break;
            case 11:
                Result[r] = 'B';
                break;
            case 12:
                Result[r] = 'C';
                break;
            case 13:
                Result[r] = 'D';
                break;
            case 14:
                Result[r] = 'E';
                break;
            case 15:
                Result[r] = 'F';
                break;
            default:
                Result[r] = '!';
                break;
        }
    }

    Result[nOutSize] = '\0';
    return Result;
}



CBigNum &CBigNum::operator-=(const CBigNum &rhs)
{
    unsigned int nPos;
    unsigned int nBorrow;

    for (nPos=0; nPos<m_nSize; nPos++)
    {
        if (nPos < rhs.m_nSize)
        {
            if (m_arVal[nPos] < rhs.m_arVal[nPos])
            {
                for (nBorrow=nPos+1; nBorrow < m_nSize; nBorrow++)
                {
                    if (m_arVal[nBorrow]>0)
                    {
                        m_arVal[nBorrow]--;
                        m_arVal[nPos] += (1<<16);
                        break;
                    }
                    else
                    {
                        m_arVal[nBorrow] = 0xFFFF;
                    }
                }
            }
            m_arVal[nPos] -= rhs.m_arVal[nPos];
        }
    }

    return *this;
}

CBigNum &CBigNum::operator-=(const unsigned int rhs)
{
    unsigned int nBorrow;

    if (m_nSize > 0)
    {
        if (m_arVal[0] < rhs)
        {
            for (nBorrow = 1; nBorrow < m_nSize; nBorrow++)
            {
                if (m_arVal[nBorrow]>0)
                {
                    m_arVal[nBorrow]--;
                    m_arVal[0] += 1<<16;
                    break;
                }
                else
                {
                    m_arVal[nBorrow] = 0xFFFF;
                }
            }
        }
        m_arVal[0] -= rhs;
    }
    return *this;
}

CBigNum CBigNum::operator/(const CBigNum &rhs) const
{
    CBigNum result(rhs);
    CBigNum numer;
    CBigNum denom;
    CBigNum placeval;
    unsigned int nMag=0;

    if (rhs==0U) return result;

    while (result < *this)
        result<<=16, nMag+=16;

    if (result==*this)
    {
        return CBigNum(1)<<nMag;
    }

    while ((result > *this) && (nMag))
        result>>=1, nMag--;

    numer = *this;
    denom = result;
    result = 0U;

    for (placeval = CBigNum(1)<<nMag; nMag; placeval>>=1, nMag--)
    {
        if (numer >= denom)
        {
            result |= placeval;
            numer-=denom;
        }
        denom>>=1;
    }

    result.m_arVal[0] |= ((numer >= denom)?1:0);

    return result;
}

CBigNum &CBigNum::operator/=(const CBigNum &rhs)
{
    return *this = *this / rhs;
}

CBigNum CBigNum::operator/(const unsigned int rhs) const
{
    return *this / CBigNum(rhs);
}

CBigNum &CBigNum::operator/=(const unsigned int rhs)
{
    return *this = *this / rhs;
}

CBigNum CBigNum::operator%(const CBigNum &rhs) const
{
    CBigNum result(rhs);
    CBigNum numer;
    CBigNum denom;
    CBigNum placeval;
    unsigned int nMag=0;

    if (rhs==0U) return result;

    while (result < *this)
        result<<=16, nMag+=16;

    if (result==*this)
        return CBigNum(0U);

    while ((result > *this) && (nMag))
        result>>=1, nMag--;

    numer = *this;
    denom = result;
    result = 0U;

    for (placeval = CBigNum(1)<<nMag; nMag; placeval>>=1, nMag--)
    {
        if (numer >= denom)
        {
            result |= placeval;
            numer-=denom;
        }
        denom>>=1;
    }

    if (numer >= denom)
    {
        result.m_arVal[0] |= 1;
        numer -= denom;
    }

    return numer;
}

unsigned int CBigNum::operator%(const unsigned int rhs) const
{
    return (*this % CBigNum(rhs)).m_arVal[0];
}

CBigNum &CBigNum::operator%=(const CBigNum &rhs)
{
    return *this = *this % rhs;
}

unsigned int CBigNum::operator%=(const unsigned int rhs)
{
    *this = *this % rhs;
    return this->m_arVal[0];
}

bool CBigNum::operator<(const CBigNum &rhs) const
{
    unsigned int nIdx;
    unsigned int nMaxSize;

    if (rhs.m_nSize > m_nSize)
        nMaxSize = rhs.m_nSize;
    else
        nMaxSize = m_nSize;

    for (nIdx = nMaxSize-1; nIdx != 0xFFFFFFFF; nIdx--)
    {
        if (nIdx < rhs.m_nSize)
        {
            if (nIdx < m_nSize)
            {
                if (rhs.m_arVal[nIdx] == m_arVal[nIdx])
                    continue;
                return  m_arVal[nIdx] < rhs.m_arVal[nIdx];
            }
            else
            if (rhs.m_arVal[nIdx] != 0)
                return true;
        }
        else
        if (m_arVal[nIdx] != 0)
            return false;
    }

    return false;
}

bool CBigNum::operator<=(const CBigNum &rhs) const
{
    unsigned int nIdx;
    unsigned int nMaxSize;

    if (rhs.m_nSize > m_nSize)
        nMaxSize = rhs.m_nSize;
    else
        nMaxSize = m_nSize;

    for (nIdx = nMaxSize-1; nIdx != 0xFFFFFFFF; nIdx--)
    {
        if (nIdx < rhs.m_nSize)
        {
            if (nIdx < m_nSize)
            {
                if (rhs.m_arVal[nIdx] == m_arVal[nIdx])
                    continue;
                return  m_arVal[nIdx] < rhs.m_arVal[nIdx];
            }
            else
            if (rhs.m_arVal[nIdx] != 0)
                return true;
        }
        else
        if (m_arVal[nIdx] != 0)
            return false;
    }

    return true;
}

bool CBigNum::operator==(const CBigNum &rhs) const
{
    unsigned int nIdx;
    unsigned int nMaxSize;

    if (rhs.m_nSize > m_nSize)
        nMaxSize = rhs.m_nSize;
    else
        nMaxSize = m_nSize;

    nIdx = nMaxSize-1;
    if (nIdx >=0)
    {
        do
        {
            if (nIdx < rhs.m_nSize)
            {
                if (nIdx < m_nSize)
                {
                    if (rhs.m_arVal[nIdx] != m_arVal[nIdx])
                        return false;
                }
                else
                if (rhs.m_arVal[nIdx] != 0)
                    return false;
            }
            else
            if (m_arVal[nIdx] != 0)
                return false;
        } while (nIdx-- > 0);
    }
    return true;
}

bool CBigNum::operator!=(const CBigNum &rhs) const
{
    return !(operator==(rhs));
}

bool CBigNum::operator>(const CBigNum &rhs) const
{
    return !(*this <= rhs);
}

bool CBigNum::operator>=(const CBigNum &rhs) const
{
    return !(*this < rhs);
}

bool CBigNum::operator<(const unsigned int rhs) const
{
    int nIdx;

    switch(m_nSize)
    {
        case 0:
            return rhs > 0;
        case 1:
            return m_arVal[0] < rhs;
        case 2:
            return ((m_arVal[1] << 16) | m_arVal[0]) < rhs;
        default:
            for (nIdx = m_nSize-1; nIdx >= 0; nIdx--)
            {
                if (m_arVal[nIdx] != 0)
                {
                    switch(nIdx)
                    {
                        case 0:
                            return m_arVal[0] < rhs;
                        case 1:
                            return ((m_arVal[1] << 16) | m_arVal[0]) < rhs;
                        default:
                            return false;
                    }
                }
            }
    }
    return false;
}

bool CBigNum::operator<=(const unsigned int rhs) const
{
    int nIdx;

    switch(m_nSize)
    {
        case 0:
            return rhs >= 0;
        case 1:
            return m_arVal[0] <= rhs;
        case 2:
            return ((m_arVal[1] << 16) | m_arVal[0]) <= rhs;
        default:
            for (nIdx = m_nSize-1; nIdx >= 0; nIdx--)
            {
                if (m_arVal[nIdx] != 0)
                {
                    switch(nIdx)
                    {
                        case 0:
                            return m_arVal[0] <= rhs;
                        case 1:
                            return ((m_arVal[1] << 16) | m_arVal[0]) <= rhs;
                        default:
                            return false;
                    }
                }
            }
    }

    return true;
}

bool CBigNum::operator>(const unsigned int rhs) const
{
    return !(*this <= rhs);
}

bool CBigNum::operator>=(const unsigned int rhs) const
{
    return !(*this < rhs);
}

CBigNum &CBigNum::operator |=(const CBigNum &rhs)
{
    unsigned int nIdx;

    if (m_nSize < rhs.m_nSize)
        Resize(rhs.m_nSize);

    for (nIdx=0; nIdx < rhs.m_nSize; nIdx++)
    {
        m_arVal[nIdx] |= rhs.m_arVal[nIdx];
    }

    return *this;
}

CBigNum CBigNum::operator|(const CBigNum &rhs) const
{
    CBigNum Result(*this);
    Result |= rhs;
    return Result;
}

CBigNum &CBigNum::operator|=(const unsigned int rhs)
{
    this->m_arVal[0] |= rhs & 0xFFFF;
    this->m_arVal[1] |= rhs >> 16;
    return *this;
}

CBigNum CBigNum::operator|(const unsigned int rhs) const
{
    CBigNum Result(*this);
    Result.m_arVal[0] |= rhs & 0xFFFF;
    Result.m_arVal[1] |= rhs >> 16;
    return Result;
}

CBigNum::operator CBigNumString() const
{
    CBigNumString TempBigNum;
    CBigNum outval(*this);
    unsigned int nDigit;
    unsigned int nNumLen;
    unsigned int nPos;

    if (m_nSize <= 0)
    {
        TempBigNum.Realloc(2);
        TempBigNum[0U] = '0';
        TempBigNum[1U] = '\0';
        return TempBigNum;
    }

    if (outval == 0U)
    {
        TempBigNum.Realloc(2);
        TempBigNum[0U] = '0';
        TempBigNum[1U] = '\0';
        return TempBigNum;
    }

    nNumLen = m_nSize * 5;
    TempBigNum.Realloc(nNumLen+1);

    for (nDigit=nNumLen-1; outval>0U; nDigit--, outval/=10U)
    {
        TempBigNum[nDigit] = '0' + (outval % 10U);
    }

    if(++nDigit > 0U)
    {
        for (nPos=0; nDigit < nNumLen; nPos++, nDigit++)
        {
            TempBigNum[nPos] = TempBigNum[nDigit];
        }
    }
    TempBigNum[nPos] = '\0';

    return TempBigNum;
}

char & CBigNumString::operator [](unsigned int nIdx)
{
    static char dummychar = '\0';

    if (nIdx < m_nSize)
    {
        return m_szBuffer[nIdx];
    }

    return dummychar;
}

CBigNum::operator const char *() const
{
    static CBigNumString bnstr;

    bnstr = ((CBigNum *)this)->operator CBigNumString();
    return bnstr;
}

const CBigNumString &CBigNumString::operator=(const CBigNumString rhs)
{
    if (m_szBuffer == rhs.m_szBuffer)
    {
        return *this;
    }

    if (m_szBuffer != NULL)
    {
        delete[] m_szBuffer;
        m_szBuffer = NULL;
        m_nSize = 0;
    }
    if (rhs.m_nSize)
    {
        m_szBuffer = new char[rhs.m_nSize];
        m_nSize = rhs.m_nSize;
        strcpy(m_szBuffer, rhs.m_szBuffer);
    }

    return *this;
}

CBigNum CBigNum::factorial() const
{
    CBigNum Num;

    CBigNum dest(*this);

    for (Num=(*this)-1U; Num; Num-=1U)
    {
        dest *= Num;
    }
    return dest;
}

CBigNum CBigNum::operator-(const unsigned int rhs) const
{
    CBigNum rslt(*this);
    rslt -= rhs;
    return rslt;
}

CBigNum CBigNum::operator+(const CBigNum &rhs) const
{
    CBigNum rslt(*this);
    rslt += rhs;
    return rslt;
}

CBigNum CBigNum::operator+(const unsigned int rhs) const
{
    CBigNum rslt(*this);
    rslt += rhs;
    return rslt;
}

CBigNum CBigNum::sqrt() const
{
    CBigNum nGuess(*this<<2U);
    CBigNum nUpper(*this<<1U);
    CBigNum nLower(1);
    CBigNum nSqr;

    if (nGuess < nLower)
        nGuess = nLower;

    while (nLower < nUpper)
    {
        nSqr = nGuess*nGuess;
        if (nSqr > *this)
        {
            if (nUpper == nGuess)
                return nGuess;
            nUpper = nGuess;
        }
        else if (nSqr < *this)
        {
            if (nLower == nGuess)
                return nGuess;
            nLower = nGuess;
        }
        else
            return nGuess;
        nGuess = (nLower + nUpper) >> 1U;
    }
    nGuess.Reduce();

    return nGuess;
}

CBigNum CBigNum::gcd(const CBigNum &x, const CBigNum &y)
{
    if (y==0U) return x;
    return gcd(y, x%y);
}

CBigNum CBigNum::lcm(const CBigNum &x, const CBigNum &y)
{
    return x*y/gcd(x,y);
}

unsigned int CBigNum::log10() const
{
    CBigNum nNum(*this);
    unsigned int nLog10=0;

    while(nNum >= 10U)
        nNum/=10U,nLog10++;

    return nLog10;
}

unsigned int CBigNum::log2() const
{
    unsigned int i;
    unsigned int nMag = m_nSize * 16 - 1;

    for (i=m_nSize-1; i>0; i--)
    {
        if(m_arVal[i])
            break;
        nMag -= 16;
    }
    if ((i==0) && (m_arVal[i] == 0))
        return 0;

    while(!(m_arVal[i]&(1U<<(nMag%16))))
        nMag--;

    return nMag;
}

CBigNum CBigNum::Inverse(const CBigNum &mod) const
{
    CBigNum quo, mod1=mod, mod2=*this, modsq = mod * mod;
    CBigNum p1=0U, p2=1U, p3;

    while(mod2)
    {
        quo = mod1 / mod2;
        p3 = mod2;
        mod2 = mod1 % mod2;
        mod1 = p3;
        p3 = modsq + p1;
        p3 -= p2 * quo;
        p3 %= mod;
        p1 = p2;
        p2 = p3;
    }
    p1.Reduce();
    return p1;
}

void CBigNum::Reduce()
{
    unsigned int i;

    if (m_nSize <= 0)
        return;

    for (i=m_nSize-1; i>0; i--)
        if (m_arVal[i])
            break;

    if (++i < m_nSize)
        Resize(i);
}
