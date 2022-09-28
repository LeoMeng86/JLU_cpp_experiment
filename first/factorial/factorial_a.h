#pragma once
#include<iostream>
#include<string>
#include<cmath>
#include<algorithm>
#include<stdlib.h>
#include<cstring>

const int maxn = 5000;

void multiply(int *a, int b)
{
    for(int i = 0; a[i] != -1; i++)
    {
        a[i] = a[i] * b;
    }
    for(int i = 0; a[i] != -1; i++)
    {
        if(a[i] >= 10)
        {
            if(a[i+1] == -1) a[i+1] = a[i] / 10;
            else a[i+1] += a[i] / 10;
            a[i] = a[i] % 10;
        } 
    }
}


void print(int *b){
	for(int i = maxn - 1; i >= 0; i--){
        if(b[i] != -1) std::cout << b[i];
	}
}