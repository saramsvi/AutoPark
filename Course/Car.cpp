#include "Car.h"
#include <iomanip>
#include "Mainclass.h"

int Car::id = 0;

Car::Car(string carName, string carModel, double maxSpeed, double mileage, int numberOfGears, int spaciousness)
{
    //устанавливаем свойства при помощи метода setAllFields
    setAllFields(carName, carModel, maxSpeed, mileage, numberOfGears, spaciousness);
}

Car::Car(const Car& tempCar)
{
    //реализвация копирования каждого свойства переданнаго обьекта в текущий
    this->carName = tempCar.carName;
    this->carModel = tempCar.carModel;
    this->maxSpeed = tempCar.maxSpeed;
    this->mileage = tempCar.mileage;
    this->numberOfGears = tempCar.numberOfGears;
    this->spaciousness = tempCar.spaciousness;
}

Car::Car()
{
    //пустые значения
    this->carName = "";
    this->carModel = "";
    this->maxSpeed = 0;
    this->mileage = 0;
    this->numberOfGears = 0;
    this->spaciousness = 0;
}

Car::~Car(){}

ostream& operator<< (ostream& cout, Car& car)
{
    //устанавливаем 2 знака после запятой для double
    //makes cout print floats with a fixed number of decimals
    cout.setf(std::ios::fixed);
    //sets the number to  be 2
    cout.precision(2);
    //вывод полей setw - ширина вывода
    cout << setw(5) << left
    << Car::id << setw(25)
    << car.carName << setw(25)
    << car.carModel << setw(15)
    << car.maxSpeed << setw(15)
    << car.mileage << setw(10)
    << car.numberOfGears << setw(10)
    << car.spaciousness << endl;
    return cout;
}

istream& operator>> (istream& cin, Car& car)
{
    //поочередной ввод каждого поля машины
    cout << "\tДобавление машины:\n";
    cout << "Название: ";
    cin >> car.carName;
    cout << "Марка: ";
    cin >> car.carModel;
    cout << "Максимальная скорость: ";
    car.maxSpeed = MainClass::cinDouble();
    cout << "Стоимость: ";
    car.mileage = MainClass::cinDouble();
    cout << " Количество передач: ";
    car.numberOfGears = MainClass::cinInt();
    cout << " Количество мест: ";
    car.spaciousness = MainClass::cinInt();
    return cin;
}

void Car::showHead()
{
    //вывод разделительной линии
    for (int i = 0; i < 120; i++) cout << "=";
    cout << endl;
    //вывод заголовок в шапке
    cout << setw(5) << left << "ИД" << setw(25)
    << "Название" << setw(25)
    << "Марка" << setw(15)
    << "Макс. скорость\t\t\t" << setw(15)
    << "Стоимость\t\t\t" << setw(10)
    << "Передач\t\t" << setw(10)
    << " Количество мест" << endl;
    //вывод разделительной линии
    for (int i = 0; i < 120; i++) cout << "=";
    cout << endl;
}

string Car::getCarName()
{
    return this->carName;
}

string Car::getCarModel()
{
    return this->carModel;
}

double Car::getMaxSpeed()
{
    return this->maxSpeed;
}

double Car::getMileage()
{
    return this->mileage;
}

int Car::getNumberOfGears()
{
    return this->numberOfGears;
}

int Car::getSpaciousness()
{
    return this->spaciousness;
}

void Car::setCarName(string carName)
{
    this->carName = carName;
}

void Car::setCarModel(string carModel)
{
    this->carModel = carModel;
}

void Car::setMaxSpeed(double maxSpeed)
{
    this->maxSpeed = maxSpeed;
}

void Car::setMileage(double mileage)
{
    this->mileage = mileage;
}

void Car::setNumberOfGears(int numberOfGears)
{
    this->numberOfGears = numberOfGears;
}

void Car::setSpaciousness(int spaciousness)
{
    this->spaciousness = spaciousness;
}

void Car::setAllFields(string carName, string carModel, double maxSpeed, double mileage, int numberOfGears, int spaciousness)
{
    //установка свойств текущего обьекта переданными параметрами
    this->carName = carName;
    this->carModel = carModel;
    this->maxSpeed = maxSpeed;
    this->mileage = mileage;
    this->numberOfGears = numberOfGears;
    this->spaciousness = spaciousness;
}

void Car::editCarName()
{
    cout << "Введите название!\n";
    cin >> this->carName;
}

void Car::editCarModel()
{
    cout << "Введите модель!\n";
    cin >> this->carModel;
}

void Car::editMaxSpeed()
{
    cout << "Введите максимальную скорость!\n";
    this->maxSpeed = MainClass::cinDouble();
}

void Car::editMileage()
{
    cout << "Введите пробег!\n";
    this->mileage = MainClass::cinDouble();
}

void Car::editNumberOfGears()
{
    cout << "Введите количество передач!\n";
    this->numberOfGears = MainClass::cinInt();
}

void Car::editSpaciousness()
{
    cout << "Введите количество мест !\n";
    this->spaciousness = MainClass::cinInt();
}

void Car::operator=(Car car)
{
    //перегрезка оператора присваения , реализация копирования каждого свойства переданного обьекта в текущий
    this->carName = car.carName;
    this->carModel = car.carModel;
    this->maxSpeed = car.maxSpeed;
    this->mileage = car.mileage;
    this->numberOfGears = car.numberOfGears;
    this->spaciousness = car.spaciousness;
}
