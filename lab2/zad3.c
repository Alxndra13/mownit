#include <stdio.h>
#include <gsl/gsl_sf_log.h>
int main(void)
{
    double x = 1.0;
    while (x > 0.0)
    {
        unsigned long long bits = *(unsigned long long *)&x;
        unsigned long long mantissa = bits & ((1ull << 52) - 1);
        int exponent = (bits >> 52) & ((1 << 11) - 1);
        exponent -= 1023;
        printf("x: %g\tmantissa: %llu\texponent: %d\n", x, mantissa, exponent);
        x /= 2.0;
    }
    return 0;
}