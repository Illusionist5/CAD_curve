#include "Curve.h"


using namespace std;


// ------------------------------------------------------
// Круг
Circle::Circle(Point center, double radius)
{
	r = radius;
	c = center;
}

Point Circle::curve_point(double t) const
{
	double x = c.x + r * cos(t);
	double y = c.y + r * sin(t);
	double z = c.z;
	return Point{x, y, z};
}
 
Vector Circle::curve_vector(double t) const
{
	// просто берем производные от уравнения точки ¯\_(ツ)_/¯
	double x = -1 * r * sin(t);
	double y = r * cos(t);
	double z = 0;
	return Vector{ x, y, z };
}

double Circle::find_radius()
{
	return r;
}




// ------------------------------------------------------
// Эллипс
Ellips::Ellips(Point center, double radius_x, double radius_y)
{
	c = center;
	r_x = radius_x;
	r_y = radius_y;
}

Point Ellips::curve_point(double t) const
{
	double x = c.x + r_x * cos(t);
	double y = c.y + r_y * sin(t);
	double z = c.z;
	return Point{ x, y, z };
}

Vector Ellips::curve_vector(double t) const
{
	double x = -1 * r_x * sin(t);
	double y = r_y * cos(t);
	double z = 0;
	return Vector{ x, y, z };
}



// -----------------------------------------------------
// Спираль
Spiral::Spiral(Point center, double radius, double st)
{
	c = center;
	r = radius;
	step = st;
}


Point Spiral::curve_point(double t) const
{
	double x = c.x + r * t * cos(t);
	double y = c.y + r * t * sin(t);
	double z = c.z + step * t;
	return Point{ x, y, z };
}

Vector Spiral::curve_vector(double t) const
{
	double x = r * cos(t) - r * t * sin(t);
	double y = r * sin(t) + r * t * cos(t);
	double z = step;
	return Vector{ x, y, z };
}


// -----------------------------------------------------
// Генератор
void Curve_generator::set_diapason(double min, double max)
{
	if ((abs(max) + abs(min)) < 2 * eps)  // если значения диапазона одновременно слишко близки к нулю,
		return; 
	rand_num = decltype(rand_num){ min, max }; // меняем параметры
}

PCurve Curve_generator::circle()
{
	double radius = 0;
	while (radius < eps)    // проверяем, что бы радиус был не слишком маленьким
		radius = abs(rand_num(rd));

	return make_shared<Circle>(Point{ rand_num(rd), rand_num(rd) }, radius);
}

PCurve Curve_generator::ellips()
{
	double radius_x = 0;
	while (radius_x < eps)  // проверяем, что бы первый радиус был не слишком маленьким
		radius_x = abs(rand_num(rd));

	double radius_y = 0;
	while (radius_y < eps)  // проверяем, что бы второй радиус был не слишком маленьким
		radius_y = abs(rand_num(rd));

	return make_shared<Ellips>(Point{ rand_num(rd), rand_num(rd) }, radius_x, radius_y);
}

PCurve Curve_generator::spiral()
{
	double radius = 0;
	while (radius < eps)    // проверяем, что бы радиус был не слишком маленьким
		radius = abs(rand_num(rd));

	double step = 0;
	while (abs(step) < eps)    // проверяем, что бы шаг был не слишком маленьким
		step = rand_num(rd);

	return make_shared<Spiral>(Point{ rand_num(rd), rand_num(rd), rand_num(rd) }, radius, step);
}

PCurve Curve_generator::random_curve()
{
	switch (rand_t(rd))
	{
	case circle_t:
		return circle();
	case ellipse_t:
		return ellips();
	case helix_t:
		return spiral();
	default:
		return circle(); // на всякий случай
	}
}
