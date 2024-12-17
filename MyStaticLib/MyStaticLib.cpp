#include "pch.h"
#include "vector.h"

Vector::Vector(const vector<double>& values) : data(values) {
    if (data.empty()) {
        throw invalid_argument("Vector cannot be empty");
    }
}

double Vector::length() const {
    double sum = 0.0;
    for (const double& value : data) {
        sum += value * value;
    }
    return sqrt(sum);
}


void Vector::normalize() {
    double len = length();
    if (len == 0) {
        throw runtime_error("Cannot normalize a zero-length vector");
    }
    for (double& value : data) {
        value /= len;
    }
}

double Vector::dotProduct(const Vector& other) const {
    if (data.size() != other.data.size()) {
        throw invalid_argument("Vectors must have the same size");
    }

    double result = 0.0;
    for (size_t i = 0; i < data.size(); ++i) {
        result += data[i] * other.data[i];
    }
    return result;
}

const vector<double>& Vector::getData() const {
    return data;
}