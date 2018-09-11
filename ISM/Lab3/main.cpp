#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <algorithm>
#include <array>
#include <random>
#include <ctime>

using namespace std;

const int n = 1000;

template <class T = unsigned long>
T C(unsigned long n, unsigned long k) {
    unsigned long i;
    T b;
    if (0 == k || n == k) {
        return 1;
    }
    if (k > n) {
        return 0;
    }
    if (k > (n - k)) {
        k = n - k;
    }
    if (1 == k) {
        return n;
    }
    b = 1;
    for (i = 1; i <= k; ++i) {
        b *= (n - (k - i));
        if (b < 0) return -1;
        b /= i;
    }
    return b;
}

long long factorial(long long n) {
    return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

int sgn(int x) {
    return x == 0 ? 0 : x > 0 ? 1 : -1;
}

template <size_t N>
double expectedValue(array<double, N> a) {
    return accumulate(a.begin(), a.end(), 0.0, plus<>()) / N ;
}

template <size_t N>
double variance(array<double, N> a) {
    double middle = expectedValue(a);
    return accumulate(a.begin(), a.end(), 0.0, [&middle](double accumulator, double e) {
        return accumulator + (e - middle) * (e - middle);
    }) / N;
}

template <size_t N>
double pearson_normal(array<double, N> a, double m, int s_2) {
    double s = 0;
    for(int i = -13; i <= 23; i += 1) {
        int j = i + 1;
        double v = (
                erf((j - m) / (sqrt(2 * s_2))) -
                erf((i - m) / (sqrt(2 * s_2)))
                ) / 2;
        double n = double(count_if(a.begin(), a.end(), [&i](double j) {return i < j && j <= (i + 1);})) / N;
        s += pow(n - v, 2) / v;
    }
    return s * N;
}

template <size_t N>
double ks_normal(array<double, N> a, double m, int s_2) {
    double max = 0;
    for(int i = -13; i <= 23; i += 1) {
        int j = i + 1;
        double v = (
                           erf((j - m) / (sqrt(2 * s_2))) -
                           erf((i - m) / (sqrt(2 * s_2)))
                   ) / 2;
        double n = double(count_if(a.begin(), a.end(), [&i](double j) {return i < j && j <= (i + 1);})) / N;
        double b = abs(n - v);
        if(max < b) max = b;
    }
    return max;
}

template <size_t N>
double pearson_uniform(array<double, N> a) {
    double s = 0;
    for(int i = 0; i < 10; i += 1) {
        double v = 1 / 10.0;
        double n = double(count_if(a.begin(), a.end(), [&i](double j) { return i < j && j <= (i + 1); })) / N;
        s += pow(n - v, 2) / v;
    }
    return s * N;
}

template <size_t N>
double ks_uniform(array<double, N> a) {
    double max = 0;
    for(int i = 0; i < 10; i += 1) {
        double v = 1 / 10.0;
        double n = double(count_if(a.begin(), a.end(), [&i](double j) { return i < j && j <= (i + 1); })) / N;
        double b = abs(n - v);
        if(max < b) max = b;
    }
    return max;
}

template <size_t N>
double pearson_exponential(array<double, N> a, double λ) {
    double s = 0;
    double sr = 1 - exp(-37 * λ);
    for(int i = 0; i < 37; i += 1) {
        int j = i + 1;
        double v = (
                (1 - exp(-j * λ)) -
                (1 - exp(-i * λ))
        ) / (sr);
        double n = double(count_if(a.begin(), a.end(), [&i](double j) { return i < j && j <= (i + 1); })) / N;
        s += pow(n - v, 2) / v;
    }
    return s * N;
}

template <size_t N>
double ks_exponential(array<double, N> a, double λ) {
    double max = 0;
    double sr = 1 - exp(-37 * λ);
    for(int i = 0; i < 37; i += 1) {
        int j = i + 1;
        double v = (
                           (1 - exp(-j * λ)) -
                           (1 - exp(-i * λ))
                   ) / (sr);
        double n = double(count_if(a.begin(), a.end(), [&i](double j) { return i < j && j <= (i + 1); })) / N;
        double b = abs(n - v);
        if(max < b) max = b;
    }
    return max;
}

template <size_t N>
double pearson_laplace(array<double, N> a, double λ) {
    double s = 0;
    double sr = 1 - exp(-9 * λ);
    for(int i = -9; i < 9; i += 1) {
        int j = i + 1;
        double v = (λ) * (
                (exp(-λ * j) * (pow(exp(λ * j) - 1, 2) * (-sgn(j)) + 2 * exp(λ * j) + exp(2 * λ * j) - 1)) / (2 * λ) -
                (exp(-λ * i) * (pow(exp(λ * i) - 1, 2) * (-sgn(i)) + 2 * exp(λ * i) + exp(2 * λ * i) - 1)) / (2 * λ)
                ) / (sr * 2);
        double n = double(count_if(a.begin(), a.end(), [&i](double j) { return i < j && j <= (i + 1); })) / N;
        s += pow(n - v, 2) / v;
    }
    return s * N;
}

template <size_t N>
double ks_laplace(array<double, N> a, double λ) {
    double max = 0;
    double sr = 1 - exp(-9 * λ);
    for(int i = -9; i < 9; i += 1) {
        int j = i + 1;
        double v = (λ) * (
                (exp(-λ * j) * (pow(exp(λ * j) - 1, 2) * (-sgn(j)) + 2 * exp(λ * j) + exp(2 * λ * j) - 1)) / (2 * λ) -
                (exp(-λ * i) * (pow(exp(λ * i) - 1, 2) * (-sgn(i)) + 2 * exp(λ * i) + exp(2 * λ * i) - 1)) / (2 * λ)
        ) / (sr * 2);
        double n = double(count_if(a.begin(), a.end(), [&i](double j) { return i < j && j <= (i + 1); })) / N;
        double b = abs(n - v);
        if(max < b) max = b;
    }
    return max;
}

template <size_t N>
double pearson_cauchy(array<double, N> a, double x0, double γ) {
    double h = (*max_element(a.begin(), a.end()) - *min_element(a.begin(), a.end())) / 10;
    double i = *min_element(a.begin(), a.end());
    double s = 0;
    for(int t = 0; t < 10; t += 1) {
        double j = i + h;
        double v = (
                atan((j - x0) / γ) -
                atan((i - x0) / γ)
                ) / M_PI;
        double n = double(count_if(a.begin(), a.end(), [&i, &h](double j) { return i <= j && j < (i + h); })) / N;
        s += pow(n - v, 2) / v;
        i += h;
    }
    return s * N;
}

template <size_t N>
double ks_cauchy(array<double, N> a, double x0, double γ) {
    double h = (*max_element(a.begin(), a.end()) - *min_element(a.begin(), a.end())) / 10;
    double i = *min_element(a.begin(), a.end());
    double max = 0;
    for(int t = 0; t < 10; t += 1) {
        double j = i + h;
        double v = (
                           atan((j - x0) / γ) -
                           atan((i - x0) / γ)
                   ) / M_PI;
        double n = double(count_if(a.begin(), a.end(), [&i, &h](double j) { return i <= j && j < (i + h); })) / N;
        double b = abs(n - v);
        if(max < b) max = b;
        i += h;
    }
    return max;
}

template <size_t N>
double pearson_logistic(array<double, N> a, double μ, double k) {
    double s = 0;
    for(int i = -53; i < 57; i += 1) {
        int j = i + 1;
        double v = (
               pow(1 + exp(-(j - μ) / k), -1) -
               pow(1 + exp(-(i - μ) / k), -1)
        );
        double n = double(count_if(a.begin(), a.end(), [&i](double j) { return i < j && j <= (i + 1); })) / N;
        s += pow(n - v, 2) / v;
    }
    return s * N;
}

template <size_t N>
double ks_logistic(array<double, N> a, double μ, double k) {
    double max = 0;
    for(int i = -53; i < 57; i += 1) {
        int j = i + 1;
        double v = (
                pow(1 + exp(-(j - μ) / k), -1) -
                pow(1 + exp(-(i - μ) / k), -1)
        );
        double n = double(count_if(a.begin(), a.end(), [&i](double j) { return i < j && j <= (i + 1); })) / N;
        double b = abs(n - v);
        if(max < b) max = b;
    }
    return max;
}

int main() {
    double λ;
    mt19937 gen;
    uniform_real_distribution<> urd(0, 1);
    gen.seed(time(0));

    // Normal
    int m = 5, s_2 = 9;
    array<double, n> no;
    for(int i = 0; i < n; i += 1) {
        double x = 0;
        for(int j = 0; j < 12; j += 1){
            x += urd(gen);
        }
        no[i] = m + sqrt(s_2) * (x - 6);
    }
    cout << "Normal" << endl;
    cout << "Expected value: " << expectedValue(no) << endl;
    cout << "True expected value: "<< m << endl;
    cout << "Variance: " << variance(no) << endl;
    cout << "True variance: "<< s_2 << endl;
    cout << "Pearson: " << pearson_normal(no, m, s_2) << endl;
    cout << "Pearson critical: "<< 50.99846016571065 << endl;
    cout << "KS test: " << ks_normal(no, m, s_2) << endl;
    cout << "KS critical: "<< 0.04294689290274677 << endl;

    // Uniform 0 10
    double d1 = 0.0, d2 = 10.0;
    array<double, n> un;
    for(int i = 0; i < n; i += 1) {
        un[i] = urd(gen) * (d2 - d1) + d1;
    }
    cout << "\nUniform 0 10" << endl;
    cout << "Expected value: " << expectedValue(un) << endl;
    cout << "True expected value: "<< (d1 + d2) / 2 << endl;
    cout << "Variance: " << variance(un) << endl;
    cout << "True variance: "<< (d1 - d2) * (d1 - d2) / 12 << endl;
    cout << "Pearson: " << pearson_uniform(un) << endl;
    cout << "Pearson critical: "<< 16.918977604620448 << endl;
    cout << "KS test: " << ks_uniform(un) << endl;
    cout << "KS critical: "<< 0.04294689290274677 << endl;

    // Exponential
    λ = 0.5;
    array<double, n> ex;
    for(int i = 0; i < n; i += 1) {
        ex[i] = -log(urd(gen)) / λ;
    }
    cout << "\nExponential" << endl;
    cout << "Expected value: " << expectedValue(ex) << endl;
    cout << "True expected value: "<< 1 / λ << endl;
    cout << "Variance: " << variance(ex) << endl;
    cout << "True variance: "<< 1 / λ / λ << endl;
    cout << "Pearson: " << pearson_exponential(ex, λ) << endl;
    cout << "Pearson critical: "<< 50.99846016571065 << endl;
    cout << "KS test: " << ks_exponential(ex, λ) << endl;
    cout << "KS critical: "<< 0.04294689290274677 << endl;

    // Laplace
    λ = 2;
    array<double, n> la;
    for(int i = 0; i < n; i += 1) {
        double y = urd(gen);
        la[i] = y < 0.5 ? log(2 * y) / λ : - log(2 * (1 - y)) / λ;
    }
    cout << "\nLaplace" << endl;
    cout << "Expected value: " << expectedValue(la) << endl;
    cout << "True expected value: "<< 0 << endl;
    cout << "Variance: " << variance(la) << endl;
    cout << "True variance: "<< 2 / λ / λ << endl;
    cout << "Pearson: " << pearson_laplace(la, λ) << endl;
    cout << "Pearson critical: "<< 28.869299430392623 << endl;
    cout << "KS test: " << ks_laplace(la, λ) << endl;
    cout << "KS critical: "<< 0.04294689290274677 << endl;

    // Cauchy
    double x0 = 2.0, γ = 3.0;
    array<double, n> ca;
    for(int i = 0; i < n; i += 1) {
        ca[i] = x0 + γ * tan(M_PI * (urd(gen) - 0.5));
    }
    cout << "\nCauchy" << endl;
    cout << "Expected value: don't exist" << endl;
    cout << "Variance: " << variance(ca) << endl;
    cout << "True variance: infinity "<< endl;
    cout << "Pearson: " << pearson_cauchy(ca, x0, γ) << endl;
    cout << "Pearson critical: "<< 16.918977604620448 << endl;
    cout << "KS test: " << ks_cauchy(ca, x0, γ) << endl;
    cout << "KS critical: "<< 0.04294689290274677 << endl;

    // Logistic
    double μ = 2.0, k = 3.0;
    array<double, n> lo;
    for(int i = 0; i < n; i += 1) {
        double y = urd(gen);
        lo[i] = μ + k * log(y /  (1 - y));
    }
    cout << "\nLogistic" << endl;
    cout << "Expected value: " << expectedValue(lo) << endl;
    cout << "True expected value: "<< μ << endl;
    cout << "Variance: " << variance(lo) << endl;
    cout << "True variance: "<< pow(M_PI * k, 2) / 3 << endl;
    cout << "Pearson: " << pearson_logistic(lo, μ, k) << endl;
    cout << "Pearson critical: "<< 135.48017792835952 << endl;
    cout << "KS test: " << ks_logistic(lo, μ, k) << endl;
    cout << "KS critical: "<< 0.04294689290274677 << endl;
    return 0;
}