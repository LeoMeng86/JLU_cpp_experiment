#pragma once
#include<iostream>
#include<string>
#include<cmath>
#include<algorithm>
#include<stdlib.h>
#include<cstring>

const int maxn = 5000;

void add(int *a, int *b){
	for(int i = 0; a[i] != -1 || b[i] != -1; i++){
        if(a[i] == -1) b[i] =  b[i];
        else if(b[i] == -1) b[i] = a[i];
        else b[i] = a[i] + b[i];
	}
	for(int i = 0; b[i] != -1; i++){
		if(b[i] > 9) {
			if(b[i+1] == -1) b[i+1] = b[i] / 10;
            else b[i+1]+=b[i] / 10;
			b[i] %= 10;
		}
	}
}

void multiply(int *a, int *b, int *c)
{
    for(int i = 0; b[i] != -1; i++)
    {
        for(int j = 0; a[j] != -1; j++)
        {
            if(c[i+j] == -1)  c[j + i] = a[j] * b[i];
            else c[j+i] += a[j] * b[i];
        }
    }
    for(int i = 0; c[i] != -1; i++)
    {
        if(c[i] >= 10)
        {
            if(c[i+1] == -1) c[i+1] = c[i] / 10;
            else c[i+1] += c[i] / 10;
            c[i] = c[i] % 10;
        } 
    }
}

void val(int *a, int *b){
	for(int i = 0; i <= maxn - 1; i++){
		a[i] = b[i];
	}
}

void print(int *b){
	for(int i = maxn - 1; i >= 0; i--){
        if(b[i] != -1) std::cout << b[i];
	}
}