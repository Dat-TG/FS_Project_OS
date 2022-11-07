#include "numeric.h"
int binaryToDecimal(long long n)
{
    long long num = n;
    int dec_value = 0;

    // Initializing base value to 1, i.e 2^0
    int base = 1;

    long long temp = num;
    while (temp) {
        int last_digit = temp % 10;
        temp = temp / 10LL;

        dec_value += last_digit * base;

        base = base * 2;
    }

    return dec_value;
}
long long decToBinary(int n)
{
    // array to store binary number
    long long binaryNum[32];

    // counter for binary array
    int i = 0;
    while (n > 0) {

        // storing remainder in binary array
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }

    // printing binary array in reverse order
    long long res = 0;
    for (int j = i - 1; j >= 0; j--)
        res=res*10LL+binaryNum[j];
    return res;
}