#include <math.h>
#include <stdio.h>
double getArea(double a, double b, double c)
{
    if (a < 0 || b < 0 || c < 0) throw "Side length must be greater than zero";

    if ((a+b) <= c || (a+c) <= b || (b+c) <= a) throw "Any sum of two sides must greater than the third one";

    double d = (a+b+c) / 2;

    return sqrt(d * (d-a) * (d-b) * (d-c));
}

int main()
{
    double a = 12, b = 14, c = -18, ret;
    try {
        ret = getArea(a, b, c);
    }
    catch (char* e) {
        printf("%s\n", e);
    }
    catch (...) {
        printf("Any exception");
    }
    return 0;
}