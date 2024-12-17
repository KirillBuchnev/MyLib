#pragma once
#include <vector>
#include <cmath>
#include <stdexcept>

using namespace std;

namespace VectorMath {

    // ����� ��� ������ � ��������������� ���������
    class Vector {
    private:
        vector<double> data; // ���������� ������ �������

    public:
        // ����������� �� ������ ��������
        explicit Vector(const vector<double>& values);

        // ���������� ����� �������
        double length() const;

        // ������������ �������
        void normalize();

        // ��������� ������������ � ������ ��������
        double dotProduct(const Vector& other) const;

        // ��������� ���������� ������
        const vector<double>& getData() const;
    };

} // namespace VectorMath