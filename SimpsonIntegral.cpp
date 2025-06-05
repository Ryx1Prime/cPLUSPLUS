#include <iostream>
#include <cmath>
using namespace std;
class Integral {
private:
    double (*f)(double x);
    double a, b;
    double result;
    double epsilon;
    double adaptive_simpson() {
    double h = (b - a) / 2;  // начальный шаг (соответствует 2 интервалам)
    double sum_nechet = f(a + h);  // средняя точка
    double sum_chet = 0;
    const double ends = f(a) + f(b);
    double integral = (ends + 4 * sum_nechet) * h / 3;
    double prev_integral = 0;
    
    while (abs(integral - prev_integral) > epsilon) {
        prev_integral = integral;
        h /= 2;
        double new_sum_odd = 0;
        for (double x = a + h; x < b; x += 2 * h) {
            new_sum_odd += f(x);
        }
        sum_chet += sum_nechet;   // cтарые нечетные -> четные
        sum_nechet = new_sum_odd; // yовые точки -> нечетные
        integral = (ends + 4 * sum_nechet + 2 * sum_chet) * h / 3;
        // чтобы при слишком большом количестве итераций программа не ломалась
        if (h < (b - a) * 1e-10) {
            cout << "дальше уже нельзя вычислить" << endl;
            break;
        }
    }
    return integral;
}
public:
    Integral(double (*func)(double), double start, double end, double eps): 
        f(func), a(start), b(end), epsilon(eps) {
        result = adaptive_simpson();
    }
    double compute(double new_a, double new_b) {
        a = new_a;
        b = new_b;
        result = adaptive_simpson();
        return result;
    }
    double getResult() const { return result; }
};

// Тест
double square(double x) { return x * x; }
double Sin1(double x) { return sin(x); }

int main() {
    setlocale(LC_ALL, "RU");
    double epsilon;
    cout << "введите эпсилон";
    cin >> epsilon;
    Integral sin_int(Sin1, 0, M_PI, epsilon);
    cout << "∫sin(x)dx от 0 до π = " << sin_int.getResult() 
         << " (ожидается: 2)" << endl;
    sin_int.compute(0, 1);
    cout << "∫sin(x)dx от 0 до 1 = " << sin_int.getResult() 
         << " (ожидается: " << 1-cos(1) << ")" << endl;
    Integral square_int(square, 0, 1, epsilon);
    cout << "∫x²dx от 0 до 1 = " << square_int.getResult() 
         << " (ожидается: " << 1.0/3 << ")" << endl;
}