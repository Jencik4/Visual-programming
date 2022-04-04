#include <iostream>
#include <string.h>
#include <locale.h>
#include <cstdlib>
#include <math.h>

using namespace std;

#define PI 3.14159265                                  

class Coordinates {
private:

	double longtitude; // Текущее положение по долготе
	double latitude;	// Текущее положение по широте
	double newLongtitude; // Следующее положение по долготе
	double newLatitude; // Следующее положение по широте

	long double allDist; // Общее пройденное расстояние в км
	long double Dist; //  Расстояние пройденное за одну последнию итерацию в км
	long double d; //  Угловое расстояние пройденное за одну последнию итерацию 

public:
	Coordinates(double longt, double latit)
	{
		allDist = 0;
		Dist = 0;
		d = 0;

		if (longt >= 0 && longt <= 180)
		{
			longtitude = longt;
		}
		else 
		{
			cout << "ОШИБКА: Неверно задана долгота" << endl;
			longtitude = -1;
		}

		if (latit >= 0 && latit <= 90)
		{
			latitude = latit;
			
		}
		else 
		{
			cout << "ОШИБКА: Неверно задана широта" << endl;
			latitude = -1;
		}
		newLatitude = latitude;
		newLongtitude = longtitude;
	}

	void move()
	{
		longtitude = newLongtitude;
		latitude = newLatitude;
		newLatitude += 0 + rand() % 10 - 5;
		newLongtitude += 0 + rand() % 10 - 5;
	}

	void setCoordinates(double dolg, double shirot) {
		longtitude = dolg;
		latitude = shirot;
	}

	double getLongtitude() {
		return longtitude;
	}

	double getLatitude() {
		return latitude;
	}

	double getDist() {
		long double Latitud = latitude * PI / 180;
		long double newLatitud = newLatitude * PI / 180;
		long double newLongtitud = newLongtitude * PI / 180;
		long double longtitud = longtitude * PI / 180;

		d = 2 * abs(asin(sqrt(pow(sin((newLatitud - Latitud) / 2), 2) + (cos(Latitud) * cos(newLatitud) * pow(sin(abs(newLongtitud - longtitud) / 2), 2)))));
		Dist = d * 6372.795;
		allDist += Dist;
		return Dist>0.1?Dist:0;
	}

	double getAllDist() {
		return allDist;

	}

	double getNewLongtitude()
	{
		return newLongtitude;
	}

	double getNewLatitude()
	{
		return newLatitude;
	}

	void showStartCoordinates() {
		cout << "\nНачальная долгота: " << getLongtitude() << endl;
		cout << "Начальная широта: " << getLatitude() << endl;
	}

	void showNewCoordinates()
	{
		cout << "\nТекущая долгота: " << getNewLongtitude() << endl;
		cout << "Текущая широта: " << getNewLatitude() << endl;
	}
};

class Human : public Coordinates {
private:
	string Name;
	string Surname;
	string Patronymiс;
	double Weight;
	double Height;
	int Age;

public:
	/// <summary>
	/// Создать экземпляр класса Human.
	/// </summary>
	/// <param name="surname"> Фамилия </param>
	/// <param name="name"> Имя </param>
	/// <param name="patronymiс"> Отчество </param>
	/// <param name="age"> Возраст </param>
	/// <param name="weight"> Вес </param>
	/// <param name="height">Рост</param>
	/// <param name="longt">Положение по долготе</param>
	/// <param name="latit">Положение по широте</param>
	Human(string surname, string name, string patronymiс, int age, double weight, double height, double longt, double latit) : Coordinates(longt, latit) 
	{
		setFullName(name, surname, patronymiс);
		setParameters(age, weight, height);
	}


	string getName()
	{
		return Name;
	}

	string getSurname()
	{
		return Surname;
	}

	string getPatronymic()
	{
		return Patronymiс;
	}

	int getAge()
	{
		return Age;
	}

	double getWeight()
	{
		return Weight;
	}

	double getHeight()
	{
		return Height;
	}

 	void setFullName(string nm, string sn, string pt)
	{
		Name = nm;
		Surname = sn;
		Patronymiс = pt;
	}

	void setParameters(int a, double w, double h) {
		Age = a;
		Weight = w;
		Height = h;
	}

	void showParameters() 
	{
		cout << "\nВозраст: " << getAge() << endl;
		cout << "\nВес: " << getWeight() << endl;
		cout << "Рост: " << getHeight() << endl;
	}

	void showFullName()
	{
		cout << "Пользователь: " << getSurname();
		cout << " " << getName();
		cout << " " << getPatronymic() << endl;
	}
};

int main() {
	setlocale(LC_ALL, "Russian");

	const int lifeTime = 5;
	

	Human* human = new Human("Кулебакин", "Евгений", "Дмитриевич", 20, 60, 178, 55, 82);
	human->showFullName();
	human->showParameters();
	human->showStartCoordinates();

	for (int i = 0; i < lifeTime; i++)
	{
		human->move();
		human->showNewCoordinates();
		cout << "Расстояние пройденное за итерацию: " << human->getDist() << " км" << endl;
	}
	cout << endl << "Время жизни " << human->getName() << " = " << lifeTime << endl;

	cout << "Расстояние пройденное за lifeTime: " << human->getAllDist() << " км" << endl;


}