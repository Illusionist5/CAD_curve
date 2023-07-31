#pragma once
#include <memory>
#include <random>
#include <cmath>
#include <iostream>

using namespace std;

// некоторые константы
const double eps = 1e-7;	// погрешность


// структура для трехмерной точки
struct Point {
	double x, y, z;

	Point() = default;
};

// структура для трехмерного вектора
struct Vector {
	double x, y, z;

	Vector() = default;
};


/*
// вывод структур в поток
ostream& operator<<(ostream& os, const Point& p)
{   // выводим точку в поток
	return os << "Point x= " << p.x << ", y= " << p.y << ", z= " << p.z << endl;
}
ostream& operator<<(ostream& os, const Vector& p)
{   // выводим точку в поток
	return os << "Vector x= " << p.x << ", y= " << p.y << ", z= " << p.z << endl;
}*/

// базовый класс
class Curve
{
public:
	Curve() = default;
	virtual ~Curve() {};

	virtual Point curve_point(double t) const = 0;
	virtual Vector curve_vector(double t) const = 0;
};


// класс круга
class Circle : public Curve
{
	double r;	// радиус окружности
	Point c;	// центр окружности
public:
	Circle() = default;
	Circle(Point center, double radius);	// конструктор круга
	virtual ~Circle() {};

	virtual Point curve_point(double t) const override;
	virtual Vector curve_vector(double t) const override;

	virtual double find_radius();	// узнаем радиус круга
};



// класс эллипса
class Ellips : public Curve
{
	double r_x;	// радиус по x
	double r_y;	// радиус по y
	Point c;	// центр эллипса
public:
	Ellips() = default;
	Ellips(Point center, double radius_x, double radius_y);	// конструктор эллипса
	virtual ~Ellips() {};

	virtual Point curve_point(double t) const override;
	virtual Vector curve_vector(double t) const override;
};



// класс спирали
class Spiral : public Curve
{
	double r;		// радиус спирали
	double step;	// шаг спирали
	Point c;		// центр спирали
public:
	Spiral() = default;
	Spiral(Point center, double radius, double st);	// конструктор спирали
	virtual ~Spiral() {};

	virtual Point curve_point(double t) const override;
	virtual Vector curve_vector(double t) const override;
};


//-----------------------------------------------------

using PCurve = shared_ptr<Curve>; // псевдоним типа - умный указатель на базовый класс

class Curve_generator   // генератор объектов - потомков Shape3D
{
    enum curve_type { circle_t, ellipse_t, helix_t };   // типы генерируемых объектов

    static random_device rd;

    uniform_real_distribution<double> rand_num{ -1, 1 };    // генератор случайных вещественных чисел
    uniform_int_distribution<> rand_t{ circle_t, helix_t };   // генератор случайных типов объектов

public:

    void set_diapason(double min, double max);   // изменение диапозона генератора случайных чисел

    PCurve circle();		// генерируем круг и возвращаем на него умный указатель

    PCurve ellips();		// генерируем эллипс и возвращаем на него умный указатель

    PCurve spiral();		// генерируем эллипс и возвращаем на него умный указатель

	PCurve random_curve();	// выбор случайной кривой
    
};