#include <iostream>
#include <math.h>
#include <time.h>
#include <algorithm>
#include <array>
#include <fstream>
using namespace std;

const int K = 64;
const int β = 50653;
unsigned long long a = 50653;
const unsigned long long M = pow(2, 31);
const int n = 1000;

class IsInRange {
    int index;
public:
    IsInRange(int p) : index(p) {}

    bool operator()(double i) {
        return (i >= index / 10.0 && i < (index + 1.0) / 10.0);
    }
};

int main() {
    array<double, n> d1;
    d1[0] = double(a) / M;
    for(int i = 1; i < n; i += 1) {
        a = (β * a) % M;
        d1[i] = double(a) / M;
    }

    srand(time(NULL));
    array<double, K> V;
    array<double, n> d3;
    a = 50653;
    V[0] = double(a) / M;
    for(int i = 1; i < n; i += 1) {
        a = (β * a) % M;
        V[i] = double(a) / M;
    }
    for(int i = 0; i < n; i += 1) {
        int s = floor(rand()/float(RAND_MAX) * K);
        d3[i] = V[s];
        a = (β * a) % M;
        V[s] = double(a) / M;
    }

    // write arrays to file
    ofstream f ("../numbers.txt");
    for(int i = 0; i < n; i += 1) {
       f << d1[i] << "\n";
    }
    for(int i = 0; i < n; i += 1) {
        f << d3[i] << "\n";
    }
    f.close();

    // Pearson's chi-squared test
    // https://ru.wikipedia.org/wiki/Квантили_распределения_хи-квадрат
    // for pearson test normal result should be less than 16.92
    double pearson1 = 0, pearson3 = 0;
    double middle = double(n) / 10;
    for(int i = 0; i < 10; i +=1 ){
        pearson1 += pow((count_if(d1.begin(), d1.end(), IsInRange(i)) - middle), 2) / middle;
        pearson3 += pow((count_if(d3.begin(), d3.end(), IsInRange(i)) - middle), 2) / middle;
    }
    cout << "Pirson test for D1: " << pearson1 << endl;
    cout << "Pirson test for D3: " << pearson3 << endl;

    // for ks test normal result should be less than 1.36 ???? 0.04294689290274677
    sort(d1.begin(), d1.end());
    sort(d3.begin(), d3.end());
    double max1 = 0, max3 = 0;
    for(int i = 1; i < n; i += 1) {
        double v1 = double(i) / n - d1[i - 1];
        double v3 = double(i) / n - d3[i - 1];
        if(v1 > max1) max1 = v1;
        if(v3 > max3) max3 = v3;

        v1 = d1[i - 1] - ((double(i) - 1) / n);
        v3 = d3[i - 1] - ((double(i) - 1) / n);
        if(v1 > max1) max1 = v1;
        if(v3 > max3) max3 = v3;
    }
    cout << "Kolmogorov-Smirnov test for D1: " << max1 << endl;
    cout << "Kolmogorov-Smirnov test for D3: " << max3 << endl;

    return 0;
}