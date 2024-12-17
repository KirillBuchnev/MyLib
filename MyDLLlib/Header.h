#pragma once
#include <vector>
#include "vector.h"

namespace VectorMath {

    // ����� ��� ������ � ������������� ���������
    class DynamicVector {
    private:
        Vector* vector; // ��������� �� ���������� ������

    public:
        // ����������� �� ������ ��������
        explicit DynamicVector(const std::vector<double>& values);

        // ����������
        ~DynamicVector();

        // ����� �������
        void printVector() const;

        // �������� � ������ ��������
        DynamicVector* add(const DynamicVector* other) const;

        // ��������� ������
        std::vector<double> getData() const;
    };

} // namespace VectorMath