#include <iostream>
#include "composite.h"
using namespace std;

int main()
{    
    Compus Un("吉林大学");
    Fc_Department Un_Fc("吉林大学财务部");
    Ed_Department Un_Ed("吉林大学教务部");
    Hr_Department Un_Hr("吉林大学人事部");

    Un.attach(&Un_Ed);
    Un.attach(&Un_Fc);
    Un.attach(&Un_Hr);

    Compus C_software("吉林大学软件学院");
    Fc_Department C_software_Fc("软件学院财务部");
    Ed_Department C_software_Ed("软件学院教务部");
    Hr_Department C_software_Hr("软件学院人事部");

    C_software.attach(&C_software_Fc);
    C_software.attach(&C_software_Ed);
    C_software.attach(&C_software_Hr);

    Un.attach(&C_software);

    Compus C_Computer("吉林大学计算机科学技术学院");
    Fc_Department C_Computer_Fc("计算机科学技术学院财务部");
    Ed_Department C_Computer_Ed("计算机科学技术学院教务部");
    Hr_Department C_Computer_Hr("计算机科学技术学院人事部");

    C_Computer.attach(&C_Computer_Fc);
    C_Computer.attach(&C_Computer_Ed);
    C_Computer.attach(&C_Computer_Hr);

    Un.attach(&C_Computer);

    string str("#");
    Un.display(str);

    cout << endl;

    Un.lineofduty(str);
    return 0;
}