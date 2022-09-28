#pragma once
#include<cstring>
#include<iostream>
#include<algorithm>

class CString
{
private:
    char *str;
    friend std::ostream& operator<<(std::ostream & out, const CString &s);
public:
    CString(){};
    CString(char* pn)
    {
        int len = strlen(pn);
        str = new char[len + 1];
        strcpy(str, pn);
    }

    CString(const CString & s)
    {
        int len = strlen(s.str);
        str = new char[len + 1];
        strcpy(str, s.str);
    }

    CString(int n, char m)
    {
        str = new char[n + 1];
        for(int i = 0; i <= n - 1; i++)
        {
            str[i] = m;
        }
        str[n] = '\0';
    }

    CString(const CString & s, int strbegin, int length)
    {
        str = new char[length + 1];
        for(int i = 0; i <= length - 1; i++)
        {
            str[i] = s.str[strbegin+i];
        }
        str[length] = '\0';
    }

    virtual ~CString()
    {
        delete[] str;
    }

    void swap(int a, int b)
    {
        char c = str[a];
        str[a] = str[b];
        str[b] = c;
    }

    int len()
    {
        return strlen(str);
    }

    CString& operator+(const CString& s);
    CString& operator=(const CString& s);
    char& operator[](int n);
    CString& operator()(int strbegin, int len);
};

std::ostream& operator<<(std::ostream & out, const CString &s)
{
    int len = strlen(s.str);
    for(int i = 0; i <= len - 1; i++)
    {
        out << s.str[i];
    }
    return out;
}

CString& CString::operator+(const CString& s)
{
    char *pstr =str;
    str = new char[strlen(str)+strlen(s.str)+1];
    strcpy(str,pstr);
    strcat(str,s.str);
    delete[] pstr;
    return *this;
}

CString& CString::operator=(const CString& s)
{
    delete[] str;
    int len = strlen(s.str);
    str = new char[len + 1];
    strcpy(str, s.str);
    return *this;
}

char& CString::operator[](int n)
{
    int len = strlen(str);
    if(n >= 0 && n <= len - 1)
    {
        return str[n];
    }
    else
    {
        std::cout << "error";
        exit(0);
    }
}

CString& CString::operator()(int strbegin, int len)
{
    char* tmp = str;
    str = new char[len + 1];
    for(int i = 0; i <= len - 1; i++)
    {
        str[i] = tmp[i+ strbegin];
    }
    str[len] = '\0';
    delete[] tmp;
    return *this;
}