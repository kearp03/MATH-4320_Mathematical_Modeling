#include <stdio.h>
#include <math.h>

int main()
{
    float R1, R2, d, x, r2;
    R1 = 0.75;
    R2 = 0.31;
    d = R1 + R2;
    float decr = -0.2;

    while(d > 0.0)
    {
        printf("%f\n", d);
        x = (R2*R2 - R1*R1 + d*d)/2*d;

        r2 = R2*R2 - x*x;

        printf("First:\nR1: %f\nR2: %f\nd: %f\nx: %f\nr^2: %f\n\n", R1, R2, d, x, r2);

        float s = (R1 + R2 + d)/2.0;
        r2 = sqrt((s-d)*(s-R1)*(s-R2)*s);

        printf("Heron:\nR1: %f\nR2: %f\nd: %f\nx: %f\nr^2: %f\n\n", R1, R2, d, x, r2);

        d += decr;
    }
    return 0;
}