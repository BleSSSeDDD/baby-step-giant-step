#include <iostream>
#include <string>

class BigInt {

public:
    std::string value;
    char sign;
    BigInt();
    BigInt(const BigInt&);
    BigInt(const long long&);
    BigInt(const std::string&);

    BigInt& operator=(const BigInt&);
    BigInt& operator=(const long long&);

    BigInt operator+() const;
    BigInt operator-() const;

    BigInt operator+(const BigInt&) const;
    BigInt operator-(const BigInt&) const;
    BigInt operator*(const BigInt&) const;
    BigInt operator/(const BigInt&) const;
    BigInt operator%(const BigInt&) const;
    BigInt operator+(const long long&) const;
    BigInt operator-(const long long&) const;
    BigInt operator*(const long long&) const;
    BigInt operator/(const long long&) const;
    BigInt operator%(const long long&) const;
    BigInt& operator++();
    BigInt& operator--();
    BigInt operator++(int);
    BigInt operator--(int);

    bool operator<(const BigInt&) const;
    bool operator>(const BigInt&) const;
    bool operator<=(const BigInt&) const;
    bool operator>=(const BigInt&) const;
    bool operator==(const BigInt&) const;
    bool operator!=(const BigInt&) const;

    bool operator==(const long long&) const;
    bool operator!=(const long long&) const;

    friend std::istream& operator>>(std::istream&, BigInt&);
    friend std::ostream& operator<<(std::ostream&, const BigInt&);

    std::string to_string() const;
};

#include <cstddef>

long long toLongLong(BigInt arg) {
    long long maximum = 9223372036854775807;
    BigInt max = maximum;
    if (arg > max) {
        return -1;
    }
    long long result = 0;
    for (char c : arg.value) {
        if (c >= '0' && c <= '9') {
            result = result * 10 + (c - '0');
        }
        else {

            return 0;
        }
    }
    return result;
}

#include <tuple>
void strip_leading_zeroes(std::string& num) {
    size_t i;
    for (i = 0; i < num.size(); i++)
        if (num[i] != '0')
            break;

    if (i == num.size())
        num = "0";
    else
        num = num.substr(i);
}

void add_leading_zeroes(std::string& num, size_t num_zeroes) {
    num = std::string(num_zeroes, '0') + num;
}

void add_trailing_zeroes(std::string& num, size_t num_zeroes) {
    num += std::string(num_zeroes, '0');
}

std::tuple<std::string, std::string> get_larger_and_smaller(const std::string& num1,
    const std::string& num2) {
    std::string larger, smaller;
    if (num1.size() > num2.size() or
        (num1.size() == num2.size() and num1 > num2)) {
        larger = num1;
        smaller = num2;
    }
    else {
        larger = num2;
        smaller = num1;
    }
    add_leading_zeroes(smaller, larger.size() - smaller.size());

    return std::make_tuple(larger, smaller);
}

bool is_power_of_10(const std::string& num) {
    if (num[0] != '1')
        return false;
    for (size_t i = 1; i < num.size(); i++)
        if (num[i] != '0')
            return false;
    return true;
}

BigInt::BigInt() {
    value = "0";
    sign = '+';
}

BigInt::BigInt(const BigInt& num) {
    value = num.value;
    sign = num.sign;
}

BigInt::BigInt(const long long& num) {
    value = std::to_string(std::abs(num));
    if (num < 0)
        sign = '-';
    else
        sign = '+';
}

BigInt::BigInt(const std::string& num) {
    value = num;
    sign = '+';
}

std::string BigInt::to_string() const {
    return this->sign == '-' ? "-" + this->value : this->value;
}

BigInt& BigInt::operator=(const BigInt& num) {
    value = num.value;
    sign = num.sign;

    return *this;
}

BigInt& BigInt::operator=(const long long& num) {
    BigInt temp(num);
    value = temp.value;
    sign = temp.sign;

    return *this;
}

BigInt BigInt::operator+() const {
    return *this;
}

BigInt BigInt::operator-() const {
    BigInt temp;

    temp.value = value;
    if (value != "0") {
        if (sign == '+')
            temp.sign = '-';
        else
            temp.sign = '+';
    }

    return temp;
}

bool BigInt::operator==(const BigInt& num) const {
    return (sign == num.sign) and (value == num.value);
}

bool BigInt::operator!=(const BigInt& num) const {
    return !(*this == num);
}

bool BigInt::operator<(const BigInt& num) const {
    if (sign == num.sign) {
        if (sign == '+') {
            if (value.length() == num.value.length())
                return value < num.value;
            else
                return value.length() < num.value.length();
        }
        else
            return -(*this) > -num;
    }
    else
        return sign == '-';
}

bool BigInt::operator>(const BigInt& num) const {
    return !((*this < num) or (*this == num));
}

bool BigInt::operator<=(const BigInt& num) const {
    return (*this < num) or (*this == num);
}

bool BigInt::operator>=(const BigInt& num) const {
    return !(*this < num);
}

bool BigInt::operator==(const long long& num) const {
    return *this == BigInt(num);
}

bool operator==(const long long& lhs, const BigInt& rhs) {
    return BigInt(lhs) == rhs;
}

bool BigInt::operator!=(const long long& num) const {
    return !(*this == BigInt(num));
}

bool operator!=(const long long& lhs, const BigInt& rhs) {
    return BigInt(lhs) != rhs;
}

bool operator<(const long long& lhs, const BigInt& rhs) {
    return BigInt(lhs) < rhs;
}

bool operator>(const long long& lhs, const BigInt& rhs) {
    return BigInt(lhs) > rhs;
}

bool operator<=(const long long& lhs, const BigInt& rhs) {
    return BigInt(lhs) <= rhs;
}

bool operator>=(const std::string& lhs, const BigInt& rhs) {
    return BigInt(lhs) >= rhs;
}

#include <string>

BigInt big_pow10(size_t exp) {
    return BigInt("1" + std::string(exp, '0'));
}

BigInt sqrt(const BigInt& num) {
    if (num == 0)
        return 0;
    else if (num < 4)
        return 1;
    else if (num < 9)
        return 2;
    else if (num < 16)
        return 3;

    BigInt sqrt_prev = -1;

    BigInt sqrt_current = big_pow10(num.to_string().size() / 2 - 1);

    while (sqrt_current - sqrt_prev > 1) {
        sqrt_prev = sqrt_current;
        sqrt_current = (num / sqrt_prev + sqrt_prev) / 2;
    }
    return sqrt_current;
}

#include <climits>
#include <cmath>
#include <string>

const long long FLOOR_SQRT_LLONG_MAX = 3037000499;

BigInt BigInt::operator+(const BigInt& num) const {
    if (this->sign == '+' and num.sign == '-') {
        BigInt rhs = num;
        rhs.sign = '+';
        return *this - rhs;
    }
    else if (this->sign == '-' and num.sign == '+') {
        BigInt lhs = *this;
        lhs.sign = '+';
        return -(lhs - num);
    }
    std::string larger, smaller;
    std::tie(larger, smaller) = get_larger_and_smaller(this->value, num.value);
    BigInt result;
    result.value = "";
    short carry = 0, sum;

    for (long i = larger.size() - 1; i >= 0; i--) {
        sum = larger[i] - '0' + smaller[i] - '0' + carry;
        result.value = std::to_string(sum % 10) + result.value;
        carry = sum / (short)10;
    }

    if (carry)
        result.value = std::to_string(carry) + result.value;
    if (this->sign == '-' and result.value != "0")
        result.sign = '-';

    return result;
}

BigInt BigInt::operator-(const BigInt& num) const {
    if (this->sign == '+' and num.sign == '-') {
        BigInt rhs = num;
        rhs.sign = '+';
        return *this + rhs;
    }
    else if (this->sign == '-' and num.sign == '+') {
        BigInt lhs = *this;
        lhs.sign = '+';
        return -(lhs + num);
    }
    BigInt result;
    std::string larger, smaller;
    if (*this > num) {
        larger = this->value;
        smaller = num.value;

        if (this->sign == '-')
            result.sign = '-';
    }
    else {
        larger = num.value;
        smaller = this->value;

        if (num.sign == '+')
            result.sign = '-';
    }
    add_leading_zeroes(smaller, larger.size() - smaller.size());
    result.value = "";
    short difference;
    long i, j;
    for (i = larger.size() - 1; i >= 0; i--) {
        difference = larger[i] - smaller[i];
        if (difference < 0) {
            for (j = i - 1; j >= 0; j--) {
                if (larger[j] != '0') {
                    larger[j]--;
                    break;
                }
            }
            j++;
            while (j != i) {
                larger[j] = '9';
                j++;
            }
            difference += 10;
        }
        result.value = std::to_string(difference) + result.value;
    }
    strip_leading_zeroes(result.value);

    if (result.value == "0")
        result.sign = '+';

    return result;
}

BigInt BigInt::operator*(const BigInt& num) const {
    if (*this == 0 or num == 0)
        return BigInt(0);
    if (*this == 1)
        return num;
    if (num == 1)
        return *this;

    BigInt product;
    if (*this <= FLOOR_SQRT_LLONG_MAX and num <= FLOOR_SQRT_LLONG_MAX)
        product = std::stoll(this->value) * std::stoll(num.value);
    else if (is_power_of_10(this->value)) {
        product.value = num.value;
        product.value.append(this->value.begin() + 1, this->value.end());
    }
    else if (is_power_of_10(num.value)) {
        product.value = this->value;
        product.value.append(num.value.begin() + 1, num.value.end());
    }
    else {
        std::string larger, smaller;
        std::tie(larger, smaller) = get_larger_and_smaller(this->value, num.value);

        size_t half_length = larger.size() / 2;
        auto half_length_ceil = (size_t)ceil(larger.size() / 2.0);

        BigInt num1_high, num1_low;
        num1_high = larger.substr(0, half_length);
        num1_low = larger.substr(half_length);

        BigInt num2_high, num2_low;
        num2_high = smaller.substr(0, half_length);
        num2_low = smaller.substr(half_length);

        strip_leading_zeroes(num1_high.value);
        strip_leading_zeroes(num1_low.value);
        strip_leading_zeroes(num2_high.value);
        strip_leading_zeroes(num2_low.value);

        BigInt prod_high, prod_mid, prod_low;
        prod_high = num1_high * num2_high;
        prod_low = num1_low * num2_low;
        prod_mid = (num1_high + num1_low) * (num2_high + num2_low)
            - prod_high - prod_low;

        add_trailing_zeroes(prod_high.value, 2 * half_length_ceil);
        add_trailing_zeroes(prod_mid.value, half_length_ceil);

        strip_leading_zeroes(prod_high.value);
        strip_leading_zeroes(prod_mid.value);
        strip_leading_zeroes(prod_low.value);

        product = prod_high + prod_mid + prod_low;
    }
    strip_leading_zeroes(product.value);

    if (this->sign == num.sign)
        product.sign = '+';
    else
        product.sign = '-';

    return product;
}

std::tuple<BigInt, BigInt> divide(const BigInt& dividend, const BigInt& divisor) {
    BigInt quotient, remainder, temp;

    temp = divisor;
    quotient = 1;
    while (temp < dividend) {
        quotient++;
        temp = temp + divisor;
    }
    if (temp > dividend) {
        quotient--;
        remainder = dividend - (temp - divisor);
    }

    return std::make_tuple(quotient, remainder);
}

BigInt BigInt::operator/(const BigInt& num) const {
    if (num == 0) {
        throw std::runtime_error("Division by zero");
    }
    BigInt c = 10;
    BigInt divisor = num;
    BigInt remainder = *this; // Remainder starts as the dividend
    BigInt result;

    while (remainder >= divisor) {
        BigInt multiple = 1;
        BigInt acc_divisor = divisor;

        while (remainder > (acc_divisor * c)) {
            acc_divisor = acc_divisor * c;
            multiple = multiple * c;
        }

        while (remainder >= acc_divisor) {
            remainder = remainder - acc_divisor;
            result = result + multiple;
        }
    }

    return result;
}

BigInt BigInt::operator%(const BigInt& num) const {
    BigInt dividend = *this;
    BigInt divisor = num;

    BigInt remainder;
    if (dividend <= LLONG_MAX and divisor <= LLONG_MAX)
        remainder = std::stoll(dividend.value) % std::stoll(divisor.value);
    else if (dividend < divisor)
        remainder = dividend;
    else {
        BigInt quotient = dividend / divisor;
        remainder = dividend - quotient * divisor;
    }
    strip_leading_zeroes(remainder.value);
    return remainder;
}

BigInt BigInt::operator+(const long long& num) const {
    return *this + BigInt(num);
}

BigInt BigInt::operator-(const long long& num) const {
    return *this - BigInt(num);
}

BigInt BigInt::operator/(const long long& num) const {
    return *this / BigInt(num);
}

BigInt BigInt::operator%(const long long& num) const {
    return *this % BigInt(num);
}

BigInt BigInt::operator++(int) {
    BigInt temp = *this;
    *this = *this + 1;
    return temp;
}

BigInt BigInt::operator--(int) {
    BigInt temp = *this;
    *this = *this - 1;
    return temp;
}

std::istream& operator>>(std::istream& in, BigInt& num) {
    std::string input;
    in >> input;
    num = BigInt(input);
    return in;
}

std::ostream& operator<<(std::ostream& out, const BigInt& num) {
    if (num.sign == '-')
        out << num.sign;
    out << num.value;
    return out;
}
