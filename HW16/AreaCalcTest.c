#include <stdio.h>

int main()
{
    float R1, R2, d, x, r2;
    R1 = 0.75;
    R2 = 0.31;
    d = 0.53;

    x = (R2*R2 - R1*R1 + d*d)/2*d;

    r2 = R2*R2 - x*x;

    printf("R1: %f\nR2: %f\nd: %f\nx: %f\nr^2: %f\n", R1, R2, d, x, r2);

    return 0;
}