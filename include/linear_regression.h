#ifndef LINEAR_REGRESSION_H
#define LINEAR_REGRESSION_H

#include "csv.h"

typedef struct
{
    double *weights;
    double bias;
    int n_features;
} LinearModel;

LinearModel train_linear_regression(CSV *x_train, double *y_train, int n_samples, double learning_rate, int epochs);
double *linear_regression_predict(CSV *x, double *weights, double bias);
void free_linear_model(LinearModel *model);

#endif