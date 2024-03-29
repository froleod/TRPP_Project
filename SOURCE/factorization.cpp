#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>
#include <map>

using namespace std;

struct polynomial {                 // Структура данных, нужная для хранения многочленов.
    vector<int> monomials;    // Содержит степень многочлена и список одночленов.
    int degree = (int) (monomials.size()) - 1;
};

struct success_and_result {         // Структура данных, хранящая признак успешности проведения операции
    bool success = false;           // и, если операция проведена успешно, её результат.
    polynomial result;
};

struct constant_and_answer {
    int constant;
    vector<polynomial> answer;
};

int calculate(const polynomial &f, int n) { // Считает значение многочлена в целой точке
    int sum = 0;
    int p = 0;
    for (auto i : f.monomials) {
        sum += i * (int) (pow(n, p++));
    }
    return sum;
}

bool equal(double x, double y) { // Сравнивает два числа с плавающей точкой
    return fabs(x - y) < 1e-9;
}

success_and_result divide(polynomial A, polynomial B) { // Делит многочлен на многочлен
    int n = (int) A.monomials.size() - 1;
    int m = (int) B.monomials.size() - 1;
    polynomial Q{vector<int>(n - m + 1)};
    for (int i = n; i >= m; i--) {
        Q.monomials[i - m] = A.monomials[i] / B.monomials[m];
        for (int j = m; j >= 0; j--)
            A.monomials[i - m + j] -= B.monomials[j] * Q.monomials[i - m];
    }
    while (!A.monomials.empty() && equal(A.monomials.back(), 0))
        A.monomials.pop_back();
    if (A.monomials.empty())
        return success_and_result{true, Q};
    else
        return success_and_result{false};
}

string str_polynomial(pair<vector<int>, int> a, bool brackets) {  // Красиво и понятно выводит на экран многочлен
    int n = a.first.size() - 1;
    stringstream str_ans;

    if (brackets) str_ans << '(';

    if (n > 1) {
        if (a.first[n] == -1)
            str_ans << "-x^" << n;
        else if (a.first[n] == 1)
            str_ans << "x^" << n;
        else
            str_ans << a.first[n] << "x^" << n;
    }

    for (int i = n - 1; i > 1; --i) {
        if (a.first[i] != 0) {
            if (a.first[i] > 0) {
                str_ans << '+';
                (a.first[i] == 1) ? str_ans << "x^" << i : str_ans << a.first[i] << "x^" << i;
            } else
                (a.first[i] == -1) ? str_ans << "-x^" << i : str_ans << a.first[i] << "x^" << i;
        }
    }

    if (a.first[1] != 0) {
        if (a.first[1] > 0) {
            if (n > 1)
                str_ans << '+';
            (a.first[1] == 1) ? str_ans << "x" : str_ans << a.first[1] << "x";
        } else
            (a.first[1] == -1) ? str_ans << "-x" : str_ans << a.first[1] << "x";
    }

    if (a.first[0] != 0) {
        if (a.first[0] > 0) {
            str_ans << '+';
            str_ans << a.first[0];
        } else
            str_ans << a.first[0];
    }

    if (brackets) str_ans << ")";

    if (a.second > 1) str_ans << "^" << a.second;

    return str_ans.str();
}

int main() {
    polynomial p;
    p.monomials = vector<int>{4, 3, 2, 1};
    p.degree = 3;
    cout << str_polynomial(make_pair(p.monomials, 0), false);
}

