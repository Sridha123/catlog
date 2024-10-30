#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

// Function to convert a number from a given base to decimal
uint64_t baseToDecimal(const char* value, int base) {
    uint64_t result = 0;
    int length = strlen(value);
    for (int i = 0; i < length; i++) {
        int digit;
        if (value[i] >= '0' && value[i] <= '9') {
            digit = value[i] - '0';
        } else if (value[i] >= 'A' && value[i] <= 'F') {
            digit = value[i] - 'A' + 10;
        } else {
            digit = value[i] - 'a' + 10;
        }
        result = result * base + digit;
    }
    return result;
}

// Lagrange interpolation to find constant term c (y-intercept)
double lagrangeInterpolation(int* x, uint64_t* y, int k) {
    double result = 0.0;
    for (int i = 0; i < k; i++) {
        double term = y[i];
        for (int j = 0; j < k; j++) {
            if (i != j) {
                term *= (0.0 - x[j]) / (x[i] - x[j]);
            }
        }
        result += term;
    }
    return result;
}

// Main function to read data and find the secret (constant term c)
int main() {
    // Sample input: JSON-like structure
    int n = 4; // Number of roots provided
    int k = 3; // Minimum number of roots required

    // Sample data
    const char* bases[] = { "2", "10", "10", "4" };
    const char* values[] = { "111", "12", "45", "213" };
    int keys[] = { 2, 3, 4, 6 };

    uint64_t yValues[k];
    int xValues[k];

    // Decode Y values and store x, y pairs
    for (int i = 0; i < k; i++) {
        int base = atoi(bases[i]);
        yValues[i] = baseToDecimal(values[i], base);
        xValues[i] = keys[i];
    }

    // Calculate the constant term c using Lagrange interpolation
    double secret = lagrangeInterpolation(xValues, yValues, k);
    printf("The secret constant term (c) is approximately: %.0f\n", secret);

    return 0;
}

