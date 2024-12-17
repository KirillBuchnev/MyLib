#pragma once
#include <iostream>
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
        bool isHappyVector() const;
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