#include "Header.h"
#include "Car.h"
#include "Mainclass.h"
#include "Admin.h"
#include <stdio.h>
int main()
{
    MainClass work;
    char ch;
    do
    {
        cout<<"\n\n\n\t\t\t\tВыберите роль!";
        cout<<"\n\n\t1.Покупатель ";
        cout<<"\n\n\t2.Администратор";
        cout<<"\n\n\t3.Выход";
        cout<<"\n\n\tВаш выбор (1-3): ";
        ch=getchar();
        switch(ch)
        {
            case '1':
            {
                work.showData();
                work.toBookATicket();
                User buyer;
                buyer.user_menu();
                
                break;
            }
            case '2':
            {
                Admin admn;
                admn.login();
                admn.accounts_menu();
              work.getStarted();
                break;
            }
            case '3':
            {
                exit(0);
            default :cout<<"\a";
            }
        }
    }
    while(ch!='3');
}
