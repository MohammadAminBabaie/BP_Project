#include <math.h>
#include "metrics.h"

double mse(double *y, double *yhat, int n)
{
    double s = 0;
    for (int i = 0; i < n; i++)
        s += pow(y[i] - yhat[i], 2);
    return s / n;
}

double mae(double *y, double *yhat, int n)
{
    double s = 0;
    for (int i = 0; i < n; i++)
        s += fabs(y[i] - yhat[i]);
    return s / n;
}

double mape(double *y, double *yhat, int n)
{
    double s = 0;
    for (int i = 0; i < n; i++)
    {
        if (y[i] != 0)
            s += fabs((y[i] - yhat[i]) / y[i]);
    }
    return 100 * s / n;
}
