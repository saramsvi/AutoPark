#include "Admin.h"
#include "Header.h"

void account::create_account()
{
    cout<<"\nВводите № вашего аккаунта:";
    cin>>account_number;
    cout<<"\n\nВводите ваше имя: ";
    cin.ignore();
    cin.getline(name,50);
    cout<<"\nВводите баланс вашего счета: ";
    cin>>deposit;
    cout<<"\n\n\nаккаунт создан!";
}

void account::show_account() const
{
    cout<<"\n№ аккаунта : "<<account_number;
    cout<<"\nВаше имя : ";
    cout<<name;
    cout<<"\nБаланс : "<<deposit;
}


void account::modify()
{
    cout<<"\n№ Аккаунта: "<<account_number;
    cout<<"\nИзменить имя : ";
    cin.ignore();
    cin.getline(name,50);
    cout<<"\nИзменить баланс : ";
    cin>>deposit;
}


void account::dep(int x)
{
    deposit+=x;
}

void account::draw(int x)
{
    deposit-=x;
}

void account::report() const
{
    cout<<account_number<<setw(10)<<" "<<name<<setw(10)<<deposit<<endl;
}


int account::retaccount_number() const
{
    return account_number;
}

int account::retdeposit() const
{
    return deposit;
}


void write_account();    //функция для записи записи в бинарный файл
void display_sp(int);    //функция для отображения данных учетной записи, предоставленной пользователем
void modify_account(int);    //функция для изменения записи файла
void delete_account(int);    //функция удаления записи файла
void display_all();        //функция для отображения всех деталей учетной записи
void deposit_withdraw(int, int); // функция для списания / снятия суммы для данного счета

void Admin :: login()
{
    cout << "\n\nТребуется имя пользователя и пароль!\n\nИмя пользователя:";
    cin >> Username_Attempt;
    
    if(Username_Attempt == Username)
    {
        cout << "Пароль:";
        cin >> Password_Attempt;
        
        if(Password_Attempt == Password)
        {
            cout << "\nДоступ предоставлен!\n\n";
            cin.get();
        }
        else
        {
            cout << "\nX Доступ запрещен X\n\n" << endl;
            login();
        }
    }
    else
    {
        cout << "\n Неправильно. Попробуйте еще раз!\n" << endl;
        login();
    }
};

int User::user_menu()
{
    char choice;
    int num;
    do
    {
        cout<<"\n\n\n\tМеню ";
        cout<<"\n\n\t01. Новый аккаунт";
        cout<<"\n\n\t02. Пополнить счет";
        cout<<"\n\n\t03. Бронировать ";
        cout<<"\n\n\t04. Узнать баланс";
        cout<<"\n\n\t05. Выход";
        cout<<"\n\n\tВаш выбор (1-5): ";
        cin>>choice;
        switch(choice)
        {
            case '1':
                write_account();
                break;
            case '2':
                cout<<"\n\n\tВводите № аккаунта : "; cin>>num;
                deposit_withdraw(num, 1);
                break;
            case '3':
                cout<<"\n\n\tВводите № аккаунта: "; cin>>num;
                deposit_withdraw(num, 2);
                break;
            case '4':
                cout<<"\n\n\tВводите № аккаунта : "; cin>>num;
                display_sp(num);
                break;
            case '5':
                cout<<"\n\n\tСпасибо , что выбрали нас!";
                break;
            default :cout<<"\a";
        }
        cin.ignore();
        cin.get();
    }
    while(choice!='5');
    return 0;
}
int  Admin::accounts_menu()
{
    char choice;
    int num;
    do
    {
        cout<<"\n\n\n\tМеню ";
        cout<<"\n\n\t01. Список всех аккаунтов";
        cout<<"\n\n\t02. Закрыть аккаунт";
        cout<<"\n\n\t03. Изменить аккаунт";
        cout<<"\n\n\t04. Меню работы с машинами";
        cout<<"\n\n\tВаш выбор (1-4): ";
        cin>>choice;
        switch(choice)
        {
            case '1':
                display_all();
                break;
            case '2':
                cout<<"\n\n\tВводите № аккаунта : "; cin>>num;
                delete_account(num);
                break;
            case '3':
                cout<<"\n\n\tВводите № аккаунта: "; cin>>num;
                modify_account(num);
                break;
            case '4':
                break;
            default :cout<<"\a";
        }
        cin.ignore();
        cin.get();
    }
    while(choice!='4');
    return 0;
}
//***************************************************************
//        function to write in file
//****************************************************************

void write_account()
{
    account ac;
    ofstream outFile;
    outFile.open("account.dat",ios::binary|ios::app);
    ac.create_account();
    outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
    outFile.close();
}

//***************************************************************
//        function to read specific record from file
//****************************************************************

void display_sp(int n)
{
    account ac;
    bool flag=false;
    ifstream inFile;
    inFile.open("account.dat",ios::binary);
    if(!inFile)
    {
        cout<<"Файл не существует!!";
        return;
    }
    cout<<"\nБаланс\n";
    
    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
    {
        if(ac.retaccount_number()==n)
        {
            ac.show_account();
            flag=true;
        }
    }
    inFile.close();
    if(flag==false)
        cout<<"\n\n№ аккаунта не существует!";
}
//***************************************************************
//        function to modify record of file
//****************************************************************

void modify_account(int n)
{
    bool found=false;
    account ac;
    fstream File;
    File.open("account.dat",ios::binary|ios::in|ios::out);
    if(!File)
    {
        cout<<"Файл не существует!!";
        return;
    }
    while(!File.eof() && found==false)
    {
        File.read(reinterpret_cast<char *> (&ac), sizeof(account));
        if(ac.retaccount_number()==n)
        {
            ac.show_account();
            cout<<"\n\nВводите новые данные аккаунта:"<<endl;
            ac.modify();
            int pos=(-1)*static_cast<int>(sizeof(account));//static_cast переобразование одного тоипа в другой 
            File.seekp(pos,ios::cur);
            File.write(reinterpret_cast<char *> (&ac), sizeof(account));
            cout<<"\n\n\t Запись обновлена";
            found=true;
        }
    }
    File.close();
    if(found==false)
        cout<<"\n\n Не существует!";
}

//***************************************************************
//        function to delete record of file
//****************************************************************


void delete_account(int n)
{
    account ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.dat",ios::binary);
    if(!inFile)
    {
        cout<<"Файл не существует!!";
        return;
    }
    outFile.open("Temp.dat",ios::binary);
    inFile.seekg(0,ios::beg);
    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
    {
        if(ac.retaccount_number()!=n)
        {
            outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
        }
    }
    inFile.close();
    outFile.close();
    remove("account.dat");
    rename("Temp.dat","account.dat");
    cout<<"\n\n\tУспешно удалено!.";
}

//***************************************************************
//        function to display all accounts deposit list
//****************************************************************

void display_all()
{
    account ac;
    ifstream inFile;
    inFile.open("account.dat",ios::binary);
    if(!inFile)
    {
        cout<<"Файл не может быть открыт! Нажмите любую кнопку...";
        return;
    }
    cout<<"\n\n\t\tСписок аккаунтов\n\n";
    cout<<"====================================================\n";
    cout<<"№      Имя             Баланс\n";
    cout<<"====================================================\n";
    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
    {
        ac.report();
    }
    inFile.close();
}

//***************************************************************
//        function to deposit and withdraw amounts
//****************************************************************

void deposit_withdraw(int n, int option)
{
    int amt;
    bool found=false;
    account ac;
    fstream File;
    File.open("account.dat", ios::binary|ios::in|ios::out);
    if(!File)
    {
        cout<<"Файл не существует!!";
        return;
    }
    while(!File.eof() && found==false)
    {
        File.read(reinterpret_cast<char *> (&ac), sizeof(account));
        if(ac.retaccount_number()==n)
        {
            ac.show_account();
            if(option==1)
            {
                cout<<"\n\n\tПополнить счет ";
                cout<<"\n\nВводите сумму:";
                cin>>amt;
                ac.dep(amt);
            }
            if(option==2)
            {
                cout<<"\n\n\tСнять сумму";
                cout<<"\n\nВводите сумму";
                cin>>amt;
                int bal=ac.retdeposit()-amt;
                if((bal<500 ) || (bal<1000))
                    cout<<"Недостаток баланса";
                else
                    ac.draw(amt);
            }
            int pos=(-1)*static_cast<int>(sizeof(ac));
            File.seekp(pos,ios::cur);
            File.write(reinterpret_cast<char *> (&ac), sizeof(account));
            cout<<"\n\n\t Запись обновлена";
            found=true;
        }
    }
    File.close();
    if(found==false)
        cout<<"\n\n Запись не существует";
}


