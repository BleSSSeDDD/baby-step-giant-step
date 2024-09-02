#include "BigInt.h"
#include <locale.h>
#include <iostream>
#include <string.h>

BigInt powMod(BigInt base, BigInt exponent, BigInt modulus) {
    BigInt result("1");
    base = base % modulus;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        exponent = exponent / 2;
        base = (base * base) % modulus;
    }
    return result;
}

BigInt gelfondShanks(BigInt g, BigInt a, BigInt p) {

    const long long size = 10000;
    BigInt m = sqrt(p);
    if (m > size) {
        m = size;
    }

    BigInt babyStep[size];

    BigInt giantStep;

    for (BigInt j = 0; j < m; j++) {
        babyStep[toLongLong(j)] = (a * powMod(g, j, p)) % p;
    }

    for (BigInt i = 0; i < m; i++) {
        giantStep = powMod(g, m * i, p);
        for (BigInt j = 0; j < m; j++) {
            if (babyStep[toLongLong(j)] == giantStep) {
                BigInt res = m * i - j;
                while (res < 0) {
                    res = res + p - 1;
                }
                return res;
            }
        }
    }

    return -1;
}

void Solve() {
    std::string str1, str2, str3;
    std::cout << "Input 3 numbers: " << std::endl;
    std::cin >> str1 >> str2 >> str3;

    BigInt alpha = str1;
    BigInt beta = str2;
    BigInt p = str3;

    BigInt ret = gelfondShanks(alpha, beta, p);

    if (ret == -1) {
        std::cout << "There is no solution" << std::endl;
        return;
    }

    std::cout << "The discrete logarithm is: " << ret << std::endl;
    return;
}

int main() {

    Solve();

    return 0;
}
