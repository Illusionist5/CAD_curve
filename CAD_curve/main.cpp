#include "Curve.h"

using namespace std;

random_device Curve_generator::rd;

int main()
{
    int sz = 10;   // размер первого массива
    const double pi = 3.141592653589793;    // пи

    vector<PCurve> list_curve;  // массив указателей на объекты базового класса

    {
        Curve_generator c_gen;  // генератор
        c_gen.set_diapason(-10, 10);    // инициализируем диапазон
        for (int i = 0; i < sz; i++)
            list_curve.push_back(c_gen.random_curve());   // заполняем массив
    }

    using PCircle = shared_ptr<Circle>;

    vector<PCircle> list_circle;    // массив указателей на круги первого контейнера

    double sum = 0;    // сумма радиусов кругов

    // перебираем первый контейнер
    for (PCurve ps : list_curve)
    {
        const type_info& ti{ typeid(*ps) };    // информация о типе объекта, на который указывает ps из первого контейнера

        // считаем точку и вектор данной кривой
        Point point_pi = ps->curve_point(pi / 4);
        Vector vector_pi = ps->curve_vector(pi / 4);

        cout << ti.name() << endl   // выводим имя типа
            << "Point: x = " << point_pi.x << ", y = " << point_pi.y << ", z = " << point_pi.z << endl         // выводим точку кривой
            << "Vector: x = " << vector_pi.x << ", y = " << vector_pi.y << ", z = " << vector_pi.z << endl;    // выводим вектор кривой


  
        if (ti.hash_code() == typeid(Circle).hash_code()) // если текущий объект - указатель на круг
        {
            list_circle.push_back(dynamic_pointer_cast<Circle>(ps));
            sum += list_circle.back()->find_radius();  // плюсуем радиус
        }
    }

    sort(list_circle.begin(), list_circle.end(), [](const auto& first, const auto& second)  // сортировка
        {
            return first->find_radius() < second->find_radius();
        });

    for (auto& pc : list_circle) // выводим
        cout << pc->find_radius() << endl;
    cout << "sum = " << sum << endl;



    //cout << "Hello, CAD!";
    return 0;
 
}