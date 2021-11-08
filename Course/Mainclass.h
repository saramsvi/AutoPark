#ifndef Mainclass_h
#define Mainclass_h
#pragma once
#include "Header.h"
#include "Car.h"
//Основной класс,который реализует вывод менью и обработку каждого пункта
class MainClass
{
private:
    vector<Car> cars;
public:
    MainClass();
    ~MainClass();
    void readData();        //метод чтения из файла данных
    void writeData();        //метод записи в файл
    void getStarted();        //вывод пунктов меню
    void addData();            //Добавление машины
    void editData();        //редактирование
    void delData();            //удаление
    void showData();        //вывод таблицы , который содержить машины
    void searchCar();        //поиск машины
    void showSearchData(string, string, vector<int>&);        //просмотр найденных результатов
    void toBookATicket();        //выбор бронированиемого машины
    void booking(int);            //бронирование машины
    static bool searchInVector(vector<int>, int); //поиск наличия элемента в векторе
    static int cinInt();        // корректный ввод интового числа (cовместно используется обьектами класса)
    static double cinDouble();    // корректный ввод времени
};

#endif /* Mainclass_h */
