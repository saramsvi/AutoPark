#include "Mainclass.h"
#include <fstream>

MainClass::MainClass()
{
}
MainClass::~MainClass()
{
}
void MainClass::getStarted()
{
    int answer;
    while(true)
    {
        cout << "Меню для работы с автомобилями:\n";
        cout << "\t1) Добавить\n\t2)Редактировать\n\t3) Удалить\n\t4) Просмотр\n"
        << "\t5) Поиск\n\t6) Забронировать\n\t0) Выход\n";
        answer = MainClass::cinInt();
        switch (answer)
        {
            case 0: writeData(); return;
            case 1: addData(); break;
            case 2: editData(); break;
            case 3: delData(); break;
            case 4: showData(); break;
            case 5: searchCar(); break;
            case 6: showData();toBookATicket(); break;
            default: cerr << "некорректные данные!\n";// default-присвоить реализацию по умолчанию. automatically assigned by the compiler
        }
    }
}
fstream file;
void MainClass::writeData()
{
   //открытие файла
 file.open("Car",ios::out|ios::in|ios::app);
        for (unsigned i = 0; i < cars.size(); i++)
        {
             file.seekg(0);
            //запись в файл каждого свойства i-той записи
            file << cars[i].getCarName() << " " << cars[i].getCarModel() << " " << cars[i].getMaxSpeed()
            << " " << cars[i].getMileage() << " " << cars[i].getNumberOfGears() << " " << cars[i].getSpaciousness();
            file.close();
            if (i != cars.size() - 1) file << "\n";
        }
}
void MainClass::readData()
{
    file.open("Car",ios::out|ios::in|ios::app);
    //временные буферы
    Car tempCar;
    char buffer1[100], buffer2[100];
    double buffer3, buffer4;
    int buffer5, buffer6;
    file.seekg(0);// moves the get pointer to the desired location i.e. for read operation.When we try reading a text file, the pointer is set to 0.
    //So we read from the 0th pointer all the way to the last pointer.
    
    //cовмещает указатель get для текущего потока
    for(int i = 0;!file.eof(); i++)
    {
        //чтение в буффера каждого свойства i-той записи
        file >> buffer1 >> buffer2 >> buffer3 >> buffer4 >> buffer5 >> buffer6;
        tempCar.setCarName(buffer1);
        tempCar.setCarModel(buffer2);
        tempCar.setMaxSpeed(buffer3);
        tempCar.setMileage(buffer4);
        tempCar.setNumberOfGears(buffer5);
        tempCar.setSpaciousness(buffer6);

        cars.push_back(tempCar);  //вставка прочитонной в вектор машины
   
    }
    file.close();
}

void MainClass::addData()
{
    int answer;
    //ввод временной машины
    Car tempCar;
    cin >> tempCar;
    //вставка временной машины в вектор машин
    cars.push_back(tempCar);
    //возможность отмены добавления машины
    cout << "Добавлена машина №" << cars.size() - 1 << ". Отменить?\n\t1) Да\n\t2) Нет\n"; answer = MainClass::cinInt();
    if(answer == 1) cars.erase(cars.begin() + cars.size()-1);
    else if(answer != 2) cerr << "Некорректный индекс!\n";
}

void MainClass::editData()
{
    showData();
    int answer, field;
    //ввод ид машины ,которую хотим редактировать
    cout << "проверка корректности ответа: ";
    answer = MainClass::cinInt();
    //проверка некорректности ответа
    if (answer >= cars.size() || answer < 0) cerr << "некорректный индекс!\n";
    else
    {
        //выбор поля для редактирования
        cout << "Поле для редактирования:\n\t1)Название.\n\t2)Марка.\n\t3)Максимальная скорость.\n\t4)Пробег.\n\t5)количество передач.\n\t6)количество мест.\n";
        field = MainClass::cinInt();
        switch (field)
        {
            case 1:  cars[answer].editCarName(); break;
            case 2:  cars[answer].editCarModel(); break;
            case 3:  cars[answer].editMaxSpeed(); break;
            case 4:  cars[answer].editMileage(); break;
            case 5:  cars[answer].editNumberOfGears(); break;
            case 6:  cars[answer].editSpaciousness(); break;
            default: cerr << "Некорректный индекс !\n"; return;
        }
        cout << "Изменена " << answer << "-ая машина!\n";
    }
}

void MainClass::delData()
{
    showData();
    int id, answer;
    cout << "Введите ИД удаляемого элемента : ";
    id = MainClass::cinInt();
    if (id >= cars.size() || id < 0) cerr << "Некорректный индекс!\n";
    else
    {
        cout << "Удалена машина № ¹" << cars.size() - 1 << ". Отменить?\n\t1) Да\n\t2) Нет\n";
        answer = MainClass::cinInt();
        if (answer == 2) cars.erase(cars.begin() + id);
        else if (answer != 2) cerr << "Некорретный индекс!\n";
    }
}


void MainClass::showData()
{
    //вывод шапки таблицы
    Car::showHead();
    Car::id = 0;
    readData();
    //циклом поочередно выводим i-ую машину
    for (unsigned i = 0; i < cars.size(); i++)
    {
        cout << cars[i];
        Car::id++;
    }
}

void MainClass::searchCar()
{
    int answer;
    vector<int> ids;
    string dCity, aCity;
    //ввод параметров машины
    cout << "Введите название: "; cin >> dCity;
    cout << "Введите марку: ";    cin >> aCity;
    //вывод найденных результатов
    showSearchData(dCity, aCity, ids);
    //выбор номера бронируемой машины
    cout << "Введите номер бронируемой машины: "; answer = MainClass::cinInt();
    //если индекс не корректен
    if (!MainClass::searchInVector(ids, answer)) cerr << "Некорректный индекс!\n";
    //если нету свободных мест
    else if (cars[answer].getSpaciousness() == 0) cerr << "Нету свободных мест на машину!\n";
    //если все окей бронируем
    else
        booking(answer);
}

bool MainClass::searchInVector(vector<int> vectorNumbers, int number)
{
    //Проходимся по вектору , если нашли сообщение -возвращаем  true
    for (int i = 0; i < vectorNumbers.size(); i++)
    {
        if (vectorNumbers[i] == number) return true;
    }
    //Не нашли - false
    return false;
}
void MainClass::showSearchData(string dCity, string aCity,vector<int>& ids)
{
    Car::showHead();
    Car::id = 0;
    //проходимся циклом по машинам
    for (unsigned i = 0; i < cars.size(); i++)
    {
        //выводим только , те где параметры совпадают с заданными
        if (dCity == cars[i].getCarName() && aCity == cars[i].getCarModel())
        {
            cout << cars[i];
            //добавляем ид в существующие
            ids.push_back(i);
        }
        Car::id++;
    }
}

void MainClass::toBookATicket()
{
    int answer;
    //ввод номера бронируемой машины
    cout << "Введите ИД бронируемой машины: ";
    answer = MainClass::cinInt();
    //если индекс не корректен
    if (answer >= cars.size() || answer < 0) cerr << "некорректный индекс!\n";
//если нету свободных мест
    else if (cars[answer].getSpaciousness() == 0) cerr << "Нету свободных мест!\n";
//если все ок бронируем
    else booking(answer);
}

void MainClass::booking(int answer)
{
    int spaciousness;
    //ввод количества бронируемых билетов
    cout << "Введите количество бронируемых мест: ";
    spaciousness = MainClass::cinInt();
    //Проверка доступности количества
    if (spaciousness > 0 && spaciousness > cars[answer].getSpaciousness()) cerr << "Ошибка: количество не доступно!\n";
    else
    {
        //уменьшение количества мест
        cars[answer].setSpaciousness(cars[answer].getSpaciousness() - spaciousness);
//вывод инфы  о бронирование машины
        cout << "Забронированная машина: \"" << cars[answer].getCarName() << "\" - \""
        << cars[answer].getCarModel() << "\" " <<". (забронировано " << spaciousness << " шт. к оплате: "
        << cars[answer].getMileage()*spaciousness << " $)\n";
    }
}

int MainClass::cinInt()
{
    int answer;
    //цикл пока не введем нужное число
    while (true)
    {
        cin >> answer;
        //при корректном вводе выходим
        if (cin.get() == '\n')
        {
            break;
        } else
        {
            //при не инте в потоке - очистим и игнорируем
            cin.clear();
            cin.ignore(256, '\n');
            cout << "некорректно , введите еще раз: ";
        }
    }
    return answer;
}

double MainClass::cinDouble()
{
    bool isBad = true;
    //цикл пока не введем нужное число
    double answer = 0.0;
    while (isBad)
    {
        cin >> answer;
        //при корректном вводе выходим
        if (cin.get() == '\n') {
            isBad = false;
        }
        else
        {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Некорректно, введите еще раз: ";
        }
    }
    return ((int)(100*answer))*0.01;
}
