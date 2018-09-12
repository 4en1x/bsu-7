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
T C(unsigned long k, unsigned long n) {
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
double pearson_bernoulli(array<double, N> a, double p) {
    return (
            pow(double(count_if(a.begin(), a.end(), [](int i) {return i == 1;}))/ N -  p, 2) / p +
            pow(double(count_if(a.begin(), a.end(), [](int i) {return i == 0;})) / N - (1 - p), 2) / (1 - p)
           ) * N;
}

template <size_t N>
double pearson_binomial(array<double, N> a, double p, int m) {
    double s = 0;
    for(int i = 0; i < m; i += 1) {
        double v = C(i, m) * pow(p, i) * pow(1 - p, m - i);
        s += pow(double(count_if(a.begin(), a.end(), [&i](int j) {return j == i;}))/ N -  v, 2) / v;
    }
    return s * N;
}

template <size_t N>
double pearson_geometric(array<double, N> a, double p) {
    double s = 0;
    for(int i = 1; i < 20; i += 1) {
        double v = p * pow(1 - p, i - 1);
        s += pow(double(count_if(a.begin(), a.end(), [&i](int j) {return j == i;}))/ N -  v, 2) / v;
    }
    return s * N;
}

template <size_t N>
double pearson_negative_binomial(array<double, N> a, double p, int r) {
    double s = 0;
    for(int i = 0; i < 100; i += 1) {
        double v = C(i, i + r - 1) * pow(p, r) * pow(1 - p, i);
        s += pow(double(count_if(a.begin(), a.end(), [&i](int j) {return j == i;}))/ N -  v, 2) / v;
    }
    return s * N;
}

template <size_t N>
double pearson_poisson(array<double, N> a, int λ) {
    double s = 0;
    for(int i = 0; i < 15; i += 1) {
        double v = exp(-λ) * pow(λ, i) / factorial(i);
        s += pow(double(count_if(a.begin(), a.end(), [&i](int j) {return j == i;}))/ N -  v, 2) / v;
    }
    return s * N;
}

int main() {
    double p;
    int m, r, λ;
    mt19937 gen;
    uniform_real_distribution<> urd(0, 1);
    gen.seed(time(0));

    // Bernoulli
    p = 0.7;
    array<double, n> be;
    for(int i = 0; i < n; i += 1) {
        double e = urd(gen);
        be[i] = p >= e ? 1 : 0;
    }
    cout << "Bernoulli" << endl;
    cout << "Expected value: " << expectedValue(be) << endl;
    cout << "True expected value: "<< p << endl;
    cout << "Variance: " << variance(be) << endl;
    cout << "True variance: "<< p * (1 - p) << endl;
    cout << "Pearson: " << pearson_bernoulli(be, p) << endl;
    cout << "Pearson critical: "<< 3.841458820694124 << endl;

    // Binomial
    p = 0.6;
    m = 5;
    array<double, n> bi;
    for(int i = 0; i < n; i += 1) {
        int x = 0;
        for(int j = 0; j < m; j += 1) {
            double e = p - urd(gen);
            if(e > 0) x += 1;
        }
        bi[i] = x;
    }
    cout << "\nBinomial" << endl;
    cout << "Expected value: " << expectedValue(bi) << endl;
    cout << "True expected value: "<< m * p << endl;
    cout << "Variance: " << variance(bi) << endl;
    cout << "True variance: "<< m * p * (1 - p) << endl;
    cout << "Pearson: " << pearson_binomial(bi, p, m) << endl;
    cout << "Pearson critical: "<< 11.070497693516351 << endl;

    // Geometric
    p = 0.6;
    array<double, n> ge;
    for(int i = 0; i < n; i += 1) {
        ge[i] = ceil(log2(urd(gen)) * log2(p));
    }
    cout << "\nGeometric" << endl;
    cout << "Expected value: " << expectedValue(ge) << endl;
    cout << "True expected value: "<< 1 / p << endl;
    cout << "Variance: " << variance(ge) << endl;
    cout << "True variance: "<< (1 - p) / (p * p) << endl;
    cout << "Pearson: " << pearson_geometric(ge, p) << endl;
    cout << "Pearson critical: "<< 30.14352720564616 << endl;

    // Negative binomial
    p = 0.25;
    r = 5;
    array<double, n> nbi;
    for(int i = 0; i < n; i += 1) {
        int x = 0, y = 0;
        while(x < r) {
            double e = p - urd(gen);
            e >= 0 ? x += 1 : y += 1;
        }
        nbi[i] = y;
    }
    cout << "\nNegative binomial" << endl;
    cout << "Expected value: " << expectedValue(nbi) << endl;
    cout << "True expected value: "<< r * (1  - p) / p << endl;
    cout << "Variance: " << variance(nbi) << endl;
    cout << "True variance: "<< r * (1 - p) / p / p << endl;
    cout << "Pearson: " << pearson_negative_binomial(nbi, p, r) << endl;
    cout << "Pearson critical: "<< 123.2252214533618 << endl;

    // Poisson
    λ = 2;
    array<double, n> pu;
    for(int i = 0; i < n; i += 1) {
        int x = -1;
        double e = exp(-λ), y = 1.0;
        while(y > e) {
            y *= urd(gen);
            x += 1;
        }
        pu[i] = x;
    }
    cout << "\nPoisson" << endl;
    cout << "Expected value: " << expectedValue(pu) << endl;
    cout << "True expected value: "<< λ << endl;
    cout << "Variance: " << variance(pu) << endl;
    cout << "True variance: "<< λ << endl;
    cout << "Pearson: " << pearson_poisson(pu, λ) << endl;
    cout << "Pearson critical: "<< 23.684791304840576 << endl;
    return 0;
}