#include <vector>
#include <random>     
#include <algorithm> 
#include <iterator>   
#include <iostream>   
#include <functional>
#include <cmath>
#include <numeric>
#include <map>


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

bool condition(int lower, int higher, int number) {
    return number > lower and number < higher;
}

bool bitTest(std::vector<short> c) {
    int ones = 0;
    for (auto i : c) {
        if (i == 1) ones++;
    }
    return condition(9725, 19275, ones);
}

bool seriesTest(std::vector<short> c, int which) {
    std::map<int, int> map = { {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0} };
    int lastDigit = c[0];
    int count = 0;
    for (auto i : c) {
        if (i == which) {
            count++;
            lastDigit = i;
        }
        else {
            if (lastDigit == which) {
                if (count >= 6) {
                    map[6]++;
                }
                else {
                    map[count]++;
                }
            }
            lastDigit = i;
            count = 0;
        }
    }
    return condition(2315, 2685, map[1]) and
        condition(1114, 1386, map[2]) and
        condition(527, 723, map[3]) and
        condition(240, 384, map[4]) and
        condition(103, 209, map[5]) and
        condition(103, 209, map[6]);
}

bool lengthTest(std::vector<short> c) {
    short lastDigit = c[0];
    int count = 0;
    for (auto i : c) {
        if (i == lastDigit) {
            count++;
            if (count >= 26) {
                return false;
            }
        }
        else {
            lastDigit = i;
            count = 0;
        }
    }
    return true;
}

bool pokerTest(std::vector<short> c) {
    std::map<int, int> map;
    for (int i = 0; i < 16; i++) map[i] = 0;
    for (auto iter = c.begin(); iter != c.end(); iter += 4) {
        int number =  (* iter << 3) +  ( * (iter + 1) << 2) + ( * (iter + 2) << 1) + *(iter+3);
        map[number]++;
    }
    double sum = 0;
    for (auto i : map) {
        sum += pow(i.second, 2);
    }
    sum = sum * 16 / 5000;
    sum -= 5000;
    return sum < 46.17 and sum > 2.16;
}

int main()
{
    long long p = 9227, q = 9257;
    
    auto result = generator(p, q);
    std::cout << bitTest(result) << std::endl;
    std::cout << seriesTest(result, 1) << std::endl;
    std::cout << lengthTest(result) << std::endl;
    std::cout << pokerTest(result) << std::endl;
    return 0;
}
