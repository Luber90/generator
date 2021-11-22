#include <vector>
#include <random>     
#include <algorithm> 
#include <iterator>   
#include <iostream>   
#include <functional>
#include <cmath>
#include <numeric>


long long gcd(long long a, long long b) {
    long long c;
    while (b != 0) {
        c = a % b;
        a = b;
        b = c;
    }
    return a;
}

std::vector<short> generator(long long p, long long q) {
    auto N = p * q;
    std::random_device device;
    std::uniform_int_distribution<long long> dist(1, N - 1);
    auto x = dist(device);
    while (gcd(x, N) != 1)x = dist(device);
    auto result = std::vector<short>{};
    for (int i = 0; i < 20000; i++) {
        auto res = static_cast<long long>(std::pow(x, 2)) % N;
        long long mask = 1;
        result.push_back(res & mask);
        x = res;
    }
    return result;
    
}

int main()
{
    
    long long p = 1511, q = 3559;
    
    auto result = generator(p, q);
    int ones = 0;
    for (auto i : result) {
        if (i == 1) ones++;
    }
    std::cout << ones << std::endl;
    return 0;
}