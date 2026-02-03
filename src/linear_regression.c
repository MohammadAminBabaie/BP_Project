#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "linear_regression.h"

LinearModel train_linear_regression(
    CSV *x_train,
    double *y_train,
    int n_samples,
    double learning_rate,
    int epochs)
{
    int n_features = x_train->cols;

    LinearModel model;
    model.n_features = n_features;
    model.bias = 0.0;
    model.weights = calloc(n_features, sizeof(double));

    for (int epoch = 0; epoch < epochs; epoch++)
    {
        double *grad_w = calloc(n_features, sizeof(double));
        double grad_b = 0.0;

        for (int i = 0; i < n_samples; i++)
        {
            double y_hat = model.bias;

            for (int j = 0; j < n_features; j++)
            {
                y_hat += model.weights[j] * atof(x_train->data[i][j]);
                // printf("%f ", atof(x_train->data[i][j]));
            }
            // printf("\ny_train : %f\n", y_train[i]);

            double error = y_hat - y_train[i];

            for (int j = 0; j < n_features; j++)
                grad_w[j] += error * atof(x_train->data[i][j]);

            grad_b += error;
        }

        for (int j = 0; j < n_features; j++)
            model.weights[j] -= learning_rate * (grad_w[j] / n_samples);

        model.bias -= learning_rate * (grad_b / n_samples);

        if (epoch % 100 == 0)
        {
            double mse = 0.0;
            for (int i = 0; i < n_samples; i++)
            {
                double pred = model.bias;
                for (int j = 0; j < n_features; j++)
                    pred += model.weights[j] * atof(x_train->data[i][j]);

                double diff = pred - y_train[i];
                mse += diff * diff;
            }
            mse /= n_samples;
            // printf("Epoch %d | MSE = %.6f\n", epoch, mse);
        }

        free(grad_w);
    }

    return model;
}

double *linear_regression_predict(
    CSV *x,
    double *weights,
    double bias)
{
    int n = x->rows;
    int m = x->cols;

    double *y_pred = malloc(n * sizeof(double));

    for (int i = 0; i < n; i++)
    {
        double pred = bias;
        for (int j = 0; j < m; j++)
        {
            pred += weights[j] * atof(x->data[i][j]);
        }
        y_pred[i] = pred;
    }

    return y_pred;
}

void free_linear_model(LinearModel *model)
{
    free(model->weights);
}
