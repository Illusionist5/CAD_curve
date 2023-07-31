#pragma once
#include <memory>
#include <random>
#include <cmath>
#include <iostream>

using namespace std;

// ��������� ���������
const double eps = 1e-7;	// �����������


// ��������� ��� ���������� �����
struct Point {
	double x, y, z;

	Point() = default;
};

// ��������� ��� ����������� �������
struct Vector {
	double x, y, z;

	Vector() = default;
};


/*
// ����� �������� � �����
ostream& operator<<(ostream& os, const Point& p)
{   // ������� ����� � �����
	return os << "Point x= " << p.x << ", y= " << p.y << ", z= " << p.z << endl;
}
ostream& operator<<(ostream& os, const Vector& p)
{   // ������� ����� � �����
	return os << "Vector x= " << p.x << ", y= " << p.y << ", z= " << p.z << endl;
}*/

// ������� �����
class Curve
{
public:
	Curve() = default;
	virtual ~Curve() {};

	virtual Point curve_point(double t) const = 0;
	virtual Vector curve_vector(double t) const = 0;
};


// ����� �����
class Circle : public Curve
{
	double r;	// ������ ����������
	Point c;	// ����� ����������
public:
	Circle() = default;
	Circle(Point center, double radius);	// ����������� �����
	virtual ~Circle() {};

	virtual Point curve_point(double t) const override;
	virtual Vector curve_vector(double t) const override;

	virtual double find_radius();	// ������ ������ �����
};



// ����� �������
class Ellips : public Curve
{
	double r_x;	// ������ �� x
	double r_y;	// ������ �� y
	Point c;	// ����� �������
public:
	Ellips() = default;
	Ellips(Point center, double radius_x, double radius_y);	// ����������� �������
	virtual ~Ellips() {};

	virtual Point curve_point(double t) const override;
	virtual Vector curve_vector(double t) const override;
};



// ����� �������
class Spiral : public Curve
{
	double r;		// ������ �������
	double step;	// ��� �������
	Point c;		// ����� �������
public:
	Spiral() = default;
	Spiral(Point center, double radius, double st);	// ����������� �������
	virtual ~Spiral() {};

	virtual Point curve_point(double t) const override;
	virtual Vector curve_vector(double t) const override;
};


//-----------------------------------------------------

using PCurve = shared_ptr<Curve>; // ��������� ���� - ����� ��������� �� ������� �����

class Curve_generator   // ��������� �������� - �������� Shape3D
{
    enum curve_type { circle_t, ellipse_t, helix_t };   // ���� ������������ ��������

    static random_device rd;

    uniform_real_distribution<double> rand_num{ -1, 1 };    // ��������� ��������� ������������ �����
    uniform_int_distribution<> rand_t{ circle_t, helix_t };   // ��������� ��������� ����� ��������

public:

    void set_diapason(double min, double max);   // ��������� ��������� ���������� ��������� �����

    PCurve circle();		// ���������� ���� � ���������� �� ���� ����� ���������

    PCurve ellips();		// ���������� ������ � ���������� �� ���� ����� ���������

    PCurve spiral();		// ���������� ������ � ���������� �� ���� ����� ���������

	PCurve random_curve();	// ����� ��������� ������
    
};