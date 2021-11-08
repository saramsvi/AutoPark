#ifndef Car_h
#define Car_h
#include "Header.h"
//Класс  который представляет модель машины (сущностный класс)
class Car
{
private:
    //данные о машине :название , марка , максимальная скорость ,стоимость , количество передач , вместительность
    string carName;
    string carModel;
    double maxSpeed;
    double mileage;
    int numberOfGears; 
    int spaciousness;
public:
    //статическая переменная - счетник (для вывода в консоль id )
    //существуют на протяжении функции и не известны за переделамии функций
    static int id;
public:
    //методы получения данных машины
    string getCarName();
    string getCarModel();
    double getMaxSpeed();
    double getMileage();
    int getNumberOfGears();
    int getSpaciousness();
    //методы редактирования ( ввод из консоли свойства машины)
    void editCarName();
    void editCarModel();
    void editMaxSpeed();
    void editMileage();
    void editNumberOfGears();
    void editSpaciousness();
    //программная установка свойств машины
    void setCarName(string);
    void setCarModel(string);
    void setMaxSpeed(double);
    void setMileage(double);
    void setNumberOfGears(int);
    void setSpaciousness(int);
    //метод : программная установка сразу всех свойств машины
    void setAllFields(string, string, double, double, int, int);
    Car(string, string, double, double, int, int);        // конструктор с параметрами
    Car(const Car&);                                    // конструктор копирования
    Car();                                                // конструктор без параметров
    ~Car();
    //функции для перегрузки операторов записи и чтения в/из потока
    friend std::ostream& operator<< (std::ostream&, Car&);
    friend std::istream& operator>> (std::istream&, Car&);
    //перегрузка оператора присваивания
    void operator=(Car);
    //вывод шапки таблицы машин
    static void showHead();
};


#endif /* Car_h */
