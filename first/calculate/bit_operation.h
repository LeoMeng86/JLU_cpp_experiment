#pragma once
#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <algorithm>

class Bit_Operation
{
public:
    int Yu(int a, int b)
    {
        return a & b;
    }

    int Huo(int a, int b)
    {
        return a | b;
    }

    int Yihuo(int a, int b)
    {
        return a ^ b;
    }

    int Fan(int a)
    {
        return ~a;
    }

    int Zy(int a, int i)
    {
        return a << i;
    }

    int Yy(int a, int i)
    {
        return a >> i;
    }
};

int add(int a, int b);
int multiply(int a, int b);
int sub(int a, int b);

int add(int a, int b)
{
    Bit_Operation Bit;
    int sum = Bit.Yihuo(a,b);
    int jinwei = Bit.Yu(a,b) << 1;
    while( jinwei !=  0)
    {
        int x = sum;
        int y = jinwei;
        sum = Bit.Yihuo(x,y);
        jinwei = Bit.Yu(x,y) << 1;
    }
    return sum;
}

int sub(int a, int b)
{
    Bit_Operation Bit;
    int subb = add(Bit.Fan(b), 1);
    int result = add(a, subb);
    return result;
}

int multiply(int a, int b)
{
    Bit_Operation Bit;
    int ma = a < 0 ? add(Bit.Fan(a), 1) : a;
    int mb = b < 0 ? add(Bit.Fan(b), 1) : b;
    int result = 0;
    int count = 0;

    while(count < mb)
    {
        result = add(result, a);
        count = add(count, 1);
    }

    if((a^b) < 0)
    {
        result = add(Bit.Fan(result), 1);
    }

    return result;
}