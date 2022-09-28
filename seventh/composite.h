#pragma once

#include<iostream>
#include<string>
#include<list>
using std::string;
using std::list;

class University
{
public:
    University(string tmp):Name(tmp){}
    virtual void attach(University * cmp){}
    virtual void detach(University * cmp){}
    virtual void display(string str){}

    virtual void lineofduty(string tmp){}
protected:
    string Name;
    list<University*> vec_cp;
};

class Compus: public University
{
public:
    Compus(string tmp):University(tmp){}
    virtual void attach(University * cmp);
    virtual void detach(University * cmp);
    virtual void display(string str);
    virtual void lineofduty(string tmp);
};

class Hr_Department: public University
{
public:
    Hr_Department(string tmp):University(tmp){}

    virtual void display(string str);
    virtual void lineofduty(string tmp);
};

class Fc_Department: public University
{
public:
    Fc_Department(string tmp):University(tmp){}

    virtual void display(string str);
    virtual void lineofduty(string tmp);
};

class Ed_Department: public University
{
public:
    Ed_Department(string tmp):University(tmp){}

    virtual void display(string str);
    virtual void lineofduty(string tmp);
};

void Compus::attach(University * cmp)
{
    if(cmp != nullptr)
    {
        vec_cp.push_back(cmp);
    }
}

void Compus::detach(University * cmp)
{
    if(cmp != nullptr)
    {
        vec_cp.remove(cmp);
    }
}

void Compus::display(string str)
{
    std::cout << str << Name << std::endl;
    for(auto it = vec_cp.begin(); it != vec_cp.end(); it++)
    {
        (*it) -> display(str);
    }
}

void Compus::lineofduty(string tmp)
{
    string name = Name;
    for(auto it = vec_cp.begin(); it != vec_cp.end(); it++)
    {
        (*it) ->lineofduty(name);
    }
}

void Hr_Department::lineofduty(string tmp)
{
    std::cout << tmp <<"人事管理" << std::endl; 
}

void Fc_Department::lineofduty(string tmp)
{
    std::cout << tmp <<"财务管理" << std::endl;
}

void Ed_Department::lineofduty(string tmp)
{
    std::cout << tmp <<"教务管理" << std::endl;
}

void Hr_Department::display(string str)
{
    std::cout << str << Name << std::endl;
}

void Fc_Department::display(string str)
{
    std::cout << str << Name << std::endl;
}

void Ed_Department::display(string str)
{
    std::cout << str << Name << std::endl;
}