#include "Curve.h"

using namespace std;

random_device Curve_generator::rd;

int main()
{
    int sz = 10;   // ������ ������� �������
    const double pi = 3.141592653589793;    // ��

    vector<PCurve> list_curve;  // ������ ���������� �� ������� �������� ������

    {
        Curve_generator c_gen;  // ���������
        c_gen.set_diapason(-10, 10);    // �������������� ��������
        for (int i = 0; i < sz; i++)
            list_curve.push_back(c_gen.random_curve());   // ��������� ������
    }

    using PCircle = shared_ptr<Circle>;

    vector<PCircle> list_circle;    // ������ ���������� �� ����� ������� ����������

    double sum = 0;    // ����� �������� ������

    // ���������� ������ ���������
    for (PCurve ps : list_curve)
    {
        const type_info& ti{ typeid(*ps) };    // ���������� � ���� �������, �� ������� ��������� ps �� ������� ����������

        // ������� ����� � ������ ������ ������
        Point point_pi = ps->curve_point(pi / 4);
        Vector vector_pi = ps->curve_vector(pi / 4);

        cout << ti.name() << endl   // ������� ��� ����
            << "Point: x = " << point_pi.x << ", y = " << point_pi.y << ", z = " << point_pi.z << endl         // ������� ����� ������
            << "Vector: x = " << vector_pi.x << ", y = " << vector_pi.y << ", z = " << vector_pi.z << endl;    // ������� ������ ������


  
        if (ti.hash_code() == typeid(Circle).hash_code()) // ���� ������� ������ - ��������� �� ����
        {
            list_circle.push_back(dynamic_pointer_cast<Circle>(ps));
            sum += list_circle.back()->find_radius();  // ������� ������
        }
    }

    sort(list_circle.begin(), list_circle.end(), [](const auto& first, const auto& second)  // ����������
        {
            return first->find_radius() < second->find_radius();
        });

    for (auto& pc : list_circle) // �������
        cout << pc->find_radius() << endl;
    cout << "sum = " << sum << endl;



    //cout << "Hello, CAD!";
    return 0;
 
}